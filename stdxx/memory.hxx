#include <memory>

namespace stx {
	template<typename T, typename ... Args>
	std::unique_ptr<T> make_unique(Args && ... args) {
		return std::unique_ptr<T>(new T{std::forward<Args>(args)...});
	}


	template<class To, class From>
	std::unique_ptr<To> static_unique_cast(std::unique_ptr<From> && from) {
		return std::unique_ptr<To>(static_cast<To*>(from.release()));
	}
}