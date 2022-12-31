# stx::json::write_iterator

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

### stx::json::write_iterator(const node *)

Constructor for an iterator pointing to node.

<br>

### stx::json::write_iterator(const node &)

Constructor for an iterator pointing to node.

<br>

### void push_back(auto x)

Sets the contained node to an array and appends x to said array. 

<br>

---

<br>

## Operators

<br>

### = stx::json::null_t

Assigns a json null to the referenced node.


<br>

### = std::nullopt_t

Assigns a json null to the referenced node.

<br>

### = stx::nullptr_t

Assigns a json null to the referenced node.

<br>

### = bool

Assigns a bool to the referenced node.

<br>

### = std::integral

Assigns a number to the referenced node.

<br>

### = std::floating_point

Assigns a number to the referenced node.

<br>

### = stx::json::array_t

Assigns an empty array to the referenced node.

<br>

### = stx::json::object_t

Assigns an empty json dict/object to the referenced node.

<br>

### = stx::string_like

Assigns a string to the referenced node.

<br>

### = stx::json::node

Assigns a node to the referenced node.

<br>

### write_iterator [ stx::string_like ]

Returns an write_iterator to the child node of the json object. 
Assigns an object to the node if necessary.

<br>

### write_iterator [ std::intergral ]

Returns an write_iterator to the node at the index of the stored array.
Assigns an array to the node or resized an existing array if necessary.