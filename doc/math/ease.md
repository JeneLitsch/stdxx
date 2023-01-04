# stx::ease::

## Header
stdxx/math.hxx

<br>

---

<br>

## Description

Collection of easing functions and related utilities. This can be used in combination with lerp and remap.

<br>

---

<br>

## Functions

<br>

### stx::ease::none(double t) -> double

Just forwards the t and does not modify the value.

<br>

### stx::ease::clamp(double t) -> double

The value of t is clamped between 0 and 1.

<br>

### stx::ease::clamped(fx) -> double(double)

Wraps an ease function into stx::ease::clamp.

<br>

### stx::ease::poly_in(degree) -> double(double)

Returns a callable polynomial in ease function of the form: t&circ;degree.

<br>

### stx::ease::poly_out(degree) -> double(double)

Returns a callable polynomial out ease function of the form: (1-(1-t))&circ;degree.

<br>

### stx::ease::poly_in_out(degree) -> double(double)

Return a combined ease function made from poly_in and poly_out of the same degree.

<br>

### stx::ease::poly_in_out(degree_in, degree_out) -> double(double)

Return a combined ease function made from poly_in and poly_out with different degrees.