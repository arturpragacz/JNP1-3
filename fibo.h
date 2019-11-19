#ifndef INC_3_FIBO_H
#define INC_3_FIBO_H

#include <boost/dynamic_bitset.hpp>
#include <string>

class Fibo {
public:
    Fibo();
    Fibo(const std::string&);
    Fibo(const char*);
    Fibo(int);
    Fibo(const Fibo&);

private:
	boost::dynamic_bitset<> data;
	void normalize();
};

Fibo Zero();
Fibo One();

#endif //INC_3_FIBO_H
