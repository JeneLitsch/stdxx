#  stx::chrono::split_hh_mm_ss

## Header

stdxx/chrono.hxx

<br>

---

<br>


## Parameter

`std::chrono::seconds`

## Return value

`std::tuple<std::chrono::hours, std::chrono::minutes, std::chrono::seconds>`

## Description

Splits an duration of seconds into the hh:mm:ss representation.

## Example

```c++
	const auto [hh, mm, ss] = stx::chrono::split_hh_mm_ss(std::chrono::seconds(90));
	// hh = 0h
	// mm = 1m
	// ss = 30s
```

