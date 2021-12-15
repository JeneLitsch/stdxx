#pragma once

auto iife(const auto & callable) {
	return callable();
}
