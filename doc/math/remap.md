# stx::remap

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

| Name | Info                                   | Default |
| ---- | -------------------------------------- | ------- |
| In   | Type of input range and value.         | -       |
| Out  | Type of output range and return value. | -       |


<br>

---

<br>

## Functions

### stx::remap(In i_min, In i_max, Out o_min, Out o_max, In value) -> Out

Default Remap without easing

<br>

### stx::remap(In i_min, In i_max, Out o_min, Out o_max, In value, double(double) ease) -> Out

Remap with easing

<br>
