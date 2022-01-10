#pragma once

namespace stx {
	template<typename Type, typename Tag>
	struct strong_type {
		constexpr strong_type(const Type & value) : value(value) {};
		constexpr strong_type() = default;
		
		// Copy to same type
		constexpr strong_type(const strong_type &) = default;
		constexpr strong_type(strong_type &&) = default;
		constexpr strong_type & operator=(const strong_type &&) = default;
		constexpr strong_type & operator=(strong_type &&) = default;
		
		// Explicit casting
		template<typename Type2, typename Tag2>
		explicit constexpr strong_type(const strong_type<Type2, Tag2> & x)
			: value(x.value) {}
		
		template<typename Type2, typename Tag2>
		explicit constexpr strong_type(strong_type<Type2, Tag2> && x) 
			: value(std::move(x.value)) {}
		

		// Decay
		const Type & operator*() const {
			return value;
		}
		
		Type & operator*() {
			return value;
		}

	private:
		Type value;
	};

	#define BINARY_OP(OP)\
	template<typename Type, typename Tag>\
	bool operator OP(\
		const strong_type<Type, Tag> & l,\
		const strong_type<Type, Tag> & r) {\
		return *l OP *r;\
	}

	BINARY_OP(<=>)
	BINARY_OP(==)
	BINARY_OP(!=)
	BINARY_OP(<)
	BINARY_OP(>)
	BINARY_OP(<=)
	BINARY_OP(>=)

	BINARY_OP(+)
	BINARY_OP(-)
	BINARY_OP(*)
	BINARY_OP(/)
	BINARY_OP(%)

	BINARY_OP(<<)
	BINARY_OP(>>)

	#undef BINARY_OP

	template<typename Tag>
	using strong_int = strong_type<int, Tag>; 
	
	template<typename Tag> 
	using strong_float = strong_type<float, Tag>; 
}