#pragma once
#include <vector>
#include "stdxx/vector.hxx"
#include "stdxx/concepts.hxx"
#include "stdxx/reference.hxx"

namespace stx {
	template<typename T, typename Container = std::vector<T>>
	class grid3 {
	public:

		grid3(
			const stx::vector_3 auto & size,
			const T & value)
			:	sizeXYZ(size) {
			this->data.resize(size.x * size.y * size.z, value);
		}


		grid3(
			const std::size_t & size_x,
			const std::size_t & size_y,
			const std::size_t & size_z,
			const T & value)
			:	sizeXYZ(size_x, size_y, size_z) {
			this->data.resize(size_x * size_y * size_z, value);
		}
		

		const auto & operator()(std::size_t x, std::size_t y, std::size_t z) const {
			guard_range(x,y,z);
			return this->data[
				z * this->sizeXYZ.x * this->sizeXYZ.y +
				y * this->sizeXYZ.x +
				x];
		}


		auto & operator()(std::size_t x, std::size_t y, std::size_t z) {
			guard_range(x,y,z);
			return this->data[
				z * this->sizeXYZ.x * this->sizeXYZ.y +
				y * this->sizeXYZ.x +
				x];
		}
		

		const auto & operator[](const stx::position3ul & pos) const {
			return (*this)(pos.x, pos.y, pos.z);
		}


		auto & operator[](const stx::position3ul & pos) {
			return (*this)(pos.x, pos.y, pos.z);
		}


		const auto & operator[](const stx::vector_3 auto & pos) const {
			return (*this)(pos.x, pos.y, pos.z);
		}


		auto & operator[](const stx::vector_3 auto & pos) {
			return (*this)(pos.x, pos.y, pos.z);
		}


		stx::size3ul size() const {
			return this->sizeXYZ;
		}
		

		bool in_range(auto x, auto y, auto z) const {
			return
				(x < this->sizeXYZ.x) &&
				(y < this->sizeXYZ.y) &&
				(z < this->sizeXYZ.z) &&
				(x >= 0) &&
				(y >= 0) &&
				(z >= 0);
		}


		bool in_range(const stx::vector_3 auto & pos) const {
			return this->in_range(pos.x, pos.y, pos.z);
		}

		bool in_range(const stx::position3ul & pos) const {
			return this->in_range(pos.x, pos.y, pos.z);
		}

		auto begin() { return std::begin(data); }
		auto begin() const { return std::begin(data); }
		auto cbegin() const { return std::cbegin(data); }

		auto end() { return std::end(data); }
		auto end() const { return std::end(data); }
		auto cend() const { return std::cend(data); }

	private:
		void guard_range(auto x, auto y, auto z) const {
			if(!this->in_range(x, y, z)) throw std::out_of_range("");
		}

		stx::size3ul sizeXYZ;
		Container data;
	};
}