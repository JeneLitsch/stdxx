# stx::json::node

## Header
stdxx/json.hxx

<br>

---

<br>

## Description
Recursive Variant containing json data.

<br>

---

<br>

## Member functions

### std::json::node()
Constructor for a node holding null as the value.

<br>

### std::json::node(std::nullptr_t)
Constructor for a node holding null as the value.

<br>

### std::json::node(bool)
Constructor for a node holding a boolean value.

<br>

### std::json::node(std::floating_point)
Constructor for a node holding a numeric value.

<br>

### std::json::node(std::integral)
Constructor for a node holding a numeric value.

<br>

### std::json::node(stx::string_like)
Constructor for a node holding a string.

<br>

### std::json::node(stx::string_like)
Constructor for a node holding a string.

<br>

### std::json::node(const stx::vector&lt;stx::json::node&gt;&)
Constructor for a node holding an array.

<br>

### std::json::node(const stx::initializer_list&lt;stx::json::node&gt;&)
Constructor for a node holding an array.

<br>

### std::json::node(const stx::vector&lt;std::pair&lt;stx::json::node&gt;&gt;&)
Constructor for a node holding an object.

<br>

### std::json::node(const stx::initializer_list&lt;std::pair&lt;stx::json::node&gt;&gt;&)
Constructor for a node holding an object.

<br>

---

<br>

## Operators

<br>


### ostream << stx::json::node
Writes json to the ostream

<br>

### istream >> stx::json::node
Read json from the istream and stores it in the node.
Throws stx::json::syntax_error if the syntax is invalid or not a supported extension/dialect.