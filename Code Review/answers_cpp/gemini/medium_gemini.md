- **LINE(s) affected**: 12
- **EXPLANATION**: The condition `num == 0` is incorrect for a function named `below_zero`. It should check if `num < 0` to determine if the balance has actually dropped below zero.

------------------------------------------------------------------------------------

## Code Review: `mean_absolute_deviation`

The following issues were identified during the review:

---

*   **LINE:** 15
*   **EXPLANATION:** The function uses `abs()` (from `stdlib.h`), which is for integers. Using it on float values will cause them to be cast to integers, losing decimal precision and leading to incorrect calculations. Use `fabs()` or `std::abs()` instead.

*   **LINE:** 16
*   **EXPLANATION:** The function returns `msum / avg`, which is not the formula for Mean Absolute Deviation. It should return `msum / numbers.size()` to provide the average of the absolute differences.

*   **LINE:** 11 & 16
*   **EXPLANATION:** There is no check for an empty vector. If `numbers` is empty, `numbers.size()` is zero, leading to a division by zero when calculating `avg` or the final result.

------------------------------------------------------------------------------------

- **LINE(s):** 8
- **EXPLANATION:** The function fails to include the first element of the `numbers` vector in the output because the loop starts at index 1.

- **LINE(s):** 8-13
- **EXPLANATION:** If the input `numbers` vector is empty, the function returns an empty vector, which is correct; however, for any non-empty vector, it completely omits the first element and begins the result with a delimiter.

- **LINE(s):** 8
- **EXPLANATION:** On some systems, `numbers.size()` (which is unsigned) minus 1 could wrap around to a very large positive integer if the vector is empty, though in this specific `i < numbers.size()` comparison, it simply prevents the loop from running.

------------------------------------------------------------------------------------

### Code Review Report

*   **LINE:** 8
    **EXPLANATION:** The variable `product` is initialized to `0`. Since any number multiplied by zero is zero, the loop will always return a product of `0` regardless of the input. It should be initialized to `1`.

*   **LINE:** 11
    **EXPLANATION:** The function logic fails on an empty input vector because it would return `{0, 0}`. While the sum is correct, the identity for an empty product is typically `1`.

*   **LINE:** 10 & 11
    **EXPLANATION:** There is a high risk of integer overflow for the `product` variable (and potentially `sum`) as `int` has a limited range. For a product calculation, `long long` or overflow checks are usually required for robust code.

------------------------------------------------------------------------------------

### Code Review: `rolling_max`

*   **LINE(s):** 9
*   **EXPLANATION:** The variable `max` is initialized to `0`, which causes incorrect behavior if the input vector contains only negative numbers. It should be initialized to the first element of the vector or `INT_MIN`.

*   **LINE(s):** 12
*   **EXPLANATION:** The function pushes the current element `numbers[i]` onto the output vector instead of the running `max`. This results in the function simply returning a copy of the input vector.

*   **LINE(s):** 10
*   **EXPLANATION:** Using `numbers.size()` in the loop comparison can lead to signed/unsigned mismatch warnings or issues with empty vectors, as `size()` returns `size_t`.

------------------------------------------------------------------------------------

NO BUGS

------------------------------------------------------------------------------------

### Code Review: `greatest_common_divisor`

*   **LINE(s):** 13
*   **EXPLANATION:** If the input `b` is 0, the expression `a%b` will cause a division by zero error, leading to a runtime crash.

---

*   **LINE(s):** 13
*   **EXPLANATION:** If both `a` and `b` are 0, the function enters an infinite loop or crashes before reaching a base case.

---

*   **LINE(s):** 11, 13
*   **EXPLANATION:** The modulo operator behavior with negative integers is implementation-defined in older C++ standards or may return negative results; the function does not handle negative inputs to ensure a positive GCD.

------------------------------------------------------------------------------------

NO BUGS

------------------------------------------------------------------------------------

### Code Review Findings

*   **LINE(s):** 11
    **EXPLANATION:** The condition `abs(numbers[i]-numbers[j])` uses the integer version of `abs` from `<stdlib.h>` or `<math.h>`, which truncates the floating-point difference to an integer, leading to incorrect comparisons. It should use `std::abs` or `fabsf` to maintain precision for `float` values.

*   **LINE(s):** 13
    **EXPLANATION:** The code accesses `out[0]` and `out[1]` without checking if the `out` vector is empty. If the input `numbers` vector has fewer than two elements, the loops never execute, and this line will cause an out-of-bounds memory access crash.

------------------------------------------------------------------------------------

### Code Review: `rescale_to_unit`

*   **LINE(s):** 8
    **EXPLANATION:** The initialization of `min` and `max` to arbitrary constants ($100,000$ and $-100,000$) causes incorrect results if all input values fall outside this range (e.g., if all numbers are $> 100,000$, `min` will incorrectly remain $100,000$).
*   **LINE(s):** 15
    **EXPLANATION:** If the input vector contains identical values or a single element, `max - min` will be zero, resulting in a **division by zero** and producing `NaN` or crashing the program.
*   **LINE(s):** 7
    **EXPLANATION:** The function does not handle an empty input vector; the loop on line 9 will not execute, and the function will return an empty vector, but the logic remains fragile regarding the initialization values.
    
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------

------------------------------------------------------------------------------------

------------------------------------------------------------------------------------