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
		while (f2 <= n) {
			int helper = f2;
			f2 += f1;
			f1 = helper;
			i++;
		}
		data = boost::dynamic_bitset<>(i);
		while (n > 0) {
			if (f1 <= n) {
				data[i] = true;
				n -= f1;
			}
			i--;
			int helper = f1;
			f1 = f2 - f1;
			f2 = f1;
		}
	}
}


//normalizacja powinna trimować zera wiodące
void Fibo::normalize() {

}

void Fibo::trimLeadingZeroes() {
	int i = data.size();
	while (!data[--i]);
	data.resize(i + 1);
}

int main() {
	Fibo f;
	std::cout << f.length();
}