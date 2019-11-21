#ifndef INC_3_FIBO_H
#define INC_3_FIBO_H

#include <iostream>
#include <string_view>
#include <boost/dynamic_bitset.hpp>
#include <boost/operators.hpp>
#include <type_traits>

class Fibo: boost::addable<Fibo>, boost::bitwise<Fibo>,
            boost::left_shiftable<Fibo, size_t>, boost::totally_ordered<Fibo> {
public:
	Fibo() = default;

	explicit Fibo(std::string_view s);
	explicit Fibo(const char* s) : Fibo(s ? std::string_view(s) : std::string_view()) {}

	template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0 >
	Fibo(T n) {
		assert(n >= 0);
		if (n > 0) {
			T f1 = 1, f2 = 2;
			size_t i = 2;
			for (; f2 <= n - f1; ++i) {
				T tmp = f2;
				f2 = f2 + f1;
				f1 = tmp;
			}
			data.resize(i);
			for (--i; n > 0; --i) {
				if (f2 <= n) {
					data[i] = true;
					n -= f2;
				}
				T tmp = f1;
				f1 = f2 - f1;
				f2 = tmp;
			}
			trimLeadingZeroes();
		}
	}

	Fibo(bool) = delete;
	Fibo(char) = delete;
	Fibo(wchar_t) = delete;

	// default copy and move constructors and assignments


	Fibo& operator+=(const Fibo& rhs);

	Fibo& operator&=(const Fibo& rhs);

	Fibo& operator|=(const Fibo& rhs);

	Fibo& operator^=(const Fibo& rhs);

	Fibo& operator<<=(size_t n);

	friend bool operator<(const Fibo& lhs, const Fibo& rhs);

	friend bool operator==(const Fibo& lhs, const Fibo& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Fibo& fibo);


	size_t length() const;


private:
	boost::dynamic_bitset<> data;
	using size_type = decltype(data)::size_type;

	void normalize();
	void carryFibitToPrefix(size_type prefixEnd);
	void coalesceOnes(size_type i);
	void trimLeadingZeroes();
};

const Fibo& Zero();

const Fibo& One();

#endif //INC_3_FIBO_H
