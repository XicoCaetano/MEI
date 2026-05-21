from __future__ import annotations

import csv
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Iterable

ROOT = Path(__file__).resolve().parent
CSV_SAIDA = ROOT / "resultados_experimentais.csv"
LOG_PATH = ROOT / "avaliacao.log"

LINGUAGENS = ("python", "cpp")
MODELOS = ("sonnet", "gemini", "deepseek")
NUM_FICHEIROS = 30
TIMEOUT_TESTES = 15
TIMEOUT_COMPILACAO = 15
TIMEOUT_COV = 15

COLUNAS_CSV = [
    "Linguagem",
    "Modelo",
    "ID_Ficheiro",
    "Compilou_Sem_Erro_Sintaxe",
    "Executou_Sem_Crash",
    "Line_Coverage_Percentage",
    "Branch_Coverage_Percentage",
    "Total_Testes",
    "Testes_Passaram",
    "Testes_Falharam",
    "Qtd_Assercoes",
]


def _configure_stdout() -> None:
    if hasattr(sys.stdout, "reconfigure"):
        try:
            sys.stdout.reconfigure(encoding="utf-8", errors="replace")
        except Exception:
            pass


def _log(msg: str) -> None:
    print(msg, flush=True)
    try:
        with LOG_PATH.open("a", encoding="utf-8") as fp:
            fp.write(msg + "\n")
    except Exception:
        pass


def _run(
    cmd: list[str],
    cwd: Path | None = None,
    timeout: int = TIMEOUT_TESTES,
    env: dict[str, str] | None = None,
) -> tuple[int, str, str]:
    try:
        completed = subprocess.run(
            cmd,
            cwd=str(cwd) if cwd else None,
            capture_output=True,
            text=True,
            timeout=timeout,
            env=env,
        )
        return completed.returncode, completed.stdout, completed.stderr
    except subprocess.TimeoutExpired:
        return -1, "", "TIMEOUT"
    except FileNotFoundError as exc:
        return -1, "", str(exc)
    except Exception as exc:  # noqa: BLE001
        return -1, "", str(exc)


def _normalize_ids(index: int) -> tuple[int, str, str]:
    file_id = index + 1
    return file_id, f"{file_id:02d}", str(index)


def _candidate_paths(
    linguagem: str,
    modelo: str,
    file_id_str: str,
    legacy_id_str: str,
) -> tuple[list[Path], list[Path]]:
    if linguagem == "python":
        source_candidates = [
            ROOT / "dataset" / linguagem / "original" / f"func_{file_id_str}.py",
            ROOT / "dataset" / linguagem / "original" / f"task_{legacy_id_str}.py",
            ROOT / "experiencia_dataset" / linguagem / f"task_{legacy_id_str}.py",
        ]
        test_candidates = [
            ROOT / "dataset" / linguagem / modelo / f"test_func_{file_id_str}.py",
            ROOT / "dataset" / linguagem / modelo / f"test_task_{legacy_id_str}.py",
            ROOT / modelo / linguagem / f"test_task_{legacy_id_str}.py",
        ]
    else:
        source_candidates = [
            ROOT / "dataset" / linguagem / "original" / f"func_{file_id_str}.cpp",
            ROOT / "dataset" / linguagem / "original" / f"task_{legacy_id_str}.cpp",
            ROOT / "experiencia_dataset" / linguagem / f"task_{legacy_id_str}.cpp",
        ]
        test_candidates = [
            ROOT / "dataset" / linguagem / modelo / f"test_func_{file_id_str}.cpp",
            ROOT / "dataset" / linguagem / modelo / f"test_task_{legacy_id_str}.cpp",
            ROOT / modelo / linguagem / f"test_task_{legacy_id_str}.cpp",
        ]
    return source_candidates, test_candidates


def _first_existing(paths: Iterable[Path]) -> Path | None:
    for path in paths:
        if path.exists():
            return path
    return None


