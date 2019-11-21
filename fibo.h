#ifndef INC_3_FIBO_H
#define INC_3_FIBO_H

#include <iostream>
#include <string_view>
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include <boost/operators.hpp>

class Fibo: boost::addable<Fibo>, boost::bitwise<Fibo>,
            boost::left_shiftable<Fibo, size_t>, boost::totally_ordered<Fibo> {
public:
    Fibo() = default;

	Fibo(const Fibo&) = default;

	Fibo(Fibo&&) = default;

    explicit Fibo(std::string_view s);

    Fibo(long long int n);

    Fibo& operator=(const Fibo&) = default;

    Fibo& operator=(Fibo&&) = default;

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
	void moveFibitOnSuffix(size_type suffixBegin) ;
	void trimLeadingZeroes();
};

const Fibo& Zero();

const Fibo& One();

#endif //INC_3_FIBO_H
