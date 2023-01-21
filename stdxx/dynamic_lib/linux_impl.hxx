#pragma once
#include <filesystem>
#include <dlfcn.h>

namespace stx {
	class dynamic_lib {
	public:
		dynamic_lib(const dynamic_lib &) = delete;
		dynamic_lib(dynamic_lib && other) {
			this->handle = other.handle;
			other.handle = nullptr;
		}
		dynamic_lib & operator=(const dynamic_lib &) = delete;
		dynamic_lib & operator=(dynamic_lib && other) {
			this->handle = other.handle;
			other.handle = nullptr;
			return *this;
		}

		~dynamic_lib() {
			if(this->handle) {
				dlclose(this->handle);
			}
		}



		dynamic_lib(const std::filesystem::path & path) {
			if(!std::filesystem::exists(path)) {
				throw std::runtime_error { "Cannot open: " + path.string() };
			}
			this->handle = dlopen(path.c_str(), RTLD_LAZY);
			if(!this->handle) {
				throw std::runtime_error { "Cannot load: " + path.string() };
			}
		}



		template<typename Ret, typename ... Args>
		auto get_fx(std::string_view name) const {
			auto * fx_ptr = this->get_if_fx<Ret, Args...>(name);
			if(!fx_ptr) {
				throw std::runtime_error { "Cannot find: " + std::string{name} };
			}
			return fx_ptr;
		}



		template<typename Ret, typename ... Args>
		auto get_if_fx(std::string_view name) const {
			auto * fx_ptr = dlsym(this->handle, name.data());
			return fx_ptr ? reinterpret_cast<Ret(*)(Args...)>(fx_ptr) : nullptr;
		}

	private:
		void * handle = nullptr;
	};
}