/*********************************************** 
 * 一个对象不可能完成所有的事情 -> 聚合与继承  * 
 * 对象之间相互利用以节约成本	-> 代码复用    * 
 * 											   * 
 * 关系的学习 								   * 
 * 	一、聚合中，对象的生成、销毁及使用		   * 
 * 	二、继承中，对象的生成、销毁及使用		   * 
 * 	三、继承中，对象的重复利用、对象的扩选 	   * 
 * 代码复用									   * 
 * 	一、拷贝/粘贴 							   * 
 *	二、库函数								   * 
 * 
 ***********************************************/
//作业：完成以下框架的代码细节，程序能编译运行得到正确结果 
#include <iostream>
class SuperPrime {
  public:
  	SuperPrime():number(0) {
  		size = 0;
	}
	SuperPrime(int n):number(n) {
		size = 0;
		split();//它就是构造对象 
	}
  	~SuperPrime() {
  		int i;
		for (i = 0; i < size; i++){//销毁对象 
			delete N[i];
		} 
	}
  	bool isSuperPrime() {
  	  split();	//分割出来的数字是对象？ 
  	  SuperPrime a(sum());		//将普通整数对象化 
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
	void split() { //工厂方法设计模式 
		// number split into N
		int temp = number;
		while(temp > 0) {
			int n = temp % 10;
			temp /= 10;
			N[size] = new SuperPrime(n);//构造对象 
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
