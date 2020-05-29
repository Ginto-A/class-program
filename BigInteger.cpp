#include<iostream>
#include<cstring>
#include<algorithm>
//#include<iomanip> 

#define MAXN 9999 	//每个元素的表示最大值 

class BigInteger{
public:
	BigInteger() : digit_len(0) { memset(digit, 0, sizeof(digit));}
	BigInteger(const int);
	BigInteger(BigInteger&);
	BigInteger &operator=(const BigInteger &);
	~BigInteger();
	
	friend std::istream &operator>>(std::istream&, BigInteger&);
	friend std::ostream &operator<<(std::ostream&, BigInteger&);
	
	BigInteger operator+(BigInteger&);
	BigInteger operator-(BigInteger&);
	BigInteger operator*(BigInteger&);
	BigInteger operator/(int&);
	BigInteger operator%(int&);
	bool operator>(const BigInteger&)const;
	bool operator>(const int &)const;
	bool operator==(const BigInteger&)const;
	bool operator!=(const BigInteger&)const;
private:
	int digit[500];//每个digit最大表示9999 
	int digit_len;
};
int main(){
	int a = 0;
	int b = 3;
	BigInteger bint(a);
	BigInteger bint2(b);
	BigInteger bint3;
//	int c = pow(10, 2);
//	std::cout << c <<std::endl;
	std::cout << bint <<std::endl;
	std::cout << bint2 <<std::endl;
	bint3 = bint + bint2;
	std::cout << bint3 <<std::endl;
//	bint3 = bint - bint2;
//	std::cout << bint3 <<std::endl;
	
	return 0;
}
BigInteger::BigInteger(const int n){
	int i = 0;
	int number = n;
	memset(digit, 0, sizeof(digit));
	for(i = 0; number > MAXN; i++){ 
		digit[i] = number % (MAXN + 1);
		number /= (MAXN + 1);
	}
	digit[i] = number;
	digit_len = i + 1;
}
BigInteger::BigInteger(BigInteger& bint){
	int i = 0;
	memset(digit, 0, sizeof(digit));
	digit_len = bint.digit_len;
	for(i = 0; i < digit_len; i++){ 
		digit[i] = bint.digit[i];
	}
}
BigInteger & BigInteger::operator=(const BigInteger & bint){
	digit_len = bint.digit_len;
	memset(digit, 0, sizeof(digit));
	int i;
	for(i = 0; i < digit_len; i++){
		digit[i] = bint.digit[i];
	}
	return *this;
}