def _count_file_occurrences(path: Path, pattern: str) -> int:
    try:
        text = path.read_text(encoding="utf-8", errors="ignore")
    except Exception:
        return 0
    return len(re.findall(pattern, text))


def _parse_pytest_summary(output: str) -> tuple[int, int, int]:
    passed = 0
    failed = 0
    summary_line = ""
    for line in reversed(output.splitlines()):
        if "passed" in line or "failed" in line or "error" in line:
            summary_line = line
            break

    for value, label in re.findall(r"(\d+)\s+(passed|failed|errors?|skipped|xfailed|xpassed)", summary_line):
        if label == "passed":
            passed = int(value)
        elif label in {"failed", "error", "errors"}:
            failed += int(value)

    total = passed + failed
    return total, passed, failed


def _parse_pytest_coverage(output: str, module_name: str) -> tuple[float, float]:
    line_cov = 0.0
    branch_cov = 0.0
    # Match either 'module_name.py' or 'module_name' and accept coverage percent
    module_pattern = re.compile(
        rf"^{re.escape(module_name)}(?:\.py)?\s+.*?\s+(\d+(?:\.\d+)?)%",
        re.MULTILINE,
    )
    total_pattern = re.compile(
        r"^TOTAL\s+.*?\s+(\d+(?:\.\d+)?)%",
        re.MULTILINE,
    )
    branch_pattern = re.compile(r"Branch(?:es)?\s+.*?\s+(\d+(?:\.\d+)?)%")

    match = module_pattern.search(output) or total_pattern.search(output)
    if match:
        line_cov = float(match.group(1))

    branch_match = branch_pattern.search(output)
    if branch_match:
        branch_cov = float(branch_match.group(1))

    if branch_cov == 0.0:
        branch_cov = line_cov

    return line_cov, branch_cov


def _parse_gcov_coverage(output: str, target_file: str) -> tuple[float, float]:
    line_cov = 0.0
    branch_cov = 0.0
    blocks = re.split(r"\n(?=File ')", output)
    target_block = ""
    for block in blocks:
        if target_file in block:
            target_block = block
            break
    if not target_block:
        target_block = output

    line_match = re.search(r"Lines executed:(\d+(?:\.\d+)?)%", target_block)
    branch_match = re.search(r"Branches executed:(\d+(?:\.\d+)?)%", target_block)
    if line_match:
        line_cov = float(line_match.group(1))
    if branch_match:
        branch_cov = float(branch_match.group(1))
    return line_cov, branch_cov


def _cleanup_temp_artifacts(temp_dir: Path) -> None:
    for pattern in ("*.gcno", "*.gcda", "*.gcov", "test_exec", "test_exec.exe"):
        for item in temp_dir.glob(pattern):
            try:
                item.unlink()
            except Exception:
                pass


