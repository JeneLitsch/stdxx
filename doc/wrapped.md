# stx::wrapped

## Headers

stdxx/math.hxx

<br>

---

<br>

## Description

Wrap around number. If the value exceed max it wraps around to min and vice versa.

<br>

---

<br>

## Template parameters
| Name | Info                 | Default |
| ---- | -------------------- | ------- |
| T    | Singned Numeric Type | -       |

<br>

---

<br>

## Member functions

<br>

---

<br>

### wrapped(T val, T min, T max)

Ctor

- constexpr
- defaults
  - value = 0 
  - min = 0 
  - max = 0 

<br>

---

<br>

## Operators

<br>

### ++wrapped

Preincrement operator

- constexpr

<br>

### wrapped++

Postincrement operator

- constexpr

<br>

### --wrapped

Predecrement operator

- constexpr

<br>

### wrapped--

Postdecrement operator

- constexpr

<br>

### const T & operator*()

Returns the underlying value.

- constexpr
