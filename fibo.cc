#include <iostream>
#include <vector>

#include "fibo.h"

Fibo::Fibo(std::string_view s) {
	assert(*s.begin() != '0');
	for (size_t i = s.length() - 1; i >= 0; i--) {
		assert(s[i] == '1' || s[i] == '0');
		data.push_back(s[i] == '1');
	}
	normalize();
}

// TODO: doodać template zamiast int, sprawdzić czy nic się nie powaliło z indeksami
Fibo::Fibo(int n) {
	assert(n >= 0);
	if (n > 0) {
		int f1 = 1, f2 = 2, i = 1;
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


//normalizacja powinna trimować zera wiodące
void Fibo::normalize() {
	// TODO

	trimLeadingZeroes();
}

void Fibo::trimLeadingZeroes() {
	int i = data.size();
	while (!data[--i]);
	data.resize(i + 1);
}

int main() {
	Fibo f1(23), f2(12);
}