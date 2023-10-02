# stx::vector2

## Header
stdxx/vector.hxx

<br>

---

<br>

## Description

stx::vector2 is 2D-Vector implementation. It provides the usual operations expected of such an implentation. Additionally it provides strong typedef support using the Flavor template parameter. 

<br>

---

<br>

## Template parameters
| Name   | Info                               | Default |
| ------ | ---------------------------------- | ------- |
| T      | Type for x and y                   | -       |
| Flavor | Descripion type for strong typedef | -       |

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

### stx::vector()

Creates a vector (0, 0).

- constexpr

<br>

### stx::vector(T x, T y)

Creates a vector (x, y).

- constexpr

<br>

### stx::vector(T xy)

Creates a vector (xy, xy).

- constexpr

<br>

### stx::vector2(const vector2 &)

Copy constructor. Implicit for same type. Explicit for vectors with another T or Flavor.

- constexpr

<br>


### VectorType to()

Creates VectorType from x and y.

- const 
- constexpr 

<br>

### VectorType to()

Creates VectorType from x and y.

- const 
- constexpr

<br>

---

<br>

## Static member functions

<br>

### vector2 from(const vector_2 auto & vec)

Creates a new vector from the x and y of any vector-like type.

- constexpr

### vector2 from(const std::tuple&lt;X,Y&gt; & tup)

Creates a new vector from a two element tuple.
The first element becomes the x-value and the second the y-value. 

- constexpr

<br>

### vectro2 from_angle(const radians_t angle)

Creates vector from angle.

- constexpr

<br>

---

<br>

## Operators 

<br>

### vector2 + vector2

Elementwise addition.

- constexpr

<br>

### vector2 - vector2

Elementwise subtraction.

- constexpr

<br>

### vector2 * vector2

Elementwise muliplication.

- constexpr

<br>

### vector2 / vector2

Elementwise division.

- constexpr

<br>

### vector2 * scalar, scalar * vector2 

Scalar multiplication of the vector components.

- constexpr

<br>

### vector2 / scalar, scalar / vector2 

Scalar multiplication of the vector components.

- constexpr

<br>

### vector2 == vector2, vector2 != vector2

Elementwise equality/inequality. Checks if the components of the two vectors are the same or not. 

- constexpr

<br>

### ostream << vector2
Output stream operator. Prints (x, y) to the stream.

<br>

---

<br>

## Strong Typedef Mechanism

An vector2 object cannot be implicitly converted to another flavor type. This prevents passing wrong vectors to functions and catches some incorrect assignments.

The flavor rules for operators are quite simple.
If both operand flavors of an binary operation are the same the result retains the flavor. If the flavor mismatch the result will be of flavor default and must casted if nesseary.

<br>

---

<br>

## Typedefs

| name        | T             | Flavor   |
| ----------- | ------------- | -------- |
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