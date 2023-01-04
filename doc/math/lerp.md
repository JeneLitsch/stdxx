# stx::lerp

## Header
stdxx/math.hxx

<br>

---

<br>

## Description

Lerp function(s) compatible with different types

|     |           |                                      |
| --- | --------- | ------------------------------------ |
| 1   | Integral  | lerp(Integral, Integral, Floating)   |
| 2   | UIntegral | lerp(UIntegral, UIntegral, Floating) |
| 3   | Floating  | lerp(Floating, Floating, Floating)   |
| 4   | Vec2      | lerp(Vec2, Vec2, Floating)           |
| 5   | Vec3      | lerp(Vec3, Vec3, Floating)           |
| 6   | RGB       | lerp(RGB, RGB, Floating)             |
| 7   | RGBA      | lerp(RGBA, RGBA, Floating)           |

1 - 3) Simple numeric linear interpolation

4 - 7) Elementwise linear interpolation. A lerp is performed along each axis.