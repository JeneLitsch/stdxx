# stx::optref

## Headers

stdxx/reference.hxx

stdxx/optional.hxx

<br>

---

<br>

## Description
Non owning pointer class which unites the functionality of stx::reference and std::optional in a single class.

<br>

---

<br>

## Template parameters
| Name | Info                     | Default |
| ---- | ------------------------ | ------- |
| T    | Type which is referenced | -       |

<br>

---

<br>

## Member functions

<br>

###	optref()

Default constructs a null optref.

- constexpr

<br>

###	optref(T & t)

Ctor for a non-null optref which points to t.

- constexpr

<br>
		
###	optref(std::nullopt_t)

Ctor for a null optref

- constexpr

<br>

###	optref(std::nullref_t)

Ctor for a null optref

- constexpr

<br>


### optref(std::nullptr_t)

Ctor for a null optref

- constexpr

<br>

### T & value() 

Checked dereference. Throws std::bad_optional_access if called on a null optref.

- constexpr
- const

<br>

### T & value_or(T & alt)

Returns the contained reference or alt in case the optref is null.

- constexpr
- const

<br>

---

<br>

## Operators

<br>

### bool ()

Returns true if the optref is non-null.

- constexpr
- const

<br>

### const T * operator-&gt;()

Pointer member access operator

- constexpr
- const

<br>

### const T & operator*()

Pointer dereference operator. This makes stx::optref syntactically similar to a pointer. 

- constexpr
- const

<br>

### const T & operator&()

Returns the contained pointer.

- constexpr
- const