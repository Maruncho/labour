#include <iostream>
using namespace std;

class B1 {
public:
	virtual void vf() { cout << "B1::vf() "; }
	void f() { cout << "B1::f() "; }
	virtual void pvf() = 0;
};

class D1 : public B1 {
public:
	void vf() { cout << "D1::vf() "; }
	void f() { cout << "D1::f() "; }
};

class D2 : public D1 {
public:
	void pvf() { cout <<"D2::pvf() "; }
};

class B2 {
public:
	virtual void pvf() = 0;
};

class D21 : public B2 {
public:
	string str = "D21::str ";
	void pvf() { cout << str; }

};

class D22 : public B2 {
public:
	int num = 22;
	void pvf() { cout << num << " "; }
};

void f(B2& b) {
	b.pvf();
}

int main() {

	D2 d2;


	d2.vf();
	d2.f();
	d2.pvf();
	D21 d21;
	D22 d22;
	f(d21);
	f(d22);
}