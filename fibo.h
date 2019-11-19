#ifndef INC_3_FIBO_H
#define INC_3_FIBO_H

#include <iostream>
#include <string_view>
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include <boost/operators.hpp>

class Fibo: boost::addable<Fibo>, boost::andable<Fibo>, boost::orable<Fibo>, boost::xorable<Fibo>,
            boost::left_shiftable<Fibo>, boost::less_than_comparable<Fibo>, boost::equality_comparable<Fibo> {
public:
	Fibo& operator+=(const Fibo& rhs) {
		auto rhsDataSize = rhs.length();
		auto larger = std::max({length(), rhsDataSize});
		data.resize(larger + 1);

		int carry = 0;
		int suma;

		for (size_type i = rhs.length(); i --> 0; ) {
			suma = data[i] + rhs.data[i] + carry;
			carry = 0;

			switch (suma) {
				case -1: // -F[i] -> -F[i]
					data[i + 1] = false; // +F[i+1] -> (F[i] + F[i-1]) - F[i] = F[i-1]
					carry = 1; // -F[i-1] -> 0
					data[i] = false; // +0 -> 0
					break;

				case 2: // +2F[i] -> 2F[i]
					if (data[i + 1]) {
						data[i + 1] = false; // +F[i+1] -> F[i+2] + F[i]
						data[i + 2] = true; // -F[i+2] -> F[i]
					}
					else {
						data [i + 1] = true; // -F[i+1] -> -(F[i] + F[i-1]) + 2F[i] = F[i] - F[i-1]
						carry = -1; // +[i-1] -> F[i]
					}
					data[i] = true; // -F[i] -> 0
					break;

				case 3: // +3F[i] -> 3F[i]
					data[i + 1] = true; // -F[i+1] -> -(F[i] + F[i-1]) + 3F[i] = 2F[i] - F[i-1]
					data[i] = true; // -F[i] -> F[i] - F[i-1] = F[i-2]
					i--;
					carry = 1; // -F[i-2] -> 0
					break;

				default:
					data[i] = suma;
			}
		}
		if (carry)
			data[0] = true;

		normalize();
		return *this;
	}
	Fibo& operator&=(const Fibo& rhs) {
		auto smaller = std::min({length(), rhs.length()});
		data.resize(smaller);
		for (size_type i = 0; i != smaller; ++i)
			data[i] &= rhs.data[i];
		normalize();
		return *this;
	}
	Fibo& operator|=(const Fibo& rhs) {
		auto larger = std::max({length(), rhs.length()});
		data.resize(larger);
		for (size_type i = 0; i != rhs.length(); ++i)
			data[i] |= rhs.data[i];
		normalize();
		return *this;
	}
	Fibo& operator^=(const Fibo& rhs) {
		auto larger = std::max({length(), rhs.length()});
		data.resize(larger);
		for (size_type i = 0; i != rhs.length(); ++i)
			data[i] ^= rhs.data[i];
		normalize();
		return *this;
	}
	Fibo& operator<<=(size_t n) {
		data <<= n;
		return *this;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Fibo& fibo);

	size_t length() const {
		return data.size();
	}

	Fibo() = default;
//	Fibo(const Fibo&) = default;
//	Fibo(Fibo&&) = default;
//	Fibo& operator=(const Fibo&) = default;
//	Fibo& operator=(Fibo&&) = default;
	explicit Fibo(std::string_view s);
	Fibo(int n);

private:
	boost::dynamic_bitset<> data;
	using size_type = decltype(data)::size_type;
	void normalize();
	void trimLeadingZeroes();
};

const Fibo& Zero();

const Fibo& One();

#endif //INC_3_FIBO_H
