# stx::lerp

## Header
stdxx/math.hxx

<br>

---

<br>

## Description

Lerp function(s) compatible with different types


<br>

---

<br>

## Functions

### stx::lerp(Integral, Integral, Floating) -> Integral

Simple numeric linear interpolation

<br>

### stx::lerp(UIntegral, UIntegral, Floating) -> UIntegral

Simple numeric linear interpolation

<br>

### stx::lerp(Floating, Floating, Floating) -> Floating

Simple numeric linear interpolation

<br>

### stx::lerp(Vec2, Vec2, Floating) -> Vec2

Elementwise linear interpolation. A lerp is performed along each axis.

<br>

### stx::lerp(Vec3, Vec3, Floating) -> Vec3

Elementwise linear interpolation. A lerp is performed along each axis.

<br>

### stx::lerp(RGB, RGB, Floating) -> RGB

Elementwise linear interpolation. A lerp is performed along each channel.

<br>

### stx::lerp(RGBA, RGBA, Floating) -> RGBA

Elementwise linear interpolation. A lerp is performed along each channel.

<br>

### lerp(T, T, Floating, double(double) ease) -> T

Forwards to other lerp-functions but applies easing to t.

<br>