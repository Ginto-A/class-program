#include <iostream>
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
	static Anything* create() {		//�����������ģʽ
		return new Anything();
	}
	static Anything* createGroup(int n) {		//�����������ģʽ
		return new Anything[n];
	}
private:
	static int count;//���������
	const int things;//const�����޸� 
	Anything() : things(0) {	//˽�л����캯�� 
		count += 1;
	}
};
int Anything::count = 0;//count��static���Σ������࣬�����ڶ��󣬹������

int main() {
	//���캯��δ˽�л�ʱ 
	//Anything a, b, c;
	//c.show();//��������3����Ϊ������3������ÿ�ι���count+1
	//Anything* p = new Anything;
	//c.show();//��������4����Ϊnew��һ���¶���
	//delete p;
	//c.show();//��������3��p��delete������count-1
	
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

