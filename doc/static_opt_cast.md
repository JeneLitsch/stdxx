# stx::static_opt_cast

## Header
stdxx/optional.hxx


<br>

---

<br>

## Description
A static cast for converting between two different but compatible std::optional types. For this cast to work T_IN must by convertible to T_OUT by a static_cast.

<br>

---

<br>

## Template parameters
| Name  | Info                           | Default                |
| ----- | ------------------------------ | ---------------------- |
| T_OUT | Type which should be casted to | -                      |
| T_IN  | Type of the parameter          | Deduced from arguments |

<br>

---

<br>

## Overloads

<br>

### std::optional<T_OUT> static_opt_cast(const std::optional<T_IN> & opt)

If the input optional contains a value, the value is casted and returned. If the input optional does NOT contain a value a nullopt is returned instead.

- constexpr

<br>

### std::optional<T_OUT> static_opt_cast(const T_IN & val)

The input value is casted to T_OUT. The returned optional always contains a value.

- constexpr

<br>

### std::optional<T_OUT> static_opt_cast(std::nullopt_t)

This overload just creates a nullopt. The returned optional never contains a value.

- constexpr
