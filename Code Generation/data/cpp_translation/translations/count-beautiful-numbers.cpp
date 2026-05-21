// task_id: count-beautiful-numbers
// difficulty: Hard

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
    long long count_le(long long n) {
        if (n <= 0) return 0;
        string s = to_string(n);
        int len = (int)s.size();
        // Encode key into a single long long: (((((i*2 + tight)*2 + isLeadingZero)*2 + hasZero)*100 + sum)*1000000000 + prod)
        // Actually use unordered_map<string, long long>
        unordered_map<long long, long long> memo;
        function<long long(int,int,int,int,int,long long)> dp =
            [&](int i, int tight, int isLeadingZero, int hasZero, int sum, long long prod) -> long long {
            if (i == len) {
                if (isLeadingZero) return 0;
                if (hasZero) return 1;
                return (prod % sum == 0) ? 1 : 0;
            }
            // Fast-path: free digits with hasZero already true.
            if (!isLeadingZero && hasZero && !tight) {
                long long pw = 1;
                for (int t = 0; t < len - i; ++t) pw *= 10;
                return pw;
            }
            long long key = ((((((long long)i * 2 + tight) * 2 + isLeadingZero) * 2 + hasZero) * 100 + sum) * 400000000LL) + prod;
            auto it = memo.find(key);
            if (it != memo.end()) return it->second;
            long long res = 0;
            int maxDigit = tight ? (s[i] - '0') : 9;
            for (int d = 0; d <= maxDigit; ++d) {
                int nextTight = tight && (d == maxDigit);
                int nextIsLeadingZero = isLeadingZero && d == 0;
                int nextHasZero = (!nextIsLeadingZero && d == 0) ? 1 : hasZero;
                long long nextProd = nextIsLeadingZero ? 1 : prod * d;
                res += dp(i + 1, nextTight, nextIsLeadingZero,
                          nextHasZero, sum + d, nextProd);
            }
            memo[key] = res;
            return res;
        };
        return dp(0, 1, 1, 0, 0, 1);
    }

    long long beautifulNumbers(int l, int r) {
        return count_le(r) - count_le((long long)l - 1);
    }
};

