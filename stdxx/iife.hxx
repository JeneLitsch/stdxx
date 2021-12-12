#pragma once

template<class Callable>
auto iife(const Callable & callable) {
	return callable();
}

template<class Callable>
auto iife(Callable && callable) {
	return callable();
}
