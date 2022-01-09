#pragma once

namespace stx {
	template<typename Iter>
	class iterator_range {
	public:
		iterator_range(Iter begin, Iter end)
		: 	begin_it(begin),
			end_it(end) {}

		Iter begin() { return this->begin_it; };
		Iter begin() const { return this->begin_it; };
		Iter cbegin() const { return this->begin_it; };

		Iter end() { return this->end_it; };
		Iter end() const { return this->end_it; };
		Iter cend() const { return this->end_it; };


		#define UNPACK\
			if constexpr (I == 0) return begin_it;\
			if constexpr (I == 1) return end_it;

		template <size_t I>	auto & get() &             { UNPACK }
		template <size_t I> const auto & get() const & { UNPACK }
		template <size_t I> auto && get() &&           { UNPACK }

		#undef UNPACK

	private:	
		Iter begin_it;
		Iter end_it;
	};


}

namespace std {
 	template <typename Iter> struct tuple_size<stx::iterator_range<Iter>> 
	 	: std::integral_constant<size_t, 2> {};

    template <typename Iter> struct tuple_element<0, stx::iterator_range<Iter>> {
		using type = Iter; 
	};
    
	template <typename Iter> struct tuple_element<1, stx::iterator_range<Iter>> {
		using type = Iter;
	};
}