int main() {
    Solution sol;

    assert((sol.beautifulNumbers(999, 999) == 1LL));
    assert((sol.beautifulNumbers(1, 9) == 9LL));
    assert((sol.beautifulNumbers(900, 1000) == 35LL));
    assert((sol.beautifulNumbers(789, 890) == 35LL));
    assert((sol.beautifulNumbers(500, 5000) == 1800LL));
    assert((sol.beautifulNumbers(5, 50) == 13LL));
    assert((sol.beautifulNumbers(100, 200) == 32LL));
    assert((sol.beautifulNumbers(50, 100) == 9LL));
    assert((sol.beautifulNumbers(10, 20) == 2LL));
    assert((sol.beautifulNumbers(999, 1001) == 3LL));
    assert((sol.beautifulNumbers(1, 999999999) == 670349658LL));
    assert((sol.beautifulNumbers(990, 1000) == 3LL));
    assert((sol.beautifulNumbers(100000000, 100000000) == 1LL));
    assert((sol.beautifulNumbers(123, 456) == 110LL));
    assert((sol.beautifulNumbers(1, 1) == 1LL));
    assert((sol.beautifulNumbers(300, 500) == 70LL));
    assert((sol.beautifulNumbers(99999, 100001) == 2LL));
    assert((sol.beautifulNumbers(100, 150) == 19LL));
    assert((sol.beautifulNumbers(1, 15) == 10LL));
    assert((sol.beautifulNumbers(1000, 10000) == 3676LL));
    assert((sol.beautifulNumbers(111, 222) == 33LL));
    assert((sol.beautifulNumbers(1000, 1010) == 11LL));
    assert((sol.beautifulNumbers(50, 55) == 1LL));
    assert((sol.beautifulNumbers(100000, 200000) == 52892LL));
    assert((sol.beautifulNumbers(100000, 150000) == 29004LL));
    assert((sol.beautifulNumbers(999999, 1000001) == 2LL));
    assert((sol.beautifulNumbers(123456, 654321) == 288118LL));
    assert((sol.beautifulNumbers(1, 1000000) == 534358LL));
    assert((sol.beautifulNumbers(333333, 444444) == 59841LL));
    assert((sol.beautifulNumbers(90000000, 99999999) == 6259058LL));
    assert((sol.beautifulNumbers(123456789, 2147483647) == 1428531442LL));
    assert((sol.beautifulNumbers(7654321, 8765432) == 646518LL));
    assert((sol.beautifulNumbers(1000000, 10000000) == 5311175LL));
    assert((sol.beautifulNumbers(987654, 987664) == 3LL));
    assert((sol.beautifulNumbers(10000000, 10001000) == 1001LL));
    assert((sol.beautifulNumbers(10000000, 20000000) == 6285218LL));
    assert((sol.beautifulNumbers(999999990, 999999999) == 2LL));
    assert((sol.beautifulNumbers(999999, 999999) == 0LL));
    assert((sol.beautifulNumbers(888888, 999999) == 57963LL));
    assert((sol.beautifulNumbers(99999999, 100000000) == 1LL));
    assert((sol.beautifulNumbers(5000, 75000) == 33900LL));
    assert((sol.beautifulNumbers(1, 1000000000) == 670349659LL));
    assert((sol.beautifulNumbers(777777, 888888) == 58602LL));
    assert((sol.beautifulNumbers(987654321, 1000000000) == 7554239LL));
    assert((sol.beautifulNumbers(999999, 9999999) == 5311174LL));
    assert((sol.beautifulNumbers(500000, 510000) == 10001LL));
    assert((sol.beautifulNumbers(987654321, 987654321) == 1LL));
    assert((sol.beautifulNumbers(123456789, 234567890) == 73969442LL));
    assert((sol.beautifulNumbers(2000000, 2010000) == 10001LL));
    assert((sol.beautifulNumbers(100000, 1000000) == 486888LL));
    assert((sol.beautifulNumbers(10000000, 10000000) == 1LL));
    assert((sol.beautifulNumbers(555555555, 555555555) == 0LL));
    assert((sol.beautifulNumbers(1000000, 1001000) == 1001LL));
    assert((sol.beautifulNumbers(500000, 999999) == 270652LL));
    assert((sol.beautifulNumbers(100000000, 300000000) == 134174863LL));
    assert((sol.beautifulNumbers(1000000, 3000000) == 1175795LL));
    assert((sol.beautifulNumbers(456789, 456789123) == 304015671LL));
    assert((sol.beautifulNumbers(123456, 123567) == 46LL));
    assert((sol.beautifulNumbers(56789, 567890) == 276722LL));
    assert((sol.beautifulNumbers(88888888, 99999999) == 6902887LL));
    assert((sol.beautifulNumbers(50000000, 60000000) == 6522427LL));
    assert((sol.beautifulNumbers(500000000, 501000000) == 1000001LL));
    assert((sol.beautifulNumbers(1234567, 12345678) == 6951395LL));
    assert((sol.beautifulNumbers(12345, 67890) == 26696LL));
    assert((sol.beautifulNumbers(98765432, 98765432) == 0LL));
    assert((sol.beautifulNumbers(8000000, 8100000) == 100001LL));
    assert((sol.beautifulNumbers(456789, 987654) == 286642LL));
    assert((sol.beautifulNumbers(1234567, 8765432) == 4438756LL));
    assert((sol.beautifulNumbers(555555, 666666) == 61137LL));
    assert((sol.beautifulNumbers(5000000, 6000000) == 609303LL));
    assert((sol.beautifulNumbers(50000, 55000) == 2738LL));
    assert((sol.beautifulNumbers(1000000, 1010000) == 10001LL));
    assert((sol.beautifulNumbers(800000, 900000) == 53367LL));
    assert((sol.beautifulNumbers(500000000, 550000000) == 36195523LL));
    assert((sol.beautifulNumbers(500000, 550000) == 30521LL));
    assert((sol.beautifulNumbers(10000000, 100000000) == 57110376LL));
    assert((sol.beautifulNumbers(111111, 222222) == 58091LL));
    assert((sol.beautifulNumbers(100000000, 111111111) == 11111111LL));
    assert((sol.beautifulNumbers(800000, 801000) == 1001LL));
    assert((sol.beautifulNumbers(100000000, 200000000) == 66911398LL));
    assert((sol.beautifulNumbers(500000, 600000) == 55997LL));
    assert((sol.beautifulNumbers(999900, 1000100) == 124LL));
    assert((sol.beautifulNumbers(123456789, 123456789) == 1LL));
    assert((sol.beautifulNumbers(100000, 999999) == 486887LL));
    assert((sol.beautifulNumbers(111111111, 222222222) == 73867777LL));
    assert((sol.beautifulNumbers(8000000, 8999999) == 583871LL));
    assert((sol.beautifulNumbers(987654, 987654) == 0LL));
    assert((sol.beautifulNumbers(999000, 1001000) == 1335LL));
    assert((sol.beautifulNumbers(123, 987654321) == 662795385LL));
    assert((sol.beautifulNumbers(100000, 500000) == 216236LL));
    assert((sol.beautifulNumbers(77777777, 88888888) == 6956761LL));
    assert((sol.beautifulNumbers(5000000, 5010000) == 10001LL));

    cout << "All tests passed for count-beautiful-numbers" << endl;
    return 0;
}
