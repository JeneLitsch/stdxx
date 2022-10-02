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

## Member functions

constexpr reference(T & ref) : ptr(&ref) {}

<br>


### template&lt;class U&gt; constexpr reference(reference&lt;U&gt; & ref)

Copy constructor for stx::reference

<br>

---

<br>

## Operators

<br>

### constexpr reference & operator=(T & ref)

Assignment operator

<br>

### constexpr operator T&() 
### constexpr operator const T &() const

This conversion operator allows the automatic conversion from stx::reference to a normal C++ reference, when e.g. passing to function

<br>

### constexpr T * operator-&gt;()
### constexpr const T * operator-&gt;() const

Member access via the arrow operator. This allows pointer-like usage. 

<br>

### constexpr T & operator*()
### constexpr const T & operator*() const

Pointer derefence operator. This makes stx::reference syntactically similar to a pointer. 
