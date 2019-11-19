#include "fibo.h"

Fibo::Fibo(std::string_view s) {
	assert(*s.begin() != '0');
	for (size_t i = s.length(); i --> 0; ) {
		assert(s[i] == '1' || s[i] == '0');
		data.push_back(s[i] == '1');
	}
	normalize();
}

// TODO: doodać template zamiast int, sprawdzić czy nic się nie powaliło z indeksami
Fibo::Fibo(int n) {
	assert(n >= 0);
	if (n > 0) {
		int f1 = 1, f2 = 2;
		size_t i = 1;
		for (; f2 <= n; ++i) {
			int tmp = f2;
			f2 = f2 + f1;
			f1 = tmp;
		}
		data.resize(i);
		for (--i; n > 0; --i) {
			if (f1 <= n) {
				data[i] = true;
				n -= f1;
			}
			int tmp = f1;
			f1 = f2 - f1;
			f2 = tmp;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Fibo& fibo) {
	if (fibo.length())
		for (Fibo::size_type i = fibo.length(); i --> 0; )
			os << fibo.data[i];
	else
		os << "0";
	return os;
}

void Fibo::normalize() {
	// TODO

	trimLeadingZeroes();
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
	static const Fibo zero(1);
	return zero;
}

int main() {
	Fibo f1(23), f2(12);
	Fibo f3 = f1 + f2;
	std::cout << f3 << std::endl;
}