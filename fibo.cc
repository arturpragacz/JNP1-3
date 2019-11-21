#include "fibo.h"

Fibo::Fibo(std::string_view s) {
	assert(*s.begin() != '0');
	for (size_t i = s.length(); i --> 0; ) {
		assert(s[i] == '1' || s[i] == '0');
		data.push_back(s[i] == '1');
	}
	normalize();
}

Fibo::Fibo(long long int n) {
	assert(n >= 0);
	if (n > 0) {
		long long int f1 = 1, f2 = 2;
		size_t i = 1;
		for (; f2 <= n; ++i) {
			long long int tmp = f2;
			f2 = f2 + f1;
			f1 = tmp;
		}
		data.resize(i);
		for (--i; n > 0; --i) {
			if (f1 <= n) {
				data[i] = true;
				n -= f1;
			}
			long long int tmp = f1;
			f1 = f2 - f1;
			f2 = tmp;
		}
	}
}


Fibo& Fibo::operator+=(const Fibo& rhs) {
	auto rhsDataSize = rhs.length();
	auto larger = std::max({length(), rhsDataSize});
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
				i--;
				carry = 1; // -F[i-2] -> 0
				break;

			default:
				data[i] = sum;
		}
	}
	if (carry)
		data[0] = true;

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

std::ostream& operator<<(std::ostream& os, const Fibo& fibo) {
	if (fibo.length() > 0)
		os << fibo.data;
	else
		os << "0";
	return os;
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
	}
	return false;
}


size_t Fibo::length() const {
	return data.size();
}


void Fibo::normalize() {
	for (Fibo::size_type i = length() - 1; i --> 0; ) {
		if (data[i] && data[i + 1]) {
			data[i] = false;
			data[i + 1] = false;
			if (length() > i + 2) {
				data[i + 2] = true;
				moveFibitOnSuffix(i + 2);
			} else {
				data.append(true);
			}
		}
	}

	trimLeadingZeroes();
}

void Fibo::moveFibitOnSuffix(size_type suffixBegin) {
	size_type i = suffixBegin;
	while (i + 1 < length() && data[i + 1]) {
		data[i] = false;
		data[i + 1] = false;
		if (length() > i + 2) {
			data[i + 2] = true;
			moveFibitOnSuffix(i + 2);
		} else {
			data.append(true);
		}
		i += 2;
	}
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