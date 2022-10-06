# stx::json::iterator

## Header
stdxx/json.hxx

<br>

---

<br>

## Description
Iterator like class to read json nodes. This is a read-only iterator.

<br>

---

<br>

## Member functions

<br>

### stx::json::iterator(std::nullptr_t)

Constructor for an invalid/empty iterator.

<br>

### stx::json::iterator(std::nullopt_t)

Constructor for an invalid/empty iterator.

<br>

### stx::json::iterator(const node *)

Constructor for an iterator pointing to node.

<br>

### stx::json::iterator(const node &)

Constructor for an iterator pointing to node.

<br>

### bool force_boolean()
Returns the stored boolean or throws stx::json::format_error if the type does not match.

- const

<br>

### double force_number()
Returns the stored number or throws stx::json::format_error if the type does not match.

- const

<br>

### std::string force_string()

Returns the stored string or throws stx::json::format_error if the type does not match.

- const

<br>

### bool null()

Checks if the null type is stored.

- const

<br>

### std::option&lt;bool&gt; boolean()

Returns the stored boolean. Returns std::nullopt if the type does not match.

- const

<br>

### std::option&lt;double&gt; number()

Returns the stored number. Returns std::nullopt if the type does not match.

- const

<br>

### std::option&lt;std::string&gt; string()

Returns the stored string. Returns std::nullopt if the type does not match.

- const

<br>

### std::size_t size()

Returns the size of the stored array. Returns the 0 if the store value is not an array.

- const

<br>

### std::vector&lt;std::string&gt; keys()

Return the keys of the json object. The result is empty if the node type is an empty object or not an object at all.

- const

<br>

---

<br>

## Operators

<br>

### bool

Returns true if the iterator points to a valid json node. Wrong if any previous node traversing was unsuccessful.

- const

<br>

### iterator [ stx::string_like ]

Returns an iterator to the child node of the json object. 
Returns an invalid iterator if the iterator does not point to json object.

- const

<br>

### iterator [ std::intergral ]

Returns an iterator to node at the index of the store array.
Returns an invalid iterator if the iterator does not point to json array.

- const

<br>

---

<br>

## Non-Member Functions

<br>

### std::vector&lt;stx::json::iterator&gt; to_array(stx::json::iterator)

Extract an array of iterators to the child nodes. The size of the array is the size of the passed iterator.