// task_id: minimum-operations-to-make-array-elements-zero
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
    long long getOperations(long long n) {
        long long res = 0;
        long long ops = 0;
        long long powerOfFour = 1;
        while (powerOfFour <= n) {
            long long l = powerOfFour;
            long long r = min(n, powerOfFour * 4 - 1);
            ops += 1;
            res += (r - l + 1) * ops;
            powerOfFour *= 4;
        }
        return res;
    }
    long long minOperations(vector<vector<long long>> queries) {
        long long total = 0;
        for (auto& q : queries) {
            long long l = q[0], r = q[1];
            total += (getOperations(r) - getOperations(l - 1) + 1) / 2;
        }
        return total;
    }
};

int main() {
    Solution sol;

    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{2LL, 4LL}}) == 3LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{10LL, 20LL}, vector<long long>{20LL, 30LL}, vector<long long>{30LL, 40LL}}) == 48LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{500000000LL, 1000000000LL}}) == 11071043045LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{100LL, 1000LL}, vector<long long>{1000LL, 10000LL}}) == 32279LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{10LL, 20LL}}) == 23LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{5LL, 5LL}, vector<long long>{10LL, 10LL}, vector<long long>{15LL, 15LL}}) == 3LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{1LL, 1000000000LL}}) == 14642086074LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{2LL, 6LL}}) == 4LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{2LL, 999999999LL}}) == 14642086066LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 3LL}, vector<long long>{4LL, 6LL}, vector<long long>{7LL, 9LL}}) == 8LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000LL}, vector<long long>{500000LL, 1000000LL}}) == 7325248LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{5LL, 5LL}, vector<long long>{10LL, 10LL}}) == 2LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{10LL, 20LL}, vector<long long>{20LL, 30LL}}) == 40LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 500000LL}, vector<long long>{500001LL, 1000000LL}, vector<long long>{1000001LL, 1500000LL}, vector<long long>{1500001LL, 2000000LL}}) == 10300956LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10000LL}, vector<long long>{20000LL, 30000LL}, vector<long long>{40000LL, 50000LL}, vector<long long>{60000LL, 70000LL}, vector<long long>{80000LL, 90000LL}}) == 199523LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100000000LL, 200000000LL}, vector<long long>{200000000LL, 300000000LL}, vector<long long>{300000000LL, 400000000LL}, vector<long long>{400000000LL, 500000000LL}, vector<long long>{500000000LL, 600000000LL}, vector<long long>{600000000LL, 700000000LL}, vector<long long>{700000000LL, 800000000LL}, vector<long long>{800000000LL, 900000000LL}, vector<long long>{900000000LL, 1000000000LL}}) == 6665782343LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{2LL, 20LL}, vector<long long>{3LL, 30LL}, vector<long long>{4LL, 40LL}, vector<long long>{5LL, 50LL}, vector<long long>{6LL, 60LL}, vector<long long>{7LL, 70LL}, vector<long long>{8LL, 80LL}, vector<long long>{9LL, 90LL}, vector<long long>{10LL, 100LL}}) == 751LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000LL}, vector<long long>{1000001LL, 2000000LL}, vector<long long>{2000001LL, 3000000LL}}) == 15800956LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{500000LL, 750000LL}, vector<long long>{750001LL, 1000000LL}, vector<long long>{1LL, 499999LL}}) == 4825243LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{2LL, 3LL}, vector<long long>{3LL, 4LL}, vector<long long>{4LL, 5LL}, vector<long long>{5LL, 6LL}, vector<long long>{6LL, 7LL}, vector<long long>{7LL, 8LL}, vector<long long>{8LL, 9LL}, vector<long long>{9LL, 10LL}}) == 16LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{10LL, 100LL}, vector<long long>{200LL, 300LL}, vector<long long>{400LL, 500LL}, vector<long long>{600LL, 700LL}, vector<long long>{800LL, 900LL}}) == 1136LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{101LL, 200LL}, vector<long long>{201LL, 300LL}, vector<long long>{301LL, 400LL}, vector<long long>{401LL, 500LL}, vector<long long>{501LL, 600LL}, vector<long long>{601LL, 700LL}, vector<long long>{701LL, 800LL}, vector<long long>{801LL, 900LL}, vector<long long>{901LL, 1000LL}}) == 2333LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 500LL}, vector<long long>{501LL, 1000LL}, vector<long long>{1001LL, 1500LL}, vector<long long>{1501LL, 2000LL}, vector<long long>{2001LL, 2500LL}, vector<long long>{2501LL, 3000LL}}) == 8321LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}}) == 7321043037LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000LL}, vector<long long>{1000LL, 2000LL}, vector<long long>{2000LL, 3000LL}, vector<long long>{3000LL, 4000LL}, vector<long long>{4000LL, 5000LL}, vector<long long>{5000LL, 6000LL}, vector<long long>{6000LL, 7000LL}, vector<long long>{7000LL, 8000LL}, vector<long long>{8000LL, 9000LL}, vector<long long>{9000LL, 10000LL}}) == 32305LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{1LL, 500000000LL}, vector<long long>{500000001LL, 1000000000LL}}) == 14642086074LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 333333333LL}, vector<long long>{333333334LL, 666666666LL}, vector<long long>{666666667LL, 999999999LL}}) == 7321043031LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 9LL}, vector<long long>{2LL, 18LL}, vector<long long>{3LL, 27LL}, vector<long long>{4LL, 36LL}, vector<long long>{5LL, 45LL}, vector<long long>{6LL, 54LL}, vector<long long>{7LL, 63LL}, vector<long long>{8LL, 72LL}, vector<long long>{9LL, 81LL}, vector<long long>{10LL, 90LL}}) == 652LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{2LL, 3LL}, vector<long long>{3LL, 5LL}, vector<long long>{5LL, 7LL}, vector<long long>{7LL, 9LL}, vector<long long>{9LL, 11LL}}) == 13LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{2LL, 200LL}, vector<long long>{3LL, 300LL}, vector<long long>{4LL, 400LL}, vector<long long>{5LL, 500LL}, vector<long long>{6LL, 600LL}, vector<long long>{7LL, 700LL}, vector<long long>{8LL, 800LL}, vector<long long>{9LL, 900LL}, vector<long long>{10LL, 1000LL}}) == 12146LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000LL}, vector<long long>{1001LL, 2000LL}, vector<long long>{2001LL, 3000LL}, vector<long long>{3001LL, 4000LL}, vector<long long>{4001LL, 5000LL}, vector<long long>{5001LL, 6000LL}, vector<long long>{6001LL, 7000LL}, vector<long long>{7001LL, 8000LL}, vector<long long>{8001LL, 9000LL}, vector<long long>{9001LL, 10000LL}}) == 32274LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{500000000LL, 750000000LL}, vector<long long>{750000001LL, 1000000000LL}}) == 3750000008LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{3LL, 4LL}, vector<long long>{5LL, 6LL}, vector<long long>{7LL, 8LL}, vector<long long>{9LL, 10LL}, vector<long long>{11LL, 12LL}, vector<long long>{13LL, 14LL}, vector<long long>{15LL, 16LL}, vector<long long>{17LL, 18LL}, vector<long long>{19LL, 20LL}}) == 22LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100000LL}, vector<long long>{2LL, 200000LL}, vector<long long>{3LL, 300000LL}, vector<long long>{4LL, 400000LL}, vector<long long>{5LL, 500000LL}}) == 6738351LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10000000LL}, vector<long long>{10000001LL, 20000000LL}, vector<long long>{20000001LL, 30000000LL}, vector<long long>{30000001LL, 40000000LL}}) == 248815197LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 3LL}, vector<long long>{4LL, 7LL}, vector<long long>{8LL, 11LL}, vector<long long>{12LL, 15LL}, vector<long long>{16LL, 19LL}, vector<long long>{20LL, 23LL}, vector<long long>{24LL, 27LL}, vector<long long>{28LL, 31LL}, vector<long long>{32LL, 35LL}, vector<long long>{36LL, 39LL}, vector<long long>{40LL, 43LL}, vector<long long>{44LL, 47LL}, vector<long long>{48LL, 51LL}, vector<long long>{52LL, 55LL}, vector<long long>{56LL, 59LL}, vector<long long>{60LL, 63LL}, vector<long long>{64LL, 67LL}, vector<long long>{68LL, 71LL}, vector<long long>{72LL, 75LL}, vector<long long>{76LL, 79LL}, vector<long long>{80LL, 83LL}, vector<long long>{84LL, 87LL}, vector<long long>{88LL, 91LL}, vector<long long>{92LL, 95LL}, vector<long long>{96LL, 99LL}}) == 158LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{20LL, 30LL}, vector<long long>{30LL, 40LL}, vector<long long>{40LL, 50LL}, vector<long long>{50LL, 60LL}, vector<long long>{60LL, 70LL}, vector<long long>{70LL, 80LL}, vector<long long>{80LL, 90LL}, vector<long long>{90LL, 100LL}}) == 163LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}}) == 7321043037LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{2LL, 20LL}, vector<long long>{3LL, 30LL}, vector<long long>{4LL, 40LL}, vector<long long>{5LL, 50LL}, vector<long long>{6LL, 60LL}, vector<long long>{7LL, 70LL}, vector<long long>{8LL, 80LL}, vector<long long>{9LL, 90LL}, vector<long long>{10LL, 100LL}}) == 751LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{500000000LL, 500000010LL}, vector<long long>{500000010LL, 500000020LL}, vector<long long>{500000020LL, 500000030LL}, vector<long long>{500000030LL, 500000040LL}, vector<long long>{500000040LL, 500000050LL}}) == 415LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 500000LL}, vector<long long>{500001LL, 1000000LL}, vector<long long>{1000001LL, 1500000LL}, vector<long long>{1500001LL, 2000000LL}, vector<long long>{2000001LL, 2500000LL}, vector<long long>{2500001LL, 3000000LL}, vector<long long>{3000001LL, 3500000LL}, vector<long long>{3500001LL, 4000000LL}, vector<long long>{4000001LL, 4500000LL}, vector<long long>{4500001LL, 5000000LL}}) == 27203805LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 31622LL}, vector<long long>{31623LL, 63245LL}, vector<long long>{63246LL, 94868LL}, vector<long long>{94869LL, 126491LL}, vector<long long>{126492LL, 158114LL}}) == 667829LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{500000000LL, 1000000000LL}}) == 11071043045LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{1LL, 20LL}, vector<long long>{1LL, 30LL}, vector<long long>{1LL, 40LL}, vector<long long>{1LL, 50LL}, vector<long long>{1LL, 60LL}, vector<long long>{1LL, 70LL}, vector<long long>{1LL, 80LL}, vector<long long>{1LL, 90LL}, vector<long long>{1LL, 100LL}}) == 784LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100LL, 200LL}, vector<long long>{200LL, 300LL}, vector<long long>{300LL, 400LL}, vector<long long>{400LL, 500LL}, vector<long long>{500LL, 600LL}}) == 1186LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{11LL, 20LL}, vector<long long>{21LL, 30LL}, vector<long long>{31LL, 40LL}, vector<long long>{41LL, 50LL}, vector<long long>{51LL, 60LL}, vector<long long>{61LL, 70LL}, vector<long long>{71LL, 80LL}, vector<long long>{81LL, 90LL}, vector<long long>{91LL, 100LL}}) == 161LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{200LL, 250LL}, vector<long long>{350LL, 400LL}, vector<long long>{550LL, 600LL}, vector<long long>{750LL, 800LL}, vector<long long>{950LL, 1000LL}}) == 774LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{4LL, 8LL}, vector<long long>{16LL, 32LL}, vector<long long>{32LL, 64LL}, vector<long long>{64LL, 128LL}, vector<long long>{128LL, 256LL}, vector<long long>{256LL, 512LL}, vector<long long>{512LL, 1024LL}, vector<long long>{1024LL, 2048LL}, vector<long long>{2048LL, 4096LL}}) == 11620LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 9LL}, vector<long long>{9LL, 81LL}, vector<long long>{81LL, 729LL}, vector<long long>{729LL, 6561LL}}) == 20243LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{2LL, 9LL}, vector<long long>{3LL, 8LL}, vector<long long>{4LL, 7LL}, vector<long long>{5LL, 6LL}}) == 28LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{50LL, 150LL}, vector<long long>{100LL, 200LL}, vector<long long>{150LL, 250LL}, vector<long long>{200LL, 300LL}}) == 984LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100000LL}, vector<long long>{200000LL, 300000LL}, vector<long long>{300000LL, 400000LL}, vector<long long>{400000LL, 500000LL}, vector<long long>{500000LL, 600000LL}}) == 2375262LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{101LL, 200LL}, vector<long long>{201LL, 300LL}, vector<long long>{301LL, 400LL}, vector<long long>{401LL, 500LL}}) == 1083LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1LL}, vector<long long>{2LL, 2LL}, vector<long long>{3LL, 3LL}, vector<long long>{4LL, 4LL}, vector<long long>{5LL, 5LL}, vector<long long>{6LL, 6LL}, vector<long long>{7LL, 7LL}, vector<long long>{8LL, 8LL}, vector<long long>{9LL, 9LL}, vector<long long>{10LL, 10LL}}) == 10LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 3LL}, vector<long long>{2LL, 5LL}, vector<long long>{3LL, 7LL}, vector<long long>{4LL, 9LL}, vector<long long>{5LL, 11LL}, vector<long long>{6LL, 13LL}, vector<long long>{7LL, 15LL}, vector<long long>{8LL, 17LL}, vector<long long>{9LL, 19LL}, vector<long long>{10LL, 21LL}}) == 79LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{50LL, 150LL}, vector<long long>{100LL, 200LL}, vector<long long>{150LL, 250LL}, vector<long long>{200LL, 300LL}, vector<long long>{250LL, 350LL}, vector<long long>{300LL, 400LL}, vector<long long>{350LL, 450LL}, vector<long long>{400LL, 500LL}, vector<long long>{450LL, 500LL}}) == 2121LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10000LL}, vector<long long>{20000LL, 30000LL}, vector<long long>{40000LL, 50000LL}, vector<long long>{60000LL, 70000LL}, vector<long long>{70000LL, 80000LL}, vector<long long>{80000LL, 90000LL}, vector<long long>{90000LL, 100000LL}}) == 289533LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100000000LL, 200000000LL}, vector<long long>{300000000LL, 400000000LL}, vector<long long>{500000000LL, 600000000LL}, vector<long long>{700000000LL, 800000000LL}, vector<long long>{900000000LL, 1000000000LL}}) == 3700000039LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1LL}, vector<long long>{2LL, 2LL}, vector<long long>{3LL, 3LL}, vector<long long>{4LL, 4LL}, vector<long long>{5LL, 5LL}, vector<long long>{6LL, 6LL}, vector<long long>{7LL, 7LL}, vector<long long>{8LL, 8LL}, vector<long long>{9LL, 9LL}, vector<long long>{10LL, 10LL}}) == 10LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{2LL, 3LL}, vector<long long>{3LL, 4LL}, vector<long long>{4LL, 5LL}, vector<long long>{5LL, 6LL}, vector<long long>{6LL, 7LL}, vector<long long>{7LL, 8LL}, vector<long long>{8LL, 9LL}, vector<long long>{9LL, 10LL}, vector<long long>{10LL, 11LL}, vector<long long>{11LL, 12LL}, vector<long long>{12LL, 13LL}, vector<long long>{13LL, 14LL}, vector<long long>{14LL, 15LL}, vector<long long>{15LL, 16LL}, vector<long long>{16LL, 17LL}, vector<long long>{17LL, 18LL}, vector<long long>{18LL, 19LL}, vector<long long>{19LL, 20LL}, vector<long long>{20LL, 21LL}}) == 44LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{10LL, 2000000LL}, vector<long long>{2000000LL, 3000000LL}, vector<long long>{3000000LL, 4000000LL}, vector<long long>{4000000LL, 5000000LL}, vector<long long>{5000000LL, 6000000LL}}) == 33203820LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{1000000LL, 1000000000LL}}) == 14637260837LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000LL}, vector<long long>{1001LL, 2000LL}, vector<long long>{2001LL, 3000LL}, vector<long long>{3001LL, 4000LL}, vector<long long>{4001LL, 5000LL}}) == 14774LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{1LL, 1LL}, vector<long long>{999999999LL, 1000000000LL}}) == 7321043053LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 5LL}, vector<long long>{6LL, 10LL}, vector<long long>{11LL, 15LL}, vector<long long>{16LL, 20LL}, vector<long long>{21LL, 25LL}, vector<long long>{26LL, 30LL}, vector<long long>{31LL, 35LL}, vector<long long>{36LL, 40LL}, vector<long long>{41LL, 45LL}, vector<long long>{46LL, 50LL}}) == 70LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{500000000LL, 500000010LL}, vector<long long>{500000010LL, 500000020LL}, vector<long long>{500000020LL, 500000030LL}, vector<long long>{500000030LL, 500000040LL}, vector<long long>{500000040LL, 500000050LL}}) == 415LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 500000LL}, vector<long long>{250000LL, 750000LL}, vector<long long>{500000LL, 1000000LL}, vector<long long>{750000LL, 1250000LL}}) == 9919899LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{500LL, 1000LL}, vector<long long>{1500LL, 2000LL}, vector<long long>{2500LL, 3000LL}, vector<long long>{3500LL, 4000LL}, vector<long long>{4500LL, 5000LL}}) == 7516LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{50LL, 150LL}, vector<long long>{100LL, 200LL}, vector<long long>{150LL, 250LL}, vector<long long>{200LL, 300LL}, vector<long long>{250LL, 350LL}, vector<long long>{300LL, 400LL}}) == 1487LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100LL, 200LL}, vector<long long>{150LL, 250LL}, vector<long long>{200LL, 300LL}, vector<long long>{250LL, 350LL}, vector<long long>{300LL, 400LL}}) == 1132LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{3LL, 5LL}, vector<long long>{7LL, 10LL}, vector<long long>{11LL, 15LL}, vector<long long>{16LL, 20LL}}) == 21LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 200LL}, vector<long long>{50LL, 150LL}, vector<long long>{100LL, 300LL}, vector<long long>{250LL, 400LL}}) == 1355LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{2LL, 3LL}, vector<long long>{3LL, 4LL}, vector<long long>{4LL, 5LL}, vector<long long>{5LL, 6LL}, vector<long long>{6LL, 7LL}, vector<long long>{7LL, 8LL}, vector<long long>{8LL, 9LL}, vector<long long>{9LL, 10LL}}) == 16LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{3LL, 6LL}, vector<long long>{7LL, 10LL}, vector<long long>{11LL, 14LL}, vector<long long>{15LL, 18LL}}) == 19LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 10LL}, vector<long long>{2LL, 11LL}, vector<long long>{3LL, 12LL}, vector<long long>{4LL, 13LL}, vector<long long>{5LL, 14LL}, vector<long long>{6LL, 15LL}, vector<long long>{7LL, 16LL}, vector<long long>{8LL, 17LL}, vector<long long>{9LL, 18LL}, vector<long long>{10LL, 19LL}}) == 104LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{101LL, 200LL}, vector<long long>{201LL, 300LL}, vector<long long>{301LL, 400LL}, vector<long long>{401LL, 500LL}, vector<long long>{501LL, 600LL}, vector<long long>{601LL, 700LL}, vector<long long>{701LL, 800LL}, vector<long long>{801LL, 900LL}, vector<long long>{901LL, 1000LL}}) == 2333LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000LL}, vector<long long>{1000001LL, 2000000LL}, vector<long long>{2000001LL, 3000000LL}, vector<long long>{3000001LL, 4000000LL}, vector<long long>{4000001LL, 5000000LL}}) == 27203805LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100LL, 1000LL}, vector<long long>{200LL, 2000LL}, vector<long long>{300LL, 3000LL}, vector<long long>{400LL, 4000LL}, vector<long long>{500LL, 5000LL}}) == 39064LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100LL, 200LL}, vector<long long>{200LL, 300LL}, vector<long long>{300LL, 400LL}, vector<long long>{400LL, 500LL}, vector<long long>{500LL, 600LL}, vector<long long>{600LL, 700LL}, vector<long long>{700LL, 800LL}, vector<long long>{800LL, 900LL}, vector<long long>{900LL, 1000LL}}) == 2198LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{2LL, 3LL}, vector<long long>{3LL, 4LL}, vector<long long>{4LL, 5LL}, vector<long long>{5LL, 6LL}}) == 8LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 3LL}, vector<long long>{2LL, 4LL}, vector<long long>{3LL, 5LL}, vector<long long>{4LL, 6LL}, vector<long long>{5LL, 7LL}, vector<long long>{6LL, 8LL}, vector<long long>{7LL, 9LL}, vector<long long>{8LL, 10LL}, vector<long long>{9LL, 11LL}, vector<long long>{10LL, 12LL}}) == 28LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 9LL}, vector<long long>{10LL, 18LL}, vector<long long>{19LL, 27LL}, vector<long long>{28LL, 36LL}, vector<long long>{37LL, 45LL}, vector<long long>{46LL, 54LL}, vector<long long>{55LL, 63LL}, vector<long long>{64LL, 72LL}, vector<long long>{73LL, 81LL}, vector<long long>{82LL, 90LL}}) == 143LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 9LL}, vector<long long>{10LL, 18LL}, vector<long long>{19LL, 27LL}, vector<long long>{28LL, 36LL}, vector<long long>{37LL, 45LL}, vector<long long>{46LL, 54LL}, vector<long long>{55LL, 63LL}, vector<long long>{64LL, 72LL}, vector<long long>{73LL, 81LL}, vector<long long>{82LL, 90LL}, vector<long long>{91LL, 99LL}}) == 161LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000000LL}, vector<long long>{500000000LL, 750000000LL}}) == 9196043045LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2000000000LL}, vector<long long>{1000000000LL, 2000000000LL}, vector<long long>{500000000LL, 1500000000LL}, vector<long long>{1500000000LL, 2500000000LL}}) == 38960430326LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 5LL}, vector<long long>{2LL, 10LL}, vector<long long>{3LL, 15LL}, vector<long long>{4LL, 20LL}, vector<long long>{5LL, 25LL}, vector<long long>{6LL, 30LL}, vector<long long>{7LL, 35LL}, vector<long long>{8LL, 40LL}, vector<long long>{9LL, 45LL}, vector<long long>{10LL, 50LL}}) == 300LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1000LL, 2000LL}, vector<long long>{3000LL, 4000LL}, vector<long long>{5000LL, 6000LL}, vector<long long>{7000LL, 8000LL}, vector<long long>{9000LL, 10000LL}, vector<long long>{11000LL, 12000LL}, vector<long long>{13000LL, 14000LL}, vector<long long>{15000LL, 16000LL}, vector<long long>{17000LL, 18000LL}, vector<long long>{19000LL, 20000LL}}) == 35026LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000LL}, vector<long long>{501LL, 1500LL}, vector<long long>{1001LL, 2000LL}, vector<long long>{1501LL, 2500LL}, vector<long long>{2001LL, 3000LL}, vector<long long>{2501LL, 3500LL}}) == 17060LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100000000LL, 150000000LL}, vector<long long>{150000001LL, 200000000LL}, vector<long long>{200000001LL, 250000000LL}, vector<long long>{250000001LL, 300000000LL}}) == 1415782280LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{100LL, 200LL}, vector<long long>{200LL, 300LL}, vector<long long>{300LL, 400LL}, vector<long long>{400LL, 500LL}, vector<long long>{500LL, 600LL}, vector<long long>{600LL, 700LL}, vector<long long>{700LL, 800LL}, vector<long long>{800LL, 900LL}, vector<long long>{900LL, 1000LL}}) == 2198LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 3LL}, vector<long long>{4LL, 6LL}, vector<long long>{7LL, 9LL}, vector<long long>{10LL, 12LL}, vector<long long>{13LL, 15LL}, vector<long long>{16LL, 18LL}, vector<long long>{19LL, 21LL}}) == 24LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 2LL}, vector<long long>{2LL, 4LL}, vector<long long>{4LL, 8LL}, vector<long long>{8LL, 16LL}, vector<long long>{16LL, 32LL}, vector<long long>{32LL, 64LL}, vector<long long>{64LL, 128LL}}) == 224LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 100LL}, vector<long long>{101LL, 200LL}, vector<long long>{201LL, 300LL}, vector<long long>{301LL, 400LL}, vector<long long>{401LL, 500LL}}) == 1083LL));
    assert((sol.minOperations(vector<vector<long long>>{vector<long long>{1LL, 1000000LL}, vector<long long>{2000000LL, 3000000LL}, vector<long long>{3000000LL, 4000000LL}, vector<long long>{4000000LL, 5000000LL}, vector<long long>{5000000LL, 6000000LL}, vector<long long>{6000000LL, 7000000LL}, vector<long long>{7000000LL, 8000000LL}, vector<long long>{8000000LL, 9000000LL}, vector<long long>{9000000LL, 10000000LL}}) == 51728139LL));

    cout << "All tests passed for minimum-operations-to-make-array-elements-zero" << endl;
    return 0;
}