def avaliar_python(modelo: str, source_path: Path, test_path: Path, file_id: int) -> dict:
    result = {
        "Linguagem": "python",
        "Modelo": modelo,
        "ID_Ficheiro": file_id,
        "Compilou_Sem_Erro_Sintaxe": 0,
        "Executou_Sem_Crash": 0,
        "Line_Coverage_Percentage": 0.0,
        "Branch_Coverage_Percentage": 0.0,
        "Total_Testes": 0,
        "Testes_Passaram": 0,
        "Testes_Falharam": 0,
        "Qtd_Assercoes": _count_file_occurrences(test_path, r"\bassert\b"),
    }

    if not source_path.exists() or not test_path.exists() or test_path.stat().st_size == 0:
        _log(f"[PY] {modelo} #{file_id:02d} - ficheiros em falta ou teste vazio")
        return result

    _log(f"[PY] {modelo} #{file_id:02d} - a preparar execução")

    with tempfile.TemporaryDirectory(prefix=f"avaliacao_py_{modelo}_{file_id:02d}_") as temp_root:
        temp_dir = Path(temp_root)
        local_source = temp_dir / source_path.name
        local_test = temp_dir / test_path.name
        shutil.copy2(source_path, local_source)
        shutil.copy2(test_path, local_test)

        if _run([sys.executable, "-m", "py_compile", local_test.name], cwd=temp_dir, timeout=TIMEOUT_TESTES)[0] != 0:
            _log(f"[PY] {modelo} #{file_id:02d} - erro de sintaxe no teste")
            return result

        result["Compilou_Sem_Erro_Sintaxe"] = 1

        env = os.environ.copy()
        env["PYTHONPATH"] = str(temp_dir)

        # Detect module names imported by the test (e.g. 'solution', 'your_module')
        test_text = ""
        try:
            test_text = local_test.read_text(encoding="utf-8", errors="ignore")
        except Exception:
            test_text = ""
        candidates = set(re.findall(r"from\s+([A-Za-z_][A-Za-z0-9_]*)\s+import", test_text))
        candidates |= set(re.findall(r"import\s+([A-Za-z_][A-Za-z0-9_]*)(?:\s|$)", test_text))
        EXCLUDE_MODULES = {
            "pytest",
            "typing",
            "unittest",
            "math",
            "os",
            "sys",
            "re",
            "pathlib",
            "random",
            "collections",
            "itertools",
            "operator",
            "builtins",
        }
        # Copy the source also under candidate module names so tests that import 'solution'
        # or 'your_module' will actually import the dataset source.
        for cand in candidates:
            if cand and cand not in EXCLUDE_MODULES:
                dest = temp_dir / f"{cand}.py"
                if not dest.exists():
                    try:
                        shutil.copy2(local_source, dest)
                    except Exception:
                        pass

        # Run pytest with coverage over the whole tmp dir, so executed modules are reported.
        cmd = [
            sys.executable,
            "-m",
            "pytest",
            local_test.name,
            "--cov=.",
            "--cov-branch",
            "--cov-report=term-missing",
            "--tb=no",
            "-q",
        ]
        rc, stdout, stderr = _run(cmd, cwd=temp_dir, timeout=TIMEOUT_TESTES, env=env)
        combined = "\n".join(part for part in (stdout, stderr) if part)

        if rc in (0, 1):
            result["Executou_Sem_Crash"] = 1

        total, passed, failed = _parse_pytest_summary(combined)
        line_cov, branch_cov = _parse_pytest_coverage(combined, local_source.stem)
        # If the original filename did not appear in the coverage report, try candidate names
        if line_cov == 0.0:
            for cand in candidates:
                cov_line, cov_branch = _parse_pytest_coverage(combined, cand)
                if cov_line > 0.0:
                    line_cov, branch_cov = cov_line, cov_branch
                    break

        result["Total_Testes"] = total
        result["Testes_Passaram"] = passed
        result["Testes_Falharam"] = failed
        result["Line_Coverage_Percentage"] = line_cov
        result["Branch_Coverage_Percentage"] = branch_cov

        _log(
            f"[PY] {modelo} #{file_id:02d} - rc={rc} total={total} pass={passed} fail={failed} "
            f"line={line_cov:.2f}% branch={branch_cov:.2f}% asserts={result['Qtd_Assercoes']}"
        )

    return result


def _parse_gtest_summary(output: str) -> tuple[int, int, int]:
    total_match = re.search(r"(\d+) tests? from", output)
    passed_matches = re.findall(r"\[\s*OK\s*\]", output)
    failed_matches = re.findall(r"\[\s*FAILED\s*\]", output)

    if total_match and (passed_matches or failed_matches):
        total = int(total_match.group(1))
        passed = len(passed_matches)
        failed = len(failed_matches)
        if passed + failed <= total:
            return total, passed, failed

    passed = len(passed_matches)
    failed = len(failed_matches)
    total = passed + failed
    return total, passed, failed


