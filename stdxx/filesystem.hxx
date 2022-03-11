#include <filesystem>


namespace stx::filesystem::literals {
	inline std::filesystem::path operator""_p(const char * str, std::size_t){
		return std::filesystem::path(str);
	}
}