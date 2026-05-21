// task_id: apply-substitutions
// difficulty: Medium

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>
#include <numeric>
#include <queue>
#include <stack>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>

using namespace std;


class Solution {
public:
    string applySubstitutions(vector<vector<string>> replacements, string text) {
        unordered_map<string,string> d;
        for (auto& r : replacements) d[r[0]] = r[1];
        function<string(const string&)> dfs = [&](const string& s) -> string {
            size_t i = s.find('%');
            if (i == string::npos) return s;
            size_t j = s.find('%', i + 1);
            if (j == string::npos) return s;
            string key = s.substr(i + 1, j - i - 1);
            string replacement = dfs(d[key]);
            return s.substr(0, i) + replacement + dfs(s.substr(j + 1));
        };
        return dfs(text);
    }
};

int main() {
    Solution sol;

    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"W", "wxy"}, vector<string>{"X", "xyz"}, vector<string>{"Y", "%W%_%X%"}, vector<string>{"Z", "uvw"}}, "%Y%_%Z%") == "wxy_xyz_uvw"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"M", "mno"}, vector<string>{"N", "pqr"}, vector<string>{"O", "stu"}, vector<string>{"P", "%M%%N%"}}, "%M%_%N%_%O%_%P%") == "mno_pqr_stu_mnopqr"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"X", "xyz"}, vector<string>{"Y", "uvw"}, vector<string>{"Z", "%X%%Y%"}}, "%X%_%Y%_%Z%") == "xyz_uvw_xyzuvw"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"M", "mno"}, vector<string>{"N", "pqr"}, vector<string>{"O", "stu"}, vector<string>{"P", "vwx"}}, "%M%_%N%_%O%_%P%") == "mno_pqr_stu_vwx"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "abc"}, vector<string>{"B", "def"}}, "%A%_%B%") == "abc_def"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"Q", "qwe"}, vector<string>{"R", "rty"}, vector<string>{"S", "%Q%%R%"}, vector<string>{"T", "%R%%S%"}}, "%Q%_%R%_%S%_%T%") == "qwe_rty_qwerty_rtyqwerty"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"X", "xyz"}, vector<string>{"Y", "uvw"}, vector<string>{"Z", "%X%_%Y%"}}, "%X%_%Y%_%Z%") == "xyz_uvw_xyz_uvw"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"Q", "qwe"}, vector<string>{"R", "rty"}, vector<string>{"S", "uiop"}, vector<string>{"T", "asdf"}, vector<string>{"U", "%Q%%R%"}}, "%Q%_%R%_%S%_%T%_%U%") == "qwe_rty_uiop_asdf_qwerty"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "bce"}, vector<string>{"B", "ace"}, vector<string>{"C", "abc%B%"}}, "%A%_%B%_%C%") == "bce_ace_abcace"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"X", "mno"}, vector<string>{"Y", "pqr"}, vector<string>{"Z", "%X%%Y%"}, vector<string>{"A", "stu"}, vector<string>{"B", "%Z%%A%"}, vector<string>{"C", "vwx%B%"}}, "%C%") == "vwxmnopqrstu"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "xy%B%zy"}, vector<string>{"B", "wv%C%vu"}, vector<string>{"C", "ut%D%tu"}, vector<string>{"D", "sr%E%sr"}, vector<string>{"E", "qp%F%pq"}, vector<string>{"F", "on%G%no"}, vector<string>{"G", "ml%H%ml"}, vector<string>{"H", "lk%I%lk"}, vector<string>{"I", "ji%J%ji"}, vector<string>{"J", "hg"}}, "%A%_%B%_%C%_%D%_%E%_%F%_%G%_%H%_%I%_%J%") == "xywvutsrqponmllkjihgjilkmlnopqsrtuvuzy_wvutsrqponmllkjihgjilkmlnopqsrtuvu_utsrqponmllkjihgjilkmlnopqsrtu_srqponmllkjihgjilkmlnopqsr_qponmllkjihgjilkmlnopq_onmllkjihgjilkmlno_mllkjihgjilkml_lkjihgjilk_jihgji_hg"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"N", "abc%O%"}, vector<string>{"O", "def%P%"}, vector<string>{"P", "ghi"}, vector<string>{"Q", "jkl%O%"}, vector<string>{"R", "mno%P%"}, vector<string>{"S", "pqr%O%"}}, "%N%_%Q%_%R%_%S%") == "abcdefghi_jkldefghi_mnoghi_pqrdefghi"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "bcd"}, vector<string>{"B", "%A%%A%"}, vector<string>{"C", "%B%def"}, vector<string>{"D", "ghi%C%"}}, "%A%_%B%_%C%_%D%") == "bcd_bcdbcd_bcdbcddef_ghibcdbcddef"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"S", "stu"}, vector<string>{"T", "vwx"}, vector<string>{"U", "%S%%T%"}, vector<string>{"V", "%U%%U%"}, vector<string>{"W", "%V%%V%"}, vector<string>{"X", "%W%%W%"}, vector<string>{"Y", "%X%%X%"}}, "%S%_%T%_%U%_%V%_%W%_%X%_%Y%") == "stu_vwx_stuvwx_stuvwxstuvwx_stuvwxstuvwxstuvwxstuvwx_stuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwx_stuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwxstuvwx"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"H", "xyz%I%"}, vector<string>{"I", "uvw"}, vector<string>{"J", "%H%_%I%"}, vector<string>{"K", "lmn"}, vector<string>{"L", "opq%I%"}, vector<string>{"M", "rst%I%"}}, "%J%_%K%_%L%_%M%") == "xyzuvw_uvw_lmn_opquvw_rstuvw"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"S", "abc"}, vector<string>{"T", "def"}, vector<string>{"U", "%S%%T%"}, vector<string>{"V", "%U%ghi"}, vector<string>{"W", "jkl%V%"}}, "%W%") == "jklabcdefghi"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"E", "efg"}, vector<string>{"F", "hij"}, vector<string>{"G", "%E%%F%"}, vector<string>{"H", "%G%%G%"}, vector<string>{"I", "%H%%H%"}, vector<string>{"J", "%I%%I%"}}, "%E%_%F%_%G%_%H%_%I%_%J%") == "efg_hij_efghij_efghijefghij_efghijefghijefghijefghij_efghijefghijefghijefghijefghijefghijefghijefghij"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "abc"}, vector<string>{"B", "def"}, vector<string>{"C", "%A%%B%"}, vector<string>{"D", "%C%%C%"}}, "%A%_%B%_%C%_%D%") == "abc_def_abcdef_abcdefabcdef"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"S", "%T%%U%"}, vector<string>{"T", "vwx"}, vector<string>{"U", "%V%uvw"}, vector<string>{"V", "xyz"}, vector<string>{"W", "123"}, vector<string>{"X", "%W%%S%"}}, "%X%_%S%_%U%_%V%_%W%") == "123vwxxyzuvw_vwxxyzuvw_xyzuvw_xyz_123"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"L", "lmn"}, vector<string>{"M", "nop"}, vector<string>{"N", "qrs"}, vector<string>{"O", "%L%%M%"}, vector<string>{"P", "%O%%N%"}, vector<string>{"Q", "%P%%P%"}}, "%L%_%M%_%N%_%O%_%P%_%Q%") == "lmn_nop_qrs_lmnnop_lmnnopqrs_lmnnopqrslmnnopqrs"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "bcd%F%"}, vector<string>{"B", "%E%abc"}, vector<string>{"C", "%A%%B%"}, vector<string>{"D", "xyz"}, vector<string>{"E", "uvw"}, vector<string>{"F", "123"}}, "%C%_%D%_%E%_%F%") == "bcd123uvwabc_xyz_uvw_123"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "abc"}, vector<string>{"B", "def"}, vector<string>{"C", "%A%%B%"}, vector<string>{"D", "%C%%C%"}, vector<string>{"E", "%D%%D%"}, vector<string>{"F", "%E%%E%"}, vector<string>{"G", "%F%%F%"}}, "%A%_%B%_%C%_%D%_%E%_%F%_%G%") == "abc_def_abcdef_abcdefabcdef_abcdefabcdefabcdefabcdef_abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdef_abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdef"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"P", "pqr"}, vector<string>{"Q", "%P%_%P%"}, vector<string>{"R", "%Q%_%Q%"}, vector<string>{"S", "%R%_%R%"}}, "%P%_%Q%_%R%_%S%") == "pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr_pqr"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "bcd%F%efg"}, vector<string>{"B", "hij%G%klm"}, vector<string>{"C", "nop%H%qrs"}, vector<string>{"D", "tuv%I%wxy"}, vector<string>{"E", "yz%J%abc"}, vector<string>{"F", "def"}, vector<string>{"G", "ghi"}, vector<string>{"H", "jkl"}, vector<string>{"I", "mno"}, vector<string>{"J", "pqr"}}, "%A%_%B%_%C%_%D%_%E%") == "bcddefefg_hijghiklm_nopjklqrs_tuvmnowxy_yzpqrabc"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"P", "pqr"}, vector<string>{"Q", "stu%P%"}, vector<string>{"R", "uvw%Q%"}, vector<string>{"S", "xyz%R%"}, vector<string>{"T", "abc"}, vector<string>{"U", "def%T%"}, vector<string>{"V", "ghi%U%"}, vector<string>{"W", "jkl%V%"}, vector<string>{"X", "mno%W%"}, vector<string>{"Y", "opq%X%"}, vector<string>{"Z", "rst%Y%"}}, "%Z%") == "rstopqmnojklghidefabc"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"M", "mnop"}, vector<string>{"N", "%O%%P%"}, vector<string>{"O", "qrst"}, vector<string>{"P", "%Q%%R%"}, vector<string>{"Q", "uvw"}, vector<string>{"R", "xyz"}}, "%M%_%N%_%O%_%P%_%Q%_%R%") == "mnop_qrstuvwxyz_qrst_uvwxyz_uvw_xyz"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"U", "uvw"}, vector<string>{"V", "xyz"}, vector<string>{"W", "%U%%V%"}, vector<string>{"X", "%W%%W%"}, vector<string>{"Y", "%X%%X%"}}, "%U%_%V%_%W%_%X%_%Y%") == "uvw_xyz_uvwxyz_uvwxyzuvwxyz_uvwxyzuvwxyzuvwxyzuvwxyz"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"X", "abc"}, vector<string>{"Y", "def%X%ghi"}, vector<string>{"Z", "jkl%Y%mno"}, vector<string>{"W", "pqr%Z%stu"}, vector<string>{"V", "vwx%W%yz"}}, "%X%_%Y%_%Z%_%W%_%V%") == "abc_defabcghi_jkldefabcghimno_pqrjkldefabcghimnostu_vwxpqrjkldefabcghimnostuyz"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"Y", "%Z%abc"}, vector<string>{"Z", "%A%%B%"}, vector<string>{"A", "def"}, vector<string>{"B", "ghi"}, vector<string>{"C", "%Y%%A%"}, vector<string>{"D", "jkl"}}, "%C%_%D%_%Y%_%Z%") == "defghiabcdef_jkl_defghiabc_defghi"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "bce"}, vector<string>{"B", "ace"}, vector<string>{"C", "abc%B%"}, vector<string>{"D", "%C%_%A%"}, vector<string>{"E", "%B%_%D%"}, vector<string>{"F", "%E%_%C%"}}, "%F%") == "ace_abcace_bce_abcace"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"I", "mno"}, vector<string>{"J", "pqr"}, vector<string>{"K", "stu%I%"}, vector<string>{"L", "%J%%K%"}, vector<string>{"M", "vwx%L%"}}, "%M%") == "vwxpqrstumno"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"M", "abc"}, vector<string>{"N", "def"}, vector<string>{"O", "ghi%N%"}, vector<string>{"P", "jkl%O%"}, vector<string>{"Q", "%P%_%M%"}, vector<string>{"R", "%Q%_%N%"}}, "%R%") == "jklghidef_abc_def"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "abc%F%def"}, vector<string>{"B", "ghi%J%klm"}, vector<string>{"C", "nop%K%qr"}, vector<string>{"D", "stu"}, vector<string>{"E", "%A%%B%"}, vector<string>{"F", "%D%vwx"}, vector<string>{"G", "%E%%C%"}, vector<string>{"H", "yz"}, vector<string>{"I", "%H%abc"}, vector<string>{"J", "%I%def"}, vector<string>{"K", "%J%ghi"}}, "%E%_%G%") == "abcstuvwxdefghiyzabcdefklm_abcstuvwxdefghiyzabcdefklmnopyzabcdefghiqr"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"Y", "abc"}, vector<string>{"Z", "def%Y%"}, vector<string>{"A", "ghi%Z%"}, vector<string>{"B", "jkl%A%"}, vector<string>{"C", "mno%B%"}, vector<string>{"D", "%C%_%A%"}}, "%D%") == "mnojklghidefabc_ghidefabc"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"A", "def%G%"}, vector<string>{"B", "ghi"}, vector<string>{"C", "jkl%G%"}, vector<string>{"D", "mno"}, vector<string>{"E", "pqr"}, vector<string>{"F", "stu%G%"}, vector<string>{"G", "abc"}}, "%A%_%B%_%C%_%D%_%E%_%F%") == "defabc_ghi_jklabc_mno_pqr_stuabc"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"E", "%F%"}, vector<string>{"F", "%G%"}, vector<string>{"G", "xyz"}, vector<string>{"H", "%E%_%F%_%G%"}}, "%H%") == "xyz_xyz_xyz"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"K", "klm"}, vector<string>{"L", "nop"}, vector<string>{"M", "qrs"}, vector<string>{"N", "%K%%L%"}, vector<string>{"O", "%M%%M%"}, vector<string>{"P", "%N%%O%"}, vector<string>{"Q", "%P%%P%"}}, "%K%_%L%_%M%_%N%_%O%_%P%_%Q%") == "klm_nop_qrs_klmnop_qrsqrs_klmnopqrsqrs_klmnopqrsqrsklmnopqrsqrs"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"N", "opq"}, vector<string>{"O", "rst"}, vector<string>{"P", "%N%%O%"}, vector<string>{"Q", "%P%uvw"}, vector<string>{"R", "xyz%Q%"}}, "%R%") == "xyzopqrstuvw"));
    assert((sol.applySubstitutions(vector<vector<string>>{vector<string>{"G", "ghi"}, vector<string>{"H", "%I%jkl"}, vector<string>{"I", "mnop"}, vector<string>{"J", "%G%%H%"}, vector<string>{"K", "qrst"}, vector<string>{"L", "%K%uvw"}}, "%J%_%L%") == "ghimnopjkl_qrstuvw"));

    cout << "All tests passed for apply-substitutions" << endl;
    return 0;
}
