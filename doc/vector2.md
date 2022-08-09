# stx::vector2<T, Flavor>

## Header
stdxx/vector.hxx

---

## Description
stx::vector2 is 2D-Vector implementation. It provides the usual operations expected of such an implentation. Additionally it provides strong typedef support using the Flavor template parameter. 

---

## Member variables

<br>

### T x
The x component of the vector

<br>

### T y
The y component of the vector

---

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

---

## Static member functions

<br>

### constexpr vector2 from(const vector_2 auto & vec)
Creates a new vector from the x and y of any vector-like type.

<br>

### constexpr vectro2 from_angle(const radians_t angle)
Creates vector from angle.


---

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

---

## Strong Typedef Mechanism

An vector2 object cannot be implicitly converted to another flavor type. This prevents passing wrong vectors to functions and catches some incorrect assignments.

The flavor rules for operators are quite simple.
If both operand flavors of an binary operation are the same the result retains the flavor. If the flavor mismatch the result will be of flavor default and must casted if nesseary.

---

## Typedefs

| name        | T             | Flavor   |
| -           | -             | -        |
| vector2f    | float         | DEFAULT  |
| vector2d    | double        | DEFAULT  |
| vector2i    | int           | DEFAULT  |
| vector2l    | long          | DEFAULT  |
| vector2u    | unsigned      | DEFAULT  |
| vector2ul   | unsigned long | DEFAULT  |
|             |               |          |
| size2f      | float         | SIZE     |
| size2d      | double        | SIZE     |
| size2i      | int           | SIZE     |
| size2l      | long          | SIZE     |
| size2u      | unsigned      | SIZE     |
| size2ul     | unsigned long | SIZE     |
|             |               |          |
| position2f  | float         | POSITION |
| position2d  | double        | POSITION |
| position2i  | int           | POSITION |
| position2l  | long          | POSITION |
| position2u  | unsigned      | POSITION |
| position2ul | unsigned long | POSITION |