#include <filesystem>


namespace stx::filesystem::literals {
	inline std::filesystem::path operator""_p(const char * str, std::size_t){
		return std::filesystem::path(str);
	}

}


namespace stx::fs {
	inline auto replace_stem(std::filesystem::path path, auto new_root) {
		const auto extension = path.extension();
		return path.
			replace_filename(new_root).
			replace_extension(extension.string());
	}

	inline auto concat_stem(std::filesystem::path path, auto str) {
		return replace_stem(path, path.stem().concat(str));
	}
}