#ifndef INC_3_FIBO_H
#define INC_3_FIBO_H

#include <boost/dynamic_bitset.hpp>
#include <boost/operators.hpp>
#include <utility>

class Fibo: boost::addable<Fibo>, boost::andable<Fibo>, boost::orable<Fibo>, boost::xorable<Fibo>,
            boost::left_shiftable<Fibo>, boost::less_than_comparable<Fibo>, boost::equality_comparable<Fibo> {
public:
	Fibo& operator+=(const Fibo& rhs) {
		// TODO
	}
	Fibo& operator&=(const Fibo& rhs) {
		if (rhs.data.size() > this->data.size())
			this->data.resize(rhs.data.size());
		this->data &= rhs.data;
		return *this;
	}
	Fibo& operator|=(const Fibo& rhs) {
		decltype(data)::size_type smaller, larger;
		if (this->data.size() > rhs.data.size()) {
			smaller = rhs.data.size();
			larger = this->data.size();
		}
		else {
			smaller = this->data.size();
			larger = rhs.data.size();
		}
		this->data.resize(larger);
		for (decltype(smaller) i = 0; i != smaller; ++i)
			this->data[i] |= rhs.data[i];
		return *this;
	}
	Fibo& operator^=(const Fibo& rhs) {
		decltype(data)::size_type smaller, larger;
		if (this->data.size() > rhs.data.size()) {
			smaller = rhs.data.size();
			larger = this->data.size();
		}
		else {
			smaller = this->data.size();
			larger = rhs.data.size();
		}
		this->data.resize(larger);
		for (decltype(smaller) i = 0; i != smaller; ++i)
			this->data[i] ^= rhs.data[i];
		return *this;
	}
	Fibo& operator<<=(size_t n) {
		this->data <<= n;
		return *this;
	}

	size_t length() {
		return data.size();
	}

private:
	boost::dynamic_bitset<> data;
	void normalize();

//	explicit Fibo(boost::dynamic_bitset<> d) : data(std::move(d)) {}
};

#endif //INC_3_FIBO_H
