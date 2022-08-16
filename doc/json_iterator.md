# stx::json::iterator

## Header
stdxx/json.hxx

<br>

---

<br>

## Description
Iterator like class to read json nodes.

<br>

---

<br>

## Member functions

<br>

### stx::json::iterator(const node *)
Constructor for an iterator pointing to node.

<br>

### stx::json::iterator(const node &)
Constructor for an iterator pointing to node.

<br>

### bool force_boolean() const
Returns the stored boolean or throws stx::json::format_error if the type does not match.

<br>

### double force_number() const
Returns the stored number or throws stx::json::format_error if the type does not match.

<br>

### std::string force_string() const
Returns the stored string or throws stx::json::format_error if the type does not match.


<br>

### bool null() const
Checks if the null type is stored.

<br>

### std::option&lt;bool&gt; boolean() const
Returns the stored boolean. Returns std::nullopt if the type dose not match.

<br>

### std::option&lt;double&gt; number() const
Returns the stored number. Returns std::nullopt if the type dose not match.

<br>

### std::option&lt;std::string&gt; number() const
Returns the stored string. Returns std::nullopt if the type dose not match.

<br>

### std::size_t size() const
Returns the size of the stored array. Returns the 0 if the store value is not an array.

<br>

### std::vector&lt;std::string&gt; keys() const
Return the keys of the json object. The result is empty if the node type is an empty object or not an object at all.

<br>

---

<br>

## Operators

<br>

### bool
Returns true if the iterator points to a valid json node. Wrong if any previous node traversing was unsuccessful.

<br>

### iterator [ const std::string & ]
### iterator [ const char * ]
### iterator [ const std::string_view ]
Returns an iterator to the child node of the json object. 
Returns an invalid iterator if the iterator does not point to json object.

<br>

### iterator [ std::size_t ]
### iterator [ std::intergral ]
Returns an iterator to node at the index of the store array.
Returns an invalid iterator if the iterator does not point to json array.

<br>
