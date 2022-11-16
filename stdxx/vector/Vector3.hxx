#pragma once
#include "VectorN.hxx"

namespace stx {
	template<typename T, typename Flavor = vectorFlavor::DEFAULT>
	using vector3 = vectorN<T, 3, Flavor>;

	using vector3f = vector3<float, 			vectorFlavor::DEFAULT>; 
	using vector3d = vector3<double,			vectorFlavor::DEFAULT>; 
	using vector3i = vector3<int, 				vectorFlavor::DEFAULT>; 
	using vector3l = vector3<long, 				vectorFlavor::DEFAULT>; 
	using vector3u = vector3<unsigned, 			vectorFlavor::DEFAULT>; 
	using vector3ul = vector3<unsigned long, 	vectorFlavor::DEFAULT>; 

	using size3f = vector3<float, 				vectorFlavor::SIZE>; 
	using size3d = vector3<double,				vectorFlavor::SIZE>; 
	using size3i = vector3<int, 				vectorFlavor::SIZE>; 
	using size3l = vector3<long, 				vectorFlavor::SIZE>; 
	using size3u = vector3<unsigned, 			vectorFlavor::SIZE>; 
	using size3ul = vector3<unsigned long, 		vectorFlavor::SIZE>; 

	using position3f = vector3<float, 			vectorFlavor::POSITION>;
	using position3d = vector3<double,			vectorFlavor::POSITION>;
	using position3i = vector3<int, 			vectorFlavor::POSITION>;
	using position3l = vector3<long, 			vectorFlavor::POSITION>;
	using position3u = vector3<unsigned, 		vectorFlavor::POSITION>;
	using position3ul = vector3<unsigned long, 	vectorFlavor::POSITION>;
}



// Unary
template<class Arithmetic, class Flavor> 
constexpr auto operator-(
	const stx::vector3<Arithmetic, Flavor> & vector) {
	return stx::vector3<Arithmetic, Flavor>(
		-vector.x,
		-vector.y,
		-vector.z);
}