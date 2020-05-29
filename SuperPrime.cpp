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
 * 											   * 
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
  	virtual bool isPrime() { 
  	  std::cout << "Prime's isPrime" << std::endl;
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
  	SuperPrime():Prime(0), pset(3) {  //为什么必须有？ 
  	}
  	SuperPrime(int n):Prime(n)/*使用了基类中的构造函数*/, pset(3) {
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
	  if (Prime::isPrime() /*使用了基类中的isPrime()*/&& pset.isAllPrime())
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
	set.add(&sp);//sp向父类转化了 
	set.add(&p);
    std::cout << "How many :" << set.count() << std::endl;
    
  return 0;
}
