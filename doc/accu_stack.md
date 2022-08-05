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

### (constructor)(T init = T{})
| Name      | Info                      |
| -         | -                         |
| init      | initial value             |

### const T & top() const
Returns the top value or init if the stack is empty.

### void push(const T & t)
Adds t and top() and pushes the result onto the stack.

### void pop()
Removes the top value from stack. Popping from an empty stack is UB.

### bool empty() const
Return true if the stack is empty.