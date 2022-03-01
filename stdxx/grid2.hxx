#pragma once
#include <vector>
#include "stdxx/vector.hxx"
#include "stdxx/concepts.hxx"
#include "stdxx/reference.hxx"

namespace stx {
	template<typename T, typename Container = std::vector<T>>
	class grid2 {
	public:

		grid2(
			const stx::vector_2 auto & sizeXY,
			const T & value)
			:	sizeXY(sizeXY) {
			this->data.resize(this->sizeXY.x * this->sizeXY.y, value);
		}


		grid2(
			const std::size_t & sizeX,
			const std::size_t & sizeY,
			const T & value)
			:	sizeXY(sizeX, sizeY) {
			this->data.resize(this->sizeXY.x * this->sizeXY.y, value);
		}
		

		const auto & operator()(std::size_t x, std::size_t y) const {
			guard_range(x,y);
			return this->data[y * this->sizeXY.x + x];
		}


		auto & operator()(std::size_t x, std::size_t y) {
			guard_range(x,y);
			return this->data[y * this->sizeXY.x + x];
		}
		

		const auto & operator[](const stx::position2ul & pos) const {
			return (*this)(pos.x, pos.y);
		}


		auto & operator[](const stx::position2ul & pos) {
			return (*this)(pos.x, pos.y);
		}


		const auto & operator[](const stx::vector_2 auto & pos) const {
			return (*this)(pos.x, pos.y);
		}


		auto & operator[](const stx::vector_2 auto & pos) {
			return (*this)(pos.x, pos.y);
		}


		stx::size2ul size() const {
			return this->sizeXY;
		}
		

		bool in_range(auto x, auto y) const {
			return
				(x < this->sizeXY.x) &&
				(y < this->sizeXY.y) &&
				(x >= 0) &&
				(y >= 0);
		}


		bool in_range(const stx::vector_2 auto & pos) const {
			return this->in_range(pos.x, pos.y);
		}

		bool in_range(const stx::position2ul & pos) const {
			return this->in_range(pos.x, pos.y);
		}

		auto begin() { return std::begin(data); }
		auto begin() const { return std::begin(data); }
		auto cbegin() const { return std::cbegin(data); }

		auto end() { return std::end(data); }
		auto end() const { return std::end(data); }
		auto cend() const { return std::cend(data); }

	private:
		void guard_range(auto x, auto y) const {
			if(!this->in_range(x, y)) throw std::out_of_range("");
		}

		stx::size2ul sizeXY;
		Container data;
	};
}