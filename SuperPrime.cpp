/*********************************************** 
 * һ�����󲻿���������е����� -> �ۺ���̳�  * 
 * ����֮���໥�����Խ�Լ�ɱ�	-> ���븴��    * 
 * 											   * 
 * ��ϵ��ѧϰ 								   * 
 * 	һ���ۺ��У���������ɡ����ټ�ʹ��		   * 
 * 	�����̳��У���������ɡ����ټ�ʹ��		   * 
 * 	�����̳��У�������ظ����á��������ѡ 	   * 
 * ���븴��									   * 
 * 	һ������/ճ�� 							   * 
 *	�����⺯��								   * 
 * 											   * 
 ***********************************************/
//��ҵ���������������¿�ܵĴ���ϸ�ڣ������ܱ������еõ���ȷ��� 
#include <iostream>
class Prime {
  public:
  	Prime():number(0) {
	}
  	Prime(int n):number(n) {
	}
	~Prime() {
	}
  	virtual bool isPrime() { 
  	  std::cout << "Prime's isPrime" << std::endl;
	//2��number-1������ 
  	  int i;
		for(i = 2; i < number; i++){
			if(number % i == 0) break;
		} 
		if(i != number) return false;
		return true;
	}
  private:
  	const int number;
};
class PrimeSet {
  public:
  	PrimeSet(int size) {
  	  //���ϵĹ���ʲô�� 
  	  set = new Prime*[size];
  	  this->size = size;
  	  index = 0;
	}
	~PrimeSet() { 
	  delete[] set;
	}
 	int count() {
  	  int count = 0;
  	  for (int i = 0; i < index; i++)
  	    if(set[i]->isPrime())
  	      count += 1;
	  return count; 
	}
	bool add(Prime *p) {
	  if(index == size)  return false;
	  set[index] = p;
	  index += 1;
	  return true;
	}
	bool isAllPrime() {
	  for(int i = 0; i < index; i++)
	    if (!set[i]->isPrime())
	      return false;
	  return true;
	} 
  private:
  	Prime **set;
	int size, index;
}; 
class SuperPrime : public Prime {
  public:
  	SuperPrime():Prime(0), pset(3) {  //Ϊʲô�����У� 
  	}
  	SuperPrime(int n):Prime(n)/*ʹ���˻����еĹ��캯��*/, pset(3) {
	  // number split into N
	  int temp = n;
	  int sum = 0;
	  int multi = 1;
	  int squareSum = 0;
	  while(temp > 0) {
	  	int n = temp % 10;
	  	int t = temp % 10;
	  	temp /= 10;
	  	sum += n;
		multi *= n;
		squareSum += n*n; 
	  } 
	  Prime Sum(sum);
	  Prime Multi(multi);
	  Prime SquareSum(squareSum);
	  pset.add(&Sum);
	  pset.add(&Multi);
	  pset.add(&SquareSum);
	}
  	~SuperPrime() {
	}
  	virtual bool isPrime() {
	  std::cout << "SuperPrime's isPrime" << std::endl;
	  if (Prime::isPrime() /*ʹ���˻����е�isPrime()*/&& pset.isAllPrime())
	    return true; 
  	  return false;
	}
  private:
  	PrimeSet pset;
};
int main() {
	Prime p(13);
	SuperPrime sp(113);
	PrimeSet set(2);
	set.add(&sp);//sp����ת���� 
	set.add(&p);
    std::cout << "How many :" << set.count() << std::endl;
    
  return 0;
}
