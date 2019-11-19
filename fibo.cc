#include <iostream>
#include <vector>

#include "fibo.h"

Fibo::Fibo() {
    data = boost::dynamic_bitset<>(1);
}

Fibo::Fibo(const std::string& str) {
    data = boost::dynamic_bitset<>();
    for (size_t i = str.length() - 1; i >= 0; i--) {
        assert(str[i] == '1' || str[i] == '0');
        data.append(str[i] == '1');
    }
    normalize();
}

Fibo::Fibo(const char* str) {
    data = boost::dynamic_bitset<>();
    int len = strlen(str);
    for (size_t i = len - 1; i >= 0; i--) {
        assert(str[i] == '1' || str[i] == '0');
        data.append(str[i] =='1');
    }
    normalize();
}

// TODO: doodać template zamiast int, sprawdzić czy nic się nie powaliło z indeksami
Fibo::Fibo(int n){
    if (n == 0) {
        Fibo();
    } else {
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

Fibo::Fibo(const Fibo& f) {
    data = boost::dynamic_bitset<>(f.data);
}

//normalizacja powinna trimować zera wiodące
void Fibo::normalize() {

}