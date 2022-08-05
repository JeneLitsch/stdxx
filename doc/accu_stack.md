# stx::accu_stack

## Header
stdxx/accu_stack.hxx

## Description
stx::accu_stack is a LIFO container adaptor.
The accumulator stack adds any pushed value to previous top value before pushing to stack.

## Template parameter
| Name      | Info                      |
| -         | -                         |
| T         | Type to store             |
| Container | Underlying container type |

## Interface

### `(constructor)(T init = T{})`
Constructs an stx::accu_stack with an init variable which will be used in subsequent pushes.


### `const T & top() const`
Returns the top value or init if the stack is empty. Only the const version is implemented to ensure the containers adaptors correct behavior.


### `void push(const T & t)`
Adds t and top() and pushes the result onto the stack.


### `void pop()`
Removes the top value from stack. Popping from an empty stack is UB.


### `bool empty() const`
Return true if the stack is empty.


### `size_type size() const`
Return the count of elements on the stack.


### `auto emplace(Args && ... args)`
Works actually more like a push. Only implemented for improved API compatibility to std::stack.


### `void swap(accu_stack & other) noexcept;`
Swaps underlying container and init value of the two stx::accu_stack objects.
