#pragma once
#include <ostream>
#include "VectorN.hxx"


namespace stx {


	template<typename T, typename Flavor = vectorFlavor::DEFAULT>
	using vector2 = vectorN<T, 2, Flavor>;	

	// Typedefs
	using vector2f  = vector2<float>; 
	using vector2d  = vector2<double>; 
	using vector2i  = vector2<int>; 
	using vector2l  = vector2<long>; 
	using vector2u  = vector2<unsigned>; 
	using vector2ul = vector2<unsigned long>; 

	using vector2i8 = vector2<std::int8_t>; 
	using vector2i16 = vector2<std::int16_t>; 
	using vector2i32 = vector2<std::int32_t>; 
	using vector2i64 = vector2<std::int64_t>; 

	using vector2u8 = vector2<std::uint8_t>; 
	using vector2u16 = vector2<std::uint16_t>; 
	using vector2u32 = vector2<std::uint32_t>; 
	using vector2u64 = vector2<std::uint64_t>; 

	template<typename Arithmetic> 
	using size2   = vector2<Arithmetic, vectorFlavor::SIZE>;
	using size2f  = size2<float>;
	using size2d  = size2<double>; 
	using size2i  = size2<int>;
	using size2l  = size2<long>;
	using size2u  = size2<unsigned>; 
	using size2ul = size2<unsigned long>;

	using size2i8 = size2<std::int8_t>; 
	using size2i16 = size2<std::int16_t>; 
	using size2i32 = size2<std::int32_t>; 
	using size2i64 = size2<std::int64_t>; 

	using size2u8 = size2<std::uint8_t>; 
	using size2u16 = size2<std::uint16_t>; 
	using size2u32 = size2<std::uint32_t>; 
	using size2u64 = size2<std::uint64_t>; 


	template<typename Arithmetic> 
	using position2   = vector2<Arithmetic, vectorFlavor::POSITION>;
	using position2f  = position2<float>; 
	using position2d  = position2<double>; 
	using position2i  = position2<int>; 
	using position2l  = position2<long>; 
	using position2u  = position2<unsigned>; 
	using position2ul = position2<unsigned long>;

	using position2i8 = position2<std::int8_t>; 
	using position2i16 = position2<std::int16_t>; 
	using position2i32 = position2<std::int32_t>; 
	using position2i64 = position2<std::int64_t>; 

	using position2u8 = position2<std::uint8_t>; 
	using position2u16 = position2<std::uint16_t>; 
	using position2u32 = position2<std::uint32_t>; 
	using position2u64 = position2<std::uint64_t>; 


	// Unary
	template<class Arithmetic, class Flavor>
	constexpr auto operator-(
		const stx::vector2<Arithmetic, Flavor> & vec) {
		return stx::vector2<Arithmetic, Flavor>(
			-vec.x,
			-vec.y);
	}
}
