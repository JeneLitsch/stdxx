# stx::fx::map / stx::fx::mapped

## Headers

stdxx/functional.hxx

## Description

These higher or functions are used to apply operations to collections.

|     | Returns              | Signature                                                  |
| --- | -------------------- | ---------------------------------------------------------- |
| 1   | std::vector&lt;R&gt; | stx::fx::map(R(T), std::vector&lt;T&gt;, Args && ... args) |

stx::fx::map calls a given function for each element in a collection and returns the results in a collection of the same kind.
Additional args can be passed after the collection.

|     | Returns  | Signature             |
| --- | -------- | --------------------- |
| 1   | Callable | stx::fx::mapped(R(T)) |

stx::fx::mapped wraps stx::fx::map into a callable and returns it.