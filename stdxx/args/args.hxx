#pragma once
#include <vector>
#include <sstream>
#include <ostream>
#include <set>
#include <iterator>
#include "stdxx/memory.hxx"
#include "stdxx/algorithm.hxx"
#include "stdxx/iterator.hxx"
#include "stdxx/io.hxx"

namespace stx {
	class args {
	public:
		friend class iterator;
		class iterator {
		public:
			constexpr iterator(const args * args, std::size_t index)
				: args{args}
				, index{index} {}
			
			constexpr std::string_view operator*() const {
				return this->args->argv[this->index];
			}

			std::string str() const {
				return std::string(**this);
			}

			std::string_view str_v() const {
				return **this;
			}

			bool is_flag() const {
				return *this && this->str_v().starts_with("-");
			}

			constexpr iterator operator++() {
				this->index++; return *this;
			}

			constexpr iterator operator++(int) {
				iterator temp = *this;
				this->index++;
				return temp;
			}

			bool is_at_end() const {
				return this->index >= this->args->argc;
			}

			operator bool() const {
				return !this->is_at_end();
			}
		private:
			const args * args;
			std::size_t index;
		};

		args(int argc, char const *argv[]) :
			argc { argc },
			argv { argv } {}

		std::string_view command() const {
			if(argc == 0) return "";
			return argv[0];
		}

		std::string str() const {
			std::ostringstream oss;
			separate_by(argv, argv + argc, oss, " ");
			return oss.str();
		}

		iterator iter() const {
			return this->iter(0);
		}

		iterator iter(std::uint64_t at) const {
			return iterator{this, at + 1};
		}

		auto begin() { return argv; }
		auto begin() const { return argv; }
		auto cbegin() const { return argv; }

		auto end() { return argv + argc; }
		auto end() const { return argv + argc; }
		auto cend() const { return argv + argc; }

	private:
		int argc;
		char const ** argv;
	};
}