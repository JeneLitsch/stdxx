#pragma once

namespace stx {
	template<typename Vector3>
	concept vector_3 = requires(Vector3 v) {
		Vector3{v.x, v.y, v.z};
	};



	template<typename Vector2> 
	concept vector_2 = requires(Vector2 v) {
		Vector2{v.x, v.y};
	} && !vector_3<Vector2>;
}