def avaliar_cpp(modelo: str, source_path: Path, test_path: Path, file_id: int) -> dict:
    result = {
        "Linguagem": "cpp",
        "Modelo": modelo,
        "ID_Ficheiro": file_id,
        "Compilou_Sem_Erro_Sintaxe": 0,
        "Executou_Sem_Crash": 0,
        "Line_Coverage_Percentage": 0.0,
        "Branch_Coverage_Percentage": 0.0,
        "Total_Testes": 0,
        "Testes_Passaram": 0,
        "Testes_Falharam": 0,
        "Qtd_Assercoes": _count_file_occurrences(test_path, r"\b(?:EXPECT|ASSERT)_[A-Z0-9_]*\b"),
    }

    if not source_path.exists() or not test_path.exists() or test_path.stat().st_size == 0:
        _log(f"[CPP] {modelo} #{file_id:02d} - ficheiros em falta ou teste vazio")
        return result

    _log(f"[CPP] {modelo} #{file_id:02d} - a preparar compilação")

    with tempfile.TemporaryDirectory(prefix=f"avaliacao_cpp_{modelo}_{file_id:02d}_") as temp_root:
        temp_dir = Path(temp_root)
        local_source = temp_dir / source_path.name
        local_test = temp_dir / test_path.name
        shutil.copy2(source_path, local_source)
        shutil.copy2(test_path, local_test)

        exec_name = "test_exec"
        exec_path = temp_dir / exec_name
        if os.name == "nt":
            exec_path = temp_dir / f"{exec_name}.exe"

        cmd_compile = [
            "g++",
            "-fprofile-arcs",
            "-ftest-coverage",
            local_source.name,
            local_test.name,
            "-lgtest",
            "-lgtest_main",
            "-pthread",
            "-o",
            exec_name,
        ]
        rc_compile, stdout_compile, stderr_compile = _run(
            cmd_compile,
            cwd=temp_dir,
            timeout=TIMEOUT_COMPILACAO,
        )

        if rc_compile != 0:
            _log(f"[CPP] {modelo} #{file_id:02d} - compilação falhou")
            if stderr_compile.strip():
                _log(stderr_compile.strip().splitlines()[-1])
            return result

        result["Compilou_Sem_Erro_Sintaxe"] = 1

        if not exec_path.exists():
            fallback_path = temp_dir / exec_name
            if fallback_path.exists():
                exec_path = fallback_path

        rc_exec, stdout_exec, stderr_exec = _run(
            [str(exec_path)],
            cwd=temp_dir,
            timeout=TIMEOUT_TESTES,
        )
        combined_exec = "\n".join(part for part in (stdout_exec, stderr_exec) if part)

        if rc_exec != -1:
            result["Executou_Sem_Crash"] = 1

        total, passed, failed = _parse_gtest_summary(combined_exec)
        result["Total_Testes"] = total
        result["Testes_Passaram"] = passed
        result["Testes_Falharam"] = failed

        rc_gcov, stdout_gcov, stderr_gcov = _run(
            ["gcov", "-b", local_source.name],
            cwd=temp_dir,
            timeout=TIMEOUT_COV,
        )
        combined_gcov = "\n".join(part for part in (stdout_gcov, stderr_gcov) if part)
        line_cov, branch_cov = _parse_gcov_coverage(combined_gcov, local_source.name)
        result["Line_Coverage_Percentage"] = line_cov
        result["Branch_Coverage_Percentage"] = branch_cov

        _log(
            f"[CPP] {modelo} #{file_id:02d} - compile={rc_compile} exec={rc_exec} gcov={rc_gcov} "
            f"total={total} pass={passed} fail={failed} line={line_cov:.2f}% branch={branch_cov:.2f}% "
            f"asserts={result['Qtd_Assercoes']}"
        )

        _cleanup_temp_artifacts(temp_dir)

    return result


