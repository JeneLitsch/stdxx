#pragma once

namespace stx {

	template <typename T>
	class fx_ptr;

	template <typename Ret, typename... Args>
	class fx_ptr <Ret(Args...)> {
		using Fx = Ret(*)(Args...);
	public:
		fx_ptr(Fx fx) : fx{fx} {}

		Ret operator()(Args && ...args) {
			return fx(args...);
		}
	private:
		Fx fx;
	};
}