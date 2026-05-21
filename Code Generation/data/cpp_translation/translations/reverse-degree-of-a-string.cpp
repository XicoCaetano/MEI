// task_id: reverse-degree-of-a-string
// difficulty: Easy

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
    int reverseDegree(string s) {
        long long ans = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            int x = 26 - (s[i] - 'a');
            ans += (long long)(i + 1) * x;
        }
        return (int)ans;
    }
};

int main() {
    Solution sol;

    assert((sol.reverseDegree("zzzz") == 10));
    assert((sol.reverseDegree("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz") == 15678));
    assert((sol.reverseDegree("world") == 230));
    assert((sol.reverseDegree("abcdefghijklmnopqrstuvwxyz") == 3276));
    assert((sol.reverseDegree("z") == 1));
    assert((sol.reverseDegree("degree") == 405));
    assert((sol.reverseDegree("abc") == 148));
    assert((sol.reverseDegree("reverse") == 403));
    assert((sol.reverseDegree("aaa") == 156));
    assert((sol.reverseDegree("zzz") == 6));
    assert((sol.reverseDegree("zyxwvutsrqponmlkjihgfedcba") == 6201));
    assert((sol.reverseDegree("a") == 26));
    assert((sol.reverseDegree("zaza") == 160));
    assert((sol.reverseDegree("hello") == 228));
    assert((sol.reverseDegree("aaabbbccc") == 1107));
    assert((sol.reverseDegree("abcdefghijklmnopqrstuvwxyzzxywvutsrqponmlkjihgfedcba") == 18602));
    assert((sol.reverseDegree("thisisaverylongstringthatweneedtocheck") == 11902));
    assert((sol.reverseDegree("abcdefghijabcdefghijabcdefghijabcdefghij") == 17300));
    assert((sol.reverseDegree("letsdothisoverandover") == 3275));
    assert((sol.reverseDegree("repeatedcharactersss") == 3224));
    assert((sol.reverseDegree("complex") == 362));
    assert((sol.reverseDegree("abracadabra") == 1453));
    assert((sol.reverseDegree("pythonprogramming") == 2314));
    assert((sol.reverseDegree("uniquecharacters") == 2168));
    assert((sol.reverseDegree("randomstringswithdifferentcharactersareincludedhere") == 22682));
    assert((sol.reverseDegree("thisisareallylongstringwithvariouscharacters") == 14440));
    assert((sol.reverseDegree("quickbrownfoxjumpsoverthelazydog") == 7059));
    assert((sol.reverseDegree("python") == 250));
    assert((sol.reverseDegree("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 1711));
    assert((sol.reverseDegree("aquickbrownfoxjumpsoverthelazydog") == 7509));
    assert((sol.reverseDegree("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 1485));
    assert((sol.reverseDegree("abcdabcdabcd") == 1896));
    assert((sol.reverseDegree("algorithms") == 724));
    assert((sol.reverseDegree("exampletestcase") == 1940));
    assert((sol.reverseDegree("reversealphabetcalculationsarefun") == 9042));
    assert((sol.reverseDegree("thisisareallylongstringthatweneedtocalculatereversedegree") == 26964));
    assert((sol.reverseDegree("qwertypoiasdfghjklzxcvbnm") == 4708));
    assert((sol.reverseDegree("abacaxabacax") == 1576));
    assert((sol.reverseDegree("loonyspoons") == 684));
    assert((sol.reverseDegree("hellothere") == 880));
    assert((sol.reverseDegree("thisisareallylongstringwithsomerepeatedcharacters") == 19494));
    assert((sol.reverseDegree("pythonisfun") == 832));
    assert((sol.reverseDegree("programmingisfun") == 1980));
    assert((sol.reverseDegree("qwen") == 136));
    assert((sol.reverseDegree("alibabacloud") == 1461));
    assert((sol.reverseDegree("reversedegree") == 1634));
    assert((sol.reverseDegree("mississippi") == 851));
    assert((sol.reverseDegree("testcase") == 611));
    assert((sol.reverseDegree("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz") == 12753));
    assert((sol.reverseDegree("abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba") == 18226));
    assert((sol.reverseDegree("programming") == 1068));
    assert((sol.reverseDegree("multiplewordstringexample") == 4768));
    assert((sol.reverseDegree("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 1275));
    assert((sol.reverseDegree("thequickbrownfoxjumpsoverthelazydog") == 8442));
    assert((sol.reverseDegree("zzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 406));

    cout << "All tests passed for reverse-degree-of-a-string" << endl;
    return 0;
}