def _resultado_vazio(linguagem: str, modelo: str, file_id: int, qtd_assercoes: int = 0) -> dict:
    return {
        "Linguagem": linguagem,
        "Modelo": modelo,
        "ID_Ficheiro": file_id,
        "Compilou_Sem_Erro_Sintaxe": 0,
        "Executou_Sem_Crash": 0,
        "Line_Coverage_Percentage": 0.0,
        "Branch_Coverage_Percentage": 0.0,
        "Total_Testes": 0,
        "Testes_Passaram": 0,
        "Testes_Falharam": 0,
        "Qtd_Assercoes": qtd_assercoes,
    }


def _avaliar_par(linguagem: str, modelo: str, file_id: int) -> dict:
    _, file_id_str, legacy_id_str = _normalize_ids(file_id - 1)
    source_candidates, test_candidates = _candidate_paths(
        linguagem,
        modelo,
        file_id_str,
        legacy_id_str,
    )
    source_path = _first_existing(source_candidates)
    test_path = _first_existing(test_candidates)

    if source_path is None or test_path is None:
        _log(f"[{linguagem.upper()}] {modelo} #{file_id:02d} - ficheiros não encontrados")
        return _resultado_vazio(linguagem, modelo, file_id)

    if linguagem == "python":
        return avaliar_python(modelo, source_path, test_path, file_id)
    return avaliar_cpp(modelo, source_path, test_path, file_id)


def _imprimir_resumo(resultados: list[dict]) -> None:
    agrupado: dict[tuple[str, str], list[dict]] = {}
    for row in resultados:
        agrupado.setdefault((row["Linguagem"], row["Modelo"]), []).append(row)

    _log("")
    _log("Resumo por linguagem e modelo")
    _log("Linguagem  Modelo     Compilou  Executou  Cob_Line  Cob_Branch")
    for (linguagem, modelo), rows in sorted(agrupado.items()):
        compilou = sum(int(r["Compilou_Sem_Erro_Sintaxe"]) for r in rows)
        executou = sum(int(r["Executou_Sem_Crash"]) for r in rows)
        line_media = sum(float(r["Line_Coverage_Percentage"]) for r in rows) / len(rows)
        branch_media = sum(float(r["Branch_Coverage_Percentage"]) for r in rows) / len(rows)
        _log(
            f"{linguagem:<10} {modelo:<10} {compilou:>7}/{len(rows):<3} {executou:>7}/{len(rows):<3} "
            f"{line_media:>7.2f}% {branch_media:>10.2f}%"
        )


def _salvar_csv(resultados: list[dict]) -> None:
    with CSV_SAIDA.open("w", newline="", encoding="utf-8") as fp:
        writer = csv.DictWriter(fp, fieldnames=COLUNAS_CSV)
        writer.writeheader()
        writer.writerows(resultados)


def main() -> None:
    _configure_stdout()
    if LOG_PATH.exists():
        try:
            LOG_PATH.unlink()
        except Exception:
            pass

    _log("Início da avaliação automática")
    _log(f"Raiz do projeto: {ROOT}")
    _log(f"Saída CSV: {CSV_SAIDA}")

    resultados: list[dict] = []
    for linguagem in LINGUAGENS:
        for modelo in MODELOS:
            _log("")
            _log(f"=== {linguagem.upper()} | {modelo.upper()} ===")
            for file_id in range(1, NUM_FICHEIROS + 1):
                try:
                    resultados.append(_avaliar_par(linguagem, modelo, file_id))
                except Exception as exc:  # noqa: BLE001
                    _log(f"[{linguagem.upper()}] {modelo} #{file_id:02d} - erro inesperado: {exc}")
                    resultados.append(_resultado_vazio(linguagem, modelo, file_id))

    _salvar_csv(resultados)
    _log("")
    _log(f"Avaliação concluída. {len(resultados)} linhas exportadas para {CSV_SAIDA}")
    _imprimir_resumo(resultados)


if __name__ == "__main__":
    main()
