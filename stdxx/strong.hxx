#pragma once

namespace stx {
	template<typename Type, typename Tag>
	struct strong {
		constexpr strong(const Type & value) : value(value) {};
		constexpr strong() = default;
		
		// Copy to same type
		constexpr strong(const strong &) = default;
		constexpr strong(strong &&) = default;
		constexpr strong & operator=(const strong &&) = default;
		constexpr strong & operator=(strong &&) = default;
		
		// Explicit casting
		template<typename Type2, typename Tag2>
		explicit constexpr strong(const strong<Type2, Tag2> & x)
			: value(x.value) {}
		
		template<typename Type2, typename Tag2>
		explicit constexpr strong(strong<Type2, Tag2> && x) 
			: value(std::move(x.value)) {}
		

		// Underlying
		explicit operator const Type &() const {
			return value;
		}
		
		explicit operator Type & () {
			return value;
		}

	private:
		Type value;
	};

	template<typename Type, typename Tag>
	auto colaps(const strong<Type, Tag> & l) {
		return static_cast<Type>(l);
	}

	#define COMP_OP(OP)\
	template<typename Type, typename Tag>\
	bool operator OP(\
		const strong<Type, Tag> & l,\
		const strong<Type, Tag> & r) {\
		return *l OP *r;\
	}

	COMP_OP(<=>)
	COMP_OP(==)
	COMP_OP(!=)
	COMP_OP(<)
	COMP_OP(>)
	COMP_OP(<=)
	COMP_OP(>=)

	#undef COMP_OP

	#define BIN_OP(OP)\
	template<typename Type, typename Tag>\
	auto operator OP(\
		const strong<Type, Tag> & l,\
		const strong<Type, Tag> & r) {\
		return strong<Type, Tag>(*l OP *r);\
	}

	BIN_OP(+)
	BIN_OP(-)
	BIN_OP(*)
	BIN_OP(/)
	BIN_OP(%)
	BIN_OP(<<)
	BIN_OP(>>)

	#undef BIN_OP


	template<typename Tag>
	using strong_int = strong<int, Tag>; 
	
	template<typename Tag> 
	using strong_float = strong<float, Tag>; 
}