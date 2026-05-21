**LINE 10**

**EXPLANATION:** The condition `if (num==0)` is wrong — it returns `true` when the balance hits exactly zero, but the function is named `below_zero` and should return `true` only when the balance goes **negative** (i.e., `num < 0`). A balance of zero is not below zero, so this will produce false positives.

------------------------------------------------------------------------------------

**LINE 18**
**EXPLANATION:** The function returns `msum/avg` (dividing by the mean), but Mean Absolute Deviation is defined as the average of the absolute deviations, so it should return `msum/numbers.size()`.

------------------------------------------------------------------------------------

**LINE 9:** The first element `numbers[0]` is never added to `out` before the loop begins. The loop starts at index 1 and only pushes the delimiter followed by `numbers[i]`, so the output is missing the first element entirely (e.g., for input `[1,2,3]`, output would be `[d,2,d,3]` instead of `[1,d,2,d,3]`).

------------------------------------------------------------------------------------

**LINE 8**
**EXPLANATION:** `product` is initialized to `0` instead of `1`, so the product will always be `0` regardless of the input (since any number multiplied by 0 is 0). It should be initialized to `1` (the multiplicative identity).

------------------------------------------------------------------------------------

**LINE 12:** `out.push_back(numbers[i])` should be `out.push_back(max)`.

The function appends the original element instead of the current running maximum, so the output is just a copy of the input rather than the rolling max sequence.

**LINE 9:** `int max=0` causes incorrect results when all input values are negative.

The initial max is hardcoded to 0, so if every number is negative, the running maximum will incorrectly remain 0 instead of reflecting the true maximum seen so far. It should be initialized to `INT_MIN` (or `numbers[0]` with a bounds check).

------------------------------------------------------------------------------------

NO BUGS

------------------------------------------------------------------------------------

LINE 12: a=a%b; executed before checking if b is zero, and more critically, after the swap ensures a >= b, the modulo is applied — but if a == b, then a%b == 0 and the next iteration returns correctly. However, if either input is 0 initially (e.g. b=0), the swap may leave b=0 and a%b causes division by zero (undefined behaviour).
LINE 9–11 (swap logic) + LINE 12: After swapping so a >= b, computing a = a % b is correct for one step, but the result is assigned back to a and the loop continues — this logic is actually correct for the Euclidean algorithm when both inputs are positive. The real bug is the missing base case for zero inputs: if b == 0 before the swap, the swap puts 0 into b, and a % 0 is undefined behaviour/crash.

------------------------------------------------------------------------------------

NO BUGS

------------------------------------------------------------------------------------

**LINE 13**
**EXPLANATION:** If `numbers` has fewer than 2 elements, the loop never executes and `out` remains empty. Accessing `out[0]` and `out[1]` on the swap check then causes undefined behaviour (out-of-bounds access on an empty vector).

------------------------------------------------------------------------------------

**LINE 13:** The division `(max - min)` will be zero when all elements are equal (or when only one element exists), causing a division-by-zero and producing `NaN` or `inf` values. There is no guard for this case.

**LINE 8:** The hardcoded initial values `min=100000` and `max=-100000` will produce wrong results if all input values exceed 100000 or are all below -100000. Using `numbers[0]` as the initial value for both, or `std::numeric_limits<float>::max/lowest()`, would be correct.

------------------------------------------------------------------------------------
