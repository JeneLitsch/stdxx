#pragma once
#include <utility>

namespace stx {
	template<typename T>
	class heaped final {
	public:
		template<typename ... Args>
		heaped(Args && ... args) {
			delete this->t;
			this->t = new T{std::forward<Args>(args)...};
		}



		heaped(const heaped & other) {
			delete this->t;
			this->t = new T{*other.t};
		} 



		heaped & operator=(const heaped & other) {
			delete this->t;
			this->t = new T{*other.t};
			return *this;
		} 



		heaped(heaped && other) {
			std::swap(this->t, other.t);
		} 



		heaped & operator=(heaped && other) {
			std::swap(this->t, other.t);
			return *this;
		} 



		friend void swap(heaped & l, heaped & r) {
			std::swap(l.t, r.t);

		}



		~heaped() {
			delete this->t;
		}



		T * operator->() {
			return t;
		}



		const T * operator->() const {
			return t;
		}



		operator bool() const {
			return !t;
		}

	private:
		T * t = nullptr;
	};
}