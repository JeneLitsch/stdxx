#pragma once
#include "VectorN.hxx"

namespace stx {
    template<typename T, typename Flavor = vectorFlavor::DEFAULT>
    using vector4 = vectorN<T, 4, Flavor>;

    using vector4f = vector4<float, 			vectorFlavor::DEFAULT>; 
    using vector4d = vector4<double,			vectorFlavor::DEFAULT>; 
    using vector4i = vector4<int, 				vectorFlavor::DEFAULT>; 
    using vector4l = vector4<long, 				vectorFlavor::DEFAULT>; 
    using vector4u = vector4<unsigned, 			vectorFlavor::DEFAULT>; 
    using vector4ul = vector4<unsigned long, 	vectorFlavor::DEFAULT>; 

    using size4f = vector4<float, 				vectorFlavor::SIZE>; 
    using size4d = vector4<double,				vectorFlavor::SIZE>; 
    using size4i = vector4<int, 				vectorFlavor::SIZE>; 
    using size4l = vector4<long, 				vectorFlavor::SIZE>; 
    using size4u = vector4<unsigned, 			vectorFlavor::SIZE>; 
    using size4ul = vector4<unsigned long, 		vectorFlavor::SIZE>; 

    using position4f = vector4<float, 			vectorFlavor::POSITION>;
    using position4d = vector4<double,			vectorFlavor::POSITION>;
    using position4i = vector4<int, 			vectorFlavor::POSITION>;
    using position4l = vector4<long, 			vectorFlavor::POSITION>;
    using position4u = vector4<unsigned, 		vectorFlavor::POSITION>;
    using position4ul = vector4<unsigned long, 	vectorFlavor::POSITION>;
}