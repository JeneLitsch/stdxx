#pragma once
#include <array>
#include <variant>

namespace stx {
	namespace internal {
		template<typename MakeEntry, typename T>
		constexpr std::array<typename MakeEntry::return_type, 1> iterate_types() {
			return std::array{ MakeEntry:: template create<T>() };
		}

		template<typename MakeEntry, typename T, typename T2, typename ... Ts>
		constexpr std::array<typename MakeEntry::return_type, sizeof...(Ts) + 2> iterate_types() {
			return iterate_types<MakeEntry, T2, Ts...>() + MakeEntry:: template create<T>();
		}

		template<typename, typename>
		struct table_maker_t {};

		template<typename MakeEntry, typename ... Ts>
		struct table_maker_t<MakeEntry, std::variant<Ts...>> {
			constexpr static auto create() {
				return iterate_types<MakeEntry, Ts...>();
			}
		};
	}

	template<typename MakeEntry, typename Variant>
	constexpr auto constexpr_table() {
		return internal::table_maker_t<MakeEntry, Variant>::create();
	}

	template<typename MakeEntry, typename Variant>
	constexpr auto constexpr_unordered_map() {
		const auto table = constexpr_table<MakeEntry, Variant>();
		return std::unordered_map(std::begin(table), std::end(table));
	}
}
