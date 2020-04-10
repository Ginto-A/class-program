#include <iostream>//����
class Anything
{
public:
	~Anything() {
		count -= 1;
	}
	void show(int a) const {
		std::cout << "How many Object:" << count << std::endl;
	}
	static void show() {
		std::cout << "How many Object:" << count << std::endl;
	}
	static Anything* create() {		//工厂方法设计模式
		return new Anything();
	}
	static Anything* createGroup(int n) {		//工厂方法设计模式
		return new Anything[n];
	}
private:
	static int count;//对象计数�
	const int things;//const不可修改 
	Anything() : things(0) {	//私有化构造函�
		count += 1;
	}
};
int Anything::count = 0;//count有static修饰，属于类，不属于对象，共享变�

int main() {
	//构造函数未私有化时 
	//Anything a, b, c;
	//c.show();//输出结果�，因为创建了3个对象，每次构造count+1
	//Anything* p = new Anything;
	//c.show();//输出结果�，因为new了一个新对象
	//delete p;
	//c.show();//输出结果�，p被delete，析构count-1
	
	Anything *p = Anything::create();
	p->show();//1
	Anything *pp = Anything::createGroup(10);
	Anything::show();//11
	delete p;
	Anything::show();//10
	delete[] pp;
	Anything::show();//0

	return 0;
}

