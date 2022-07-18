#pragma once
#include <queue>
#include <vector>
#include <iterator>

namespace stx {
	template<typename T, typename Container = std::vector<T>>
	class closed_queue {
	public:

		closed_queue(auto begin, auto end) : data{ begin, end } {
			this->reset();
		}



		closed_queue(std::initializer_list<T> && data) : data{ std::move(data) } {
			this->reset();
		}



		closed_queue(const Container & data) : data{data} {
			this->reset();
		}



		closed_queue(Container && data) : data { std::move(data) } {
			this->reset();
		}



		closed_queue(const closed_queue & q) {
			this->operator=(q);
		}



		closed_queue(closed_queue && q) {
			this->operator=(q);
		}



		closed_queue & operator=(const closed_queue & q) {
			const auto qi = q.index();
			this->data = q.data;
			this->current = std::begin(this->data);
			std::advance(this->current, qi);
			return *this;
		}



		closed_queue & operator=(closed_queue && q) {
			const auto qi = q.index();
			this->data = std::move(q.data);
			this->current = std::begin(this->data);
			std::advance(this->current, qi);
			return *this;
		}



		std::size_t index() const {
			const typename Container::const_iterator begin = std::begin(this->data);
			const typename Container::const_iterator cur = this->current;
			const auto i = std::distance(begin, cur);
			return static_cast<std::size_t>(std::max<decltype(i)>(i, 0));
		}



		void pop() {
			++current;
		}



		void unpop() {
			--current;
		}



		T & front() {
			return *current;
		}



		const T & front() const {
			return *current;
		}



		void reset() {
			this->current = std::begin(this->data);
		}



		std::size_t size() const {
			const typename Container::const_iterator end = std::end(this->data);
			const typename Container::const_iterator cur = this->current;
			const auto size = std::distance(cur, end);
			return static_cast<std::size_t>(std::max<decltype(size)>(size, 0));
		}



		std::size_t full_size() const {
			return data.size();
		}



		bool empty() const {
			return !size();
		}



		bool full() const {
			return this->size() == this->full_size();
		}



		friend auto operator<=>(const closed_queue & r, const closed_queue & l) {
			return std::lexicographical_compare_three_way(
				typename Container::const_iterator{r.current}, std::end(r.data),
				typename Container::const_iterator{l.current}, std::end(l.data));
		}



		friend bool operator==(const closed_queue & r, const closed_queue & l) {
			return (r <=> l) == 0;
		}

	private:
		Container data;
		typename Container::iterator current;
	};
}