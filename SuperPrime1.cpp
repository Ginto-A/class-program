#include <iostream>

class BigPrime{
public:
	BigPrime(int n) : num(n){ }
	virtual bool isPrime() const {
		int i;
		int number = num;
		for(i = 2; i < number; i++){
			if(number % i == 0) break;
		} 
		if(i != number) return false;
		return true;
	} 
private:
	const int num;
};
class BigSuperPrime : public BigPrime {
public:
	BigSuperPrime(int n) : BigPrime(n), num(n){ }
	virtual bool isPrime() const {
		if(BigPrime::isPrime()) return true;
	}
private:
	const int num;
};
class Set{
public:
	Set(int sz);
	~Set();
	bool add(BigPrime *bp);
	bool remove(BigPrime *bp);
	int count() const {
		int ret = 0;
		for(int i = 0; i < index; i++){
			if(pset[i]->isPrime()) ret++;
		}
		return ret;
	}
	int sum() const {
		return 0;
	}
private:
	BigPrime **pset;
	int size, index;	
};

int main() {
	Set set(1000);
	BigSuperPrime bp(2);
	set.add(&bp);
	std::cout << set.count() << std::endl;
	return 0;
}

Set::Set(int sz) : size(sz) {
	index = 0;
	pset = new BigPrime*[size];//分配存储空间 
}
Set::~Set() {
	delete[] pset;//回收存储空间 
}
bool Set::add(BigPrime *bp) {
	if(index > size) return false;
	pset[index] = bp;
	index++;//pset[index++] = bp;
	return true;
}
bool Set::remove(BigPrime *bp){
	if(index < 0) return false;
	delete bp;
	index--;
	return true;
}
