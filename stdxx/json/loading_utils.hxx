#pragma once
#include <vector>
#include <map>
#include <set>
#include "iterator.hxx"

namespace stx::json {
	auto vector_of(auto fx, const stx::json::iterator & json) {
		std::vector<decltype(fx(json))> vec;
		for(const auto elem : stx::json::to_array(json)) {
			vec.push_back(fx(elem));
		}
		return vec;
	}



	auto set_of(auto fx, const stx::json::iterator & json) {
		std::set<decltype(fx(json))> vec;
		for(const auto elem : stx::json::to_array(json)) {
			vec.insert(fx(elem));
		}
		return vec;
	}



	auto map_of(auto fx, const stx::json::iterator & json) {
		std::map<std::string, decltype(fx(json))> map;
		for(const auto & key : json.keys()) {
			map.insert({key, fx(json[key])});
		}
		return map;
	}
}