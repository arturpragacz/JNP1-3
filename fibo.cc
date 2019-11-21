#include "fibo.h"

#include <algorithm>

Fibo::Fibo(std::string_view s) {
	assert(s.begin());
	assert(*s.begin() != '0');
	for (size_t i = s.length(); i --> 0; ) {
		assert(s[i] == '1' || s[i] == '0');
		data.push_back(s[i] == '1');
	}
	normalize();
}


Fibo& Fibo::operator+=(const Fibo& rhs) {
	auto larger = std::max({length(), rhs.length()});
	data.resize(larger + 1);

	int carry = 0;
	int sum;

	for (size_type i = rhs.length(); i --> 0; ) {
		sum = data[i] + rhs.data[i] + carry;
		carry = 0;

		switch (sum) {
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
				if (i > 0)
					i--;
				carry = 1; // -F[i-2] -> 0
				break;

			default:
				data[i] = sum;
		}
	}
	if (carry == 1)
		data[0] = true;
	else if (carry == -1)
		data[0] = false;

	normalize();
	return *this;
}

Fibo& Fibo::operator&=(const Fibo& rhs) {
	auto smaller = std::min({length(), rhs.length()});
	data.resize(smaller);
	for (size_type i = 0; i != smaller; ++i)
		data[i] &= rhs.data[i];
	normalize();
	return *this;
}

Fibo& Fibo::operator|=(const Fibo& rhs) {
	auto larger = std::max({length(), rhs.length()});
	data.resize(larger);
	for (size_type i = 0; i != rhs.length(); ++i)
		data[i] |= rhs.data[i];
	normalize();
	return *this;
}

Fibo& Fibo::operator^=(const Fibo& rhs) {
	auto larger = std::max({length(), rhs.length()});
	data.resize(larger);
	for (size_type i = 0; i != rhs.length(); ++i)
		data[i] ^= rhs.data[i];
	normalize();
	return *this;
}

Fibo& Fibo::operator<<=(size_t n) {
	data.resize(length() + n);
	data <<= n;
	return *this;
}

bool operator==(const Fibo& lhs, const Fibo& rhs) {
	return lhs.data == rhs.data;
}

bool operator<(const Fibo& lhs, const Fibo& rhs) {
	if (lhs.length() != rhs.length())
		return lhs.length() < rhs.length();
	Fibo::size_type i = lhs.length();
	while(i --> 0) {
		if (lhs.data[i] < rhs.data[i])
			return true;
		else if (lhs.data[i] > rhs.data[i])
			return false;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Fibo& fibo) {
	if (fibo.length() > 0)
		os << fibo.data;
	else
		os << "0";
	return os;
}


size_t Fibo::length() const {
	return data.size();
}


void Fibo::normalize() {
	data.resize(length() + 1);
	for (Fibo::size_type i = length() - 2; i --> 0; ) {
		if (data[i] && data[i + 1]) {
			coalesceOnes(i);
			carryFibitToPrefix(i + 2);
		}
	}

	trimLeadingZeroes();
}

void Fibo::carryFibitToPrefix(size_type prefixEnd) {
	for (size_type i = prefixEnd; i + 2 < length() && data[i + 1]; i += 2)
		coalesceOnes(i);
}

void Fibo::coalesceOnes(size_type i) {
	data[i + 2] = true;
	data[i + 1] = false;
	data[i] = false;
}

void Fibo::trimLeadingZeroes() {
	size_type i = length();
	while (i --> 0) {
		if (data[i])
			break;
	}
	data.resize(i + 1);
}


const Fibo& Zero() {
	static const Fibo zero(0);
	return zero;
}

const Fibo& One() {
	static const Fibo one(1);
	return one;
}