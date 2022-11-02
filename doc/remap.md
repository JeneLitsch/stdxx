# stx::remap(In in_min, In in_max, Out out_min, Out out_max, In value)

## Header
stdxx/math.hxx

<br>

---

<br>

## Description

Remaps the value from range [in_min, in_max] to [out_min, out_max].
The function is defined if stx::invlerp is defined for In and stx::lerp is defined for Out.

<br>

---

<br>

## Template parameters

| Name  | Info                                   | Default |
| ----- | -------------------------------------- | ------- |
| In  | Type of input range and value.         | -       |
| Out | Type of output range and return value. | -       |