**LINE 7**
**EXPLANATION:** The function returns `number - int(number) + 1` but should return just `number - int(number)`. The `+ 1` incorrectly adds 1 to the fractional part, so e.g. `truncate_number(3.7)` returns `1.7` instead of `0.7`.

------------------------------------------------------------------------------------

**LINE 9:** The loop condition is `i < n` but should be `i <= n`.

The function is supposed to return a sequence from 0 to n (inclusive), but the loop stops at `n-1`, so the final value `n` is never appended to the output string.

------------------------------------------------------------------------------------

**LINE 7** — `if (n-i==0)` should be `if (n%i==0)`.
The condition checks whether `n` minus `i` equals zero (i.e. `n == i`), rather than checking whether `i` divides `n` evenly. This means the function almost never finds a divisor and incorrectly returns 1 for nearly all inputs.

------------------------------------------------------------------------------------

**LINE 11**

**EXPLANATION:** The condition is inverted — it pushes strings that do *not* start with the prefix, excluding those that do. The `!=` operator should be `==` to correctly filter *in* strings that match the prefix.

------------------------------------------------------------------------------------

**LINE 9**
**EXPLANATION:** The condition `l[i] < 0` is inverted — it pushes *negative* values into `out` instead of positive ones. The condition should be `l[i] > 0` to correctly filter for positive numbers.

------------------------------------------------------------------------------------

**LINE(s): 7–9**
**EXPLANATION:** The function is named `strlen`, which conflicts with the standard C library function `strlen` declared in `<string.h>`/`<cstring>` (and transitively included by other headers). This creates an ambiguous or redefined symbol, leading to undefined behaviour or compilation errors. Additionally, the parameter is passed by value, causing an unnecessary copy, though this is a performance issue rather than a correctness bug.

**LINE(s): 9**
**EXPLANATION:** `str.length()` returns `std::string::size_type` (an unsigned type, typically `size_t`), but the function returns `int`. For strings longer than `INT_MAX`, this truncates/overflows, producing an incorrect (potentially negative) result.

------------------------------------------------------------------------------------

NO BUGS

------------------------------------------------------------------------------------

NO BUGS

------------------------------------------------------------------------------------

**LINE 8**
**EXPLANATION:** Initializing `max` to `-10000` is a magic number that will produce incorrect results if all elements in the vector are less than `-10000`. The initial value should be `l[0]` (with an empty-vector guard) or `-INFINITY` / `std::numeric_limits<float>::lowest()`.

**LINE 9**
**EXPLANATION:** If the vector is empty, the loop doesn't execute and the function returns `-10000` — a meaningless sentinel — rather than signalling an error. There is no empty-input guard (e.g. an early `return` or exception), so the caller receives a silently bogus value.

------------------------------------------------------------------------------------

NO BUGS

------------------------------------------------------------------------------------
