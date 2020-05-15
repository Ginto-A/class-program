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
class SuperPrime : public Prime {
  public:
  	SuperPrime():Prime(0){  //为什么必须有？ 
  	}
  	SuperPrime(int n):Prime(n){
	  // number split into N
	  int temp = n;
	  int SUm = 0;
	  int MUlti = 1;
	  int SQuareSum = 0;
	  while(temp > 0) {
	  	int t = temp % 10;
	  	temp /= 10;
	  	SUm += t;
		MUlti *= t;
		SQuareSum += (t * t);	
	  } 
	  sum = new Prime(SUm);
	  multi = new Prime(MUlti);
	  squareSum = new Prime(SQuareSum); 
	}
  	~SuperPrime() {
  		delete sum;
  		delete multi;
  		delete squareSum;
	}
  	bool isPrime() {   //类/对象的接口，更抽象说是外观 
	  if (Prime::isPrime() && sum->isPrime() && multi->isPrime() && squareSum->isPrime())
	    return true; 
  	  return false;
	}
  private:
	Prime *sum; 
	Prime *multi;
	Prime *squareSum;
};
int main() {
  SuperPrime sp(113);
  if (sp.isPrime())
    std::cout << "113 is SuperPrime" << std::endl;
  else
    std::cout << "113 is NOT SuperPrime" << std::endl;
  return 0;
}
