#pragma once
#include <utility>
#include <concepts>
#include <tuple>

namespace stx {
	template<typename Container>
	using iterator_of = decltype(std::begin(std::declval<Container&>()));
	
	template<typename Container>
	using const_iterator_of = decltype(std::cbegin(std::declval<const Container&>()));
	
	template<typename Index, typename Iterator>
	class enumerate_iterator {
	public:
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;


		constexpr enumerate_iterator(Iterator iter, Index index) 
		: iter{iter}, index{index} {}



		constexpr auto operator*() const {
			return std::tuple<Index, std::remove_reference_t<decltype(*this->iter)> &>(this->index, *this->iter);
		}

		constexpr auto operator*() {
			return std::tuple<Index, std::remove_reference_t<decltype(*this->iter)> &>(this->index, *this->iter);
		}



		constexpr enumerate_iterator operator++() {
			this->index++;
			this->iter++;
			return *this;
		}

		constexpr enumerate_iterator operator++(int) {
			auto temp = *this;
			this->index++;
			this->iter++;
			return temp;
		}



		constexpr friend bool operator==(const enumerate_iterator & l, const enumerate_iterator & r) {
			return l.iter == r.iter;
		}

		constexpr friend bool operator!=(const enumerate_iterator & l, const enumerate_iterator & r) {
			return l.iter != r.iter;
		}



		Iterator iter;
		Index index;
	};



	template<std::integral Index, typename Container> 
	class enumerate_range {
	public:

		using iterator = enumerate_iterator<Index, iterator_of<Container>>;
		using const_iterator = enumerate_iterator<Index, const_iterator_of<Container>>;


		enumerate_range(Container & container) : container{container} {}



		constexpr auto begin() {
			return iterator{std::begin(container), 0};
		}

		constexpr auto end() {
			return iterator{std::end(container), static_cast<Index>(std::size(container))};
		}

		
		
		constexpr auto begin() const {
			return const_iterator{std::begin(container), 0};
		}

		constexpr auto end() const {
			return const_iterator{std::end(container), static_cast<Index>(std::size(container))};
		}



		constexpr auto cbegin() const {
			return const_iterator{std::cbegin(container), 0};
		}

		constexpr auto cend() const {
			return const_iterator{std::cend(container), static_cast<Index>(std::size(container))};
		}

	private:
		Container & container;
	};



	template<std::integral Index, typename Container> 
	class const_enumerate_range {
	public:

		using iterator = enumerate_iterator<Index, iterator_of<Container>>;
		using const_iterator = enumerate_iterator<Index, const_iterator_of<Container>>;


		const_enumerate_range(const Container & container) : container{container} {}


		
		constexpr auto begin() const {
			return const_iterator{std::begin(container), 0};
		}

		constexpr auto end() const {
			return const_iterator{std::end(container), static_cast<Index>(std::size(container))};
		}



		constexpr auto cbegin() const {
			return const_iterator{std::cbegin(container), 0};
		}

		constexpr auto cend() const {
			return const_iterator{std::cend(container), static_cast<Index>(std::size(container))};
		}

	private:
		const Container & container;
	};



	template<std::integral Index = std::size_t, typename Container> 
	auto enumerate(Container & container) {
		return enumerate_range<Index, Container>{container};
	}



	template<std::integral Index = std::size_t, typename Container> 
	auto enumerate(const Container & container) {
		return const_enumerate_range<Index, Container>{container};
	}
}