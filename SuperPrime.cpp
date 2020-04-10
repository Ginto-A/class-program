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
 * 
 ***********************************************/
//��ҵ��������¿�ܵĴ���ϸ�ڣ������ܱ������еõ���ȷ��� 
#include <iostream>
class SuperPrime {
  public:
  	SuperPrime():number(0) {
  		size = 0;
	}
	SuperPrime(int n):number(n) {
		size = 0;
		split();//�����ǹ������ 
	}
  	~SuperPrime() {
  		int i;
		for (i = 0; i < size; i++){//���ٶ��� 
			delete N[i];
		} 
	}
  	bool isSuperPrime() {
  	  split();	//�ָ�����������Ƕ��� 
  	  SuperPrime a(sum());		//����ͨ�������� 
	  SuperPrime b(multi());	
	  SuperPrime c(squareSum());
	  if (isPrime() && a.isPrime() && b.isPrime() && c.isPrime())
	    return true; 
  	  return false;
	}
  private:
  	const int number;
  	SuperPrime *N[100];
	int size;
  	bool isPrime() {
  		int i = 2;
		for(i = 2; i < number; i++){
    		if(number % i == 0){
    			break;
			}
		}
		if(i == number) return true;
		return false;
	}
	void split() { //�����������ģʽ 
		// number split into N
		int temp = number;
		while(temp > 0) {
			int n = temp % 10;
			temp /= 10;
			N[size] = new SuperPrime(n);//������� 
			size += 1;
		}
	}
	int sum() {
		return 0;
	}
	int multi() {
		return 0;
	}
	int squareSum() {
		return 0;
	}
};
class Set {
  public:
  	Set(int from, int to) {
  	  size = 0;
	}
  	~Set() {
	}
  	int count() {
  	  int count = 0;
  	  for (int i = 0; i < size; i++)
  	    if(set[i].isSuperPrime())
  	      count += 1;
	  return count; 
	}
  	int sum() {
  	  int sum = 0;
  	  /*
  	  for (int i = 0; i < size; i++)
  	    if(set[i].isSuperPrime())
  	      sum += set[i];
  	      */ 
	  return sum; 
	}
  private:
  	SuperPrime set[1000];
  	int size;
};
int main() {
  SuperPrime sp(113);
  if(sp.isSuperPrime()) std::cout << "113 is SuperPrime" << std::endl;
  else std::cout << "113 is NOT SuperPrime" << std::endl;
  return 0;
} 