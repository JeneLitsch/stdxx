# stx::reference

## Header
stdxx/reference.hxx

<br>

---

<br>

## Description
Alternative to std::reference_wrapper.

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

### reference(T & ref) 

Ctor that creates reference pointing to ref 

- constexpr

<br>


### reference(reference&lt;U&gt; & ref)

<br>

Copy constructor for stx::reference

- constexpr
- template type U

<br>

---

<br>

## Operators

<br>

### reference & operator=(T & ref)

Assignment operator

- constexpr

<br>

### operator T&() 

This conversion operator allows the automatic conversion from stx::reference to a normal C++ reference, when e.g. passing to function

- constexpr
- const

<br>

### T * operator-&gt;()

Member access via the arrow operator. This allows pointer-like usage. 

- constexpr
- const

<br>

### T & operator*()

Pointer dereference operator. This makes stx::reference syntactically similar to a pointer. 

- constexpr
- const