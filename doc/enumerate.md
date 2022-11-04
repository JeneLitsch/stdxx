# stx::enumerate

## Header

stdxx/utility.hxx

<br>

---

<br>

## Description

C++ implementation of a python-like enumerate.

|     |            |                                   |
| --- | ---------- | --------------------------------- |
| 1   | Range      | stx::enumerate(Container)         |
| 2   | ConstRange | stx::enumerate(const Container &) |

1) Creates a range with mutable values.

2) Creates a range with const values.

## Usage

The returned range can be iterated with a for loop and allows structured binding. The first identifier holds the index and the second a reference to the value at the index.

```c++
#include <vector>
#include <iostream>
#include "proto/enumerate.hxx"

int main() {
	std::vector<int> arr = {10,20,30,40,50};

	for(const auto [i, v] : stx::enumerate(arr)) {
		std::cout << i << ") " << v << "\n";
	}
}
// Output:
// 0) 10
// 1) 20
// 2) 30
// 3) 40
// 4) 50
```