#ifndef BIGNUM_H
#define BIGNUM_H

#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

class BigNum
{

public:
	int len;
	int sign;
	int x[40001];
	BigNum();
	BigNum(const BigNum& x);
	BigNum operator+(const BigNum& );
	BigNum operator-(const BigNum& );
	BigNum operator*(const BigNum& );
	BigNum operator/(const BigNum& );
	friend ostream& operator<<(ostream &,const BigNum &);
	friend istream& operator>>(istream &,BigNum& );
			
};


#endif