BigInteger::~BigInteger(){
}
std::istream &operator>>(std::istream& in, BigInteger& bint){
	char c[500];//先作为字符存储，在逐位转换 
	std::cin >> c;
	int len = strlen(c);
	int i, j;
	int index = 0;
	for(i = len - 1; i > 0; ){
		for(j = 0; j < 4 && i >= 0; j++, i--){
			bint.digit[index] += (c[i] - '0') * pow(10, j);
		}
		index++;
	}
	bint.digit_len = index;
	return in;
}
std::ostream &operator<<(std::ostream& out, BigInteger& bint){
	int i;
	for(i = bint.digit_len - 1; i >= 0; i--){
		if(bint.digit[i] == 0 && bint.digit[bint.digit_len - 1] != 0) 
			std::cout << 0 << 0 << 0 << 0; //当该位为0且不是整个大数字不是0时 
		else if(bint.digit[i] < 10 && i != bint.digit_len - 1) 
			std::cout << 0 << 0 << 0 << bint.digit[i];
		else if(bint.digit[i] < 100 && i != bint.digit_len - 1) 
			std::cout << 0 << 0 << bint.digit[i];
		else if(bint.digit[i] < 1000 && i != bint.digit_len - 1) 
			std::cout << 0 << bint.digit[i];
		else std::cout << bint.digit[i];
	}
	return out;
}
BigInteger BigInteger::operator+(BigInteger& bint){
	BigInteger sum(*this);//this为第一个运算数，bint为第二个运算数 
	int i = 0;
	for(i = 0; i < sum.digit_len && i < bint.digit_len; i++){
		if(sum.digit[i] + bint.digit[i] > MAXN){
			sum.digit[i+1] += 1;	//进位 
			sum.digit[i] = (sum.digit[i] + bint.digit[i]) % (MAXN + 1); 
		}else{
			sum.digit[i] = sum.digit[i] + bint.digit[i];
		}	
	}
	return sum;
}
BigInteger BigInteger::operator-(BigInteger& bint){
	BigInteger difference(*this);//this为第一个运算数，bint为第二个运算数 
	int i = 0;
	if(difference > bint){
		for(i = 0; i < difference.digit_len && i < bint.digit_len; i++){
			if(difference.digit[i] - bint.digit[i] < 0){
				difference.digit[i+1] -= 1;	//借位 
				difference.digit[i] = difference.digit[i] + MAXN + 1 - bint.digit[i]; 
			}else{
				difference.digit[i] = difference.digit[i] - bint.digit[i];
			}	
		}
	} else{
		for(i = 0; i < difference.digit_len && i < bint.digit_len; i++){
			if(bint.digit[i] - difference.digit[i] < 0){
				bint.digit[i+1] -= 1;	//借位 
				bint.digit[i] = bint.digit[i] + MAXN + 1 - difference.digit[i]; 
			}else{
				bint.digit[i] = bint.digit[i] - difference.digit[i];
			}	
		}
		bint.digit[bint.digit_len - 1] = 0 - bint.digit[bint.digit_len - 1];
		difference = bint;
	}
	while(difference.digit[difference.digit_len-1] == 0 && difference.digit_len > 1) 
			difference.digit_len --;//消除-运算后的0位 
	return difference;
}
BigInteger BigInteger::operator*(BigInteger& bint){
	BigInteger multi;
	int i, j, carry;
	int temp;//不使用temp而直接使用表达式出现数据错误，猜测 
	for(i = 0; i < digit_len; i++){
		carry = 0;
		for(j = 0; j < bint.digit_len; j++){
			temp = digit[i] * bint.digit[j] + multi.digit[i + j] + carry;
			if(temp > MAXN){
				carry =  temp / (MAXN + 1);
				multi.digit[i + j] = temp % (MAXN + 1);
			}else{
				carry = 0;
				multi.digit[i + j] = temp;
			}
		}
		if(carry != 0) multi.digit[i + j] = carry;
	}
	multi.digit_len = i + j;
	while(multi.digit[multi.digit_len-1] == 0 && multi.digit_len > 1) 
		multi.digit_len --;//消除0位
	return multi;
}
BigInteger BigInteger::operator/(int & num){
	BigInteger quotient;
	int i, remainder = 0;
	for(i = digit_len - 1; i >= 0; i--){
		if((digit[i] + remainder * (MAXN + 1)) % num == 0) {
			quotient.digit[i] = (digit[i] + remainder * (MAXN + 1)) / num;
		}else {
			quotient.digit[i] = (digit[i] + remainder * (MAXN + 1)) / num;
			remainder = (digit[i] + remainder * (MAXN + 1)) % num;
		}
	}
	quotient.digit_len = digit_len;	
	while(quotient.digit[quotient.digit_len-1] == 0 && quotient.digit_len > 1) 
		quotient.digit_len --;//消除0位
	return quotient; 
}
BigInteger BigInteger::operator%(int & num){
	BigInteger remainder;
	int i, Remainder = 0;
	for(i = digit_len - 1; i >= 0; i--){
		if((digit[i] + Remainder * (MAXN + 1)) % num == 0) {
			Remainder = 0;
		}else {
			Remainder = (digit[i] + Remainder * (MAXN + 1)) % num;
		}
	}
	remainder.digit_len = digit_len;	
	while(remainder.digit[remainder.digit_len-1] == 0 && remainder.digit_len > 1) 
		remainder.digit_len --;//消除0位
	return remainder;
}
bool BigInteger::operator>(const BigInteger & bint)const{ 
	int len; 
	if(digit_len > bint.digit_len)
		return true; 
	else if(digit_len == bint.digit_len)
	{ 
		len = digit_len - 1; 
		while(digit[len] == bint.digit[len] && len >= 0)
			len--; 
		if(len >= 0 && digit[len] > bint.digit[len])
			return true; 
		else
			return false; 
	} 
	else
		return false; 
}
bool BigInteger::operator>(const int & num) const{
	BigInteger number(num);
	return *this > number;
}
bool BigInteger::operator==(const BigInteger & num) const{
	if(digit_len != num.digit_len) return false;
	int i;
	for(i = digit_len - 1; i >= 0; i--){
		if(digit[i] != num.digit[i]) return false;
	}
	return true;
}
bool BigInteger::operator!=(const BigInteger & num) const{
	if(*this == num) return false;
	return true;
}
