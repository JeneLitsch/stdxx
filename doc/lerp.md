# stx::lerp(a, b, t)

## Header
stdxx/math.hxx

<br>

---

<br>

## Description

Linear interpolation function. It works for more types than std::lerp.
- signed and unsigned integrals
- floating point types
- stx::vector2<...>
- stx::vector3<...>

<br>

---

<br>

## Template parameters

| Name | Info                                       | Default |
| ---- | ------------------------------------------ | ------- |
| AB   | Return type and type lower and upper value | -       |
| T    | Type of the the position t.                | -       |

<br>

---

<br>

## floating point

Normal lerp function.

## signed integrals,

Normal lerp function. The return value is truncated.

## unsigned integrals

Normal lerp function. The function is safe to use if b &lt; a. The implementation contains protection against underflows. If the t is in [0,1] the return value is well defined.

## stx::vector2 and stx::vector3

Elementwise wise lerp of x and y (and z).