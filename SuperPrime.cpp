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
//作业：面向对象设计以下框架的代码细节，程序能编译运行得到正确结果 
#include <iostream>
class Prime {
  public:
  	Prime():number(0) {
	}
  	Prime(int n):number(n) {
	}
	~Prime() {
	}
  	bool isPrime() { 
  	  //2到number-1的因子
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
  	  //集合的构造什么？ 
  	  N = new Prime*[size];
  	  this->size = size;
  	  index = 0;
	}
	~PrimeSet() {
  	  for (int i = 0; i < index; ++i)  //销毁对象 
		delete N[i]; 
	  delete[] N;
	}
	bool add(int n) {
	  if(index == size)  return false;
	  Prime *p = new Prime(n);
	  N[index] = p;
	  index += 1;
	  return true;//添加数 
	}
	bool isAllPrime() {
	  for(int i = 0; i < index; i++)
	    if (!N[i]->isPrime())
	      return false;
	  return true;//判断是否所有数都是素数 
	} 
  private:
  	Prime **N;
	int size, index;//size是大小，index是下标 
};
class SuperPrime {
  public:
  	SuperPrime():number(0), pset(3) {  //为什么必须有？ 
  	}
  	SuperPrime(int n):number(n), pset(3) {
  	  split();  //它就是构造对象 
	}
  	~SuperPrime() {
	}
  	bool isSuperPrime() {
  	  //怎么使用pset？ 
  	  Prime p(number);
	  if (p.isPrime() && pset.isAllPrime())
	    return true; 
  	  return false;
	}
  private:
  	const int number;
  	PrimeSet pset;
	void split() {   //工厂方法设计模式 
	  // number split into N
	  int temp = number;
	  int sum = 0;
	  int multi = 1;
	  int squareSum = 0;
	  while(temp > 0) {
	  	int n = temp % 10;
	  	temp /= 10;
	  	sum += n;
		multi *= n;
		squareSum += n*n; 
	  }
	  pset.add(sum);  //和/积/平方和为对象？ 
	  pset.add(multi);
	  pset.add(squareSum);
	}
};
class SuperPrimeSet {
  public:
  	SuperPrimeSet(int from, int to) {
  	  size = to - from;
  	  for (int i = from; i < to; i++)
  	    set[i-from] = new SuperPrime(i);
	}
  	~SuperPrimeSet() {
  	  for(int i = 0; i < size; i++)
  	    delete set[i];
	}
  	int count() {
  	  int count = 0;
  	  for (int i = 0; i < size; i++)
  	    if(set[i]->isSuperPrime())
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
  	SuperPrime **set;
  	int size, index;
};
int main() {
  SuperPrime sp(113);
  if (sp.isSuperPrime())
    std::cout << "113 is SuperPrime" << std::endl;
  else
    std::cout << "113 is NOT SuperPrime" << std::endl;
  return 0;
}
