# `stx::vector2<T, Flavor>`

## Header
stdxx/vector.hxx

<br>

---

<br>

## Member variables

<br>

### T x
The x component of the vector

<br>

### T y
The y component of the vector

<br>

---

<br>

## Member functions

<br>

### constexpr stx::vector()
Creates a vector (0, 0).

<br>

### constexpr stx::vector(T x, T y)
Creates a vector (x, y).

<br>

### constexpr stx::vector(T xy)
Creates a vector (xy, xy).

<br>

### constexpr stx::vector2(const vector2 &)
Copy constructor. Implicit for same type. Explicit for vectors with another T or Flavor.

<br>


### constexpr VectorType to() const
Creates VectorType from x and y.

<br>

### constexpr VectorType to() const
Creates VectorType from x and y.

<br>

---

<br>


## Static member functions

<br>

### constexpr vector2 from(const vector_2 auto & vec)
Creates a new vector from the x and y of any vector-like type.

<br>

### constexpr vectro2 from_angle(const radians_t angle)
Creates vector from angle.


<br>

---

<br>

## Operators 

<br>

### vector2 + vector2
Elementwise addition.

<br>

### vector2 - vector2
Elementwise subtraction.

<br>

### vector2 * vector2
Elementwise muliplication.

<br>

### vector2 / vector2
Elementwise division.

<br>

### vector2 * scalar, scalar * vector2 
Scalar multiplication of the vector components.

<br>

### vector2 / scalar, scalar / vector2 
Scalar multiplication of the vector components.

<br>

### vector2 == vector2, vector2 != vector2
Elementwise equality/inequality. Checks if the components of the two vectors are the same or not. 

<br>

### ostream << vector2
Output stream operator. Prints (x, y) to the stream.
