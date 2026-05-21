"""
Helper para gerar ficheiros .cpp a partir das entradas do
sample_30_problems.jsonl. Usado pelo Claude durante a tradução manual.

Uso (no Python):
    from _helper import problem, py_to_cpp, translate_asserts
"""

import ast
import json
from pathlib import Path

_PROBS = None


def all_problems():
    global _PROBS
    if _PROBS is None:
        with open(Path(__file__).parent / "sample_30_problems.jsonl") as f:
            _PROBS = [json.loads(line) for line in f]
    return _PROBS


def problem(task_id):
    for p in all_problems():
        if p["task_id"] == task_id:
            return p
    raise KeyError(task_id)


def py_to_cpp(value, cpp_type=None):
    if isinstance(value, bool):
        return "true" if value else "false"
    if isinstance(value, int):
        # 'long long' literals get a LL suffix when needed
        if cpp_type in ("long long", "long long int"):
            return f"{value}LL"
        return str(value)
    if isinstance(value, float):
        s = repr(value)
        if "." not in s and "e" not in s and "E" not in s:
            s += ".0"
        return s
    if isinstance(value, str):
        return json.dumps(value)
    if value is None:
        return "nullptr"
    if isinstance(value, list):
        elem_type = None
        if cpp_type and cpp_type.startswith("vector<") and cpp_type.endswith(">"):
            elem_type = cpp_type[7:-1]
        elements = [py_to_cpp(e, elem_type) for e in value]
        if cpp_type:
            return f"{cpp_type}{{{', '.join(elements)}}}"
        return f"{{{', '.join(elements)}}}"
    if isinstance(value, tuple):
        return f"{{{', '.join(py_to_cpp(e) for e in value)}}}"
    raise ValueError(f"Unsupported: {value!r}")


def translate_asserts(test_str, method_name, arg_specs, ret_type,
                      indent="    "):
    """
    arg_specs: list of (kw_name, cpp_type) in declaration order.
    Returns a string with one C++ assert per line.
    """
    tree = ast.parse(test_str)
    out = []
    for fn in ast.walk(tree):
        if isinstance(fn, ast.FunctionDef) and fn.name == "check":
            for stmt in fn.body:
                if not isinstance(stmt, ast.Assert):
                    continue
                cmp = stmt.test
                if not isinstance(cmp, ast.Compare):
                    continue
                call = cmp.left
                rhs_node = cmp.comparators[0]
                rhs_val = ast.literal_eval(rhs_node)
                kw = {k.arg: ast.literal_eval(k.value)
                      for k in call.keywords}
                pos = [ast.literal_eval(a) for a in call.args]
                cpp_args = []
                for i, (name, ctype) in enumerate(arg_specs):
                    if name in kw:
                        cpp_args.append(py_to_cpp(kw[name], ctype))
                    elif i < len(pos):
                        cpp_args.append(py_to_cpp(pos[i], ctype))
                    else:
                        raise ValueError(
                            f"Missing arg {name} in: "
                            f"{ast.unparse(stmt)}"
                        )
                rhs_cpp = py_to_cpp(rhs_val, ret_type)
                call_str = f"sol.{method_name}({', '.join(cpp_args)})"
                # Extra parens guard against the assert() macro splitting
                # on commas inside braces (e.g. vector<int>{1,2,3}).
                out.append(f"{indent}assert(({call_str} == {rhs_cpp}));")
    return "\n".join(out)


def write_translation(task_id, difficulty, includes_extra,
                      solution_code, asserts_code, helpers=""):
    """Generate a .cpp file with the standard skeleton."""
    base_includes = [
        "<cassert>", "<iostream>", "<vector>", "<string>",
        "<unordered_map>", "<unordered_set>", "<map>", "<set>",
        "<algorithm>", "<cmath>", "<climits>", "<numeric>",
        "<queue>", "<stack>", "<deque>", "<functional>",
        "<utility>", "<tuple>",
    ]
    all_inc = base_includes + list(includes_extra)
    seen = set()
    inc_lines = []
    for h in all_inc:
        if h not in seen:
            seen.add(h)
            inc_lines.append(f"#include {h}")
    body = f"""// task_id: {task_id}
// difficulty: {difficulty}

{chr(10).join(inc_lines)}

using namespace std;

{helpers}
{solution_code}

int main() {{
    Solution sol;

{asserts_code}

    cout << "All tests passed for {task_id}" << endl;
    return 0;
}}
"""
    out_path = Path(__file__).parent / "translations" / f"{task_id}.cpp"
    out_path.write_text(body, encoding="utf-8")
    return out_path
