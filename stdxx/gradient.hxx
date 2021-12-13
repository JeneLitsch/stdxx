#pragma once
#include <map>
#include <algorithm>
#include <cmath>
#include <numeric>
#include "lerp.hxx"
#include "iterator.hxx"

namespace stx {


 
	template<typename Key, typename Value>
	Value gradient(
		const typename std::map<Key, Value>::const_iterator & begin,
		const typename std::map<Key, Value>::const_iterator & end,
		const Key & t,
		const Value & defaultValue = {}) {

		if(empty(begin, end)) {
			return defaultValue;
		}

		constexpr auto comp = [](const auto t, const auto & pair) {
			return pair.first > t;
		};

		const auto pair = std::upper_bound(begin, end, t, comp);

		const auto next = (pair == end)   ? stx::prev(pair) : pair;
		const auto prev = (pair != begin) ? stx::prev(pair) : pair; 

		const auto [posNext, valueNext] = *next;
		const auto [posPrev, valuePrev] = *prev;

		const auto distance = posNext - posPrev;
		
		if(distance == 0) {
			return valuePrev;
		}

		const auto tLerp = std::clamp(
			static_cast<Key>((t - posPrev)/distance),
			static_cast<Key>(0.0),
			static_cast<Key>(1.0));

		return lerp(valuePrev, valueNext, tLerp);	
	}
}
