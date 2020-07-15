#include<iostream>
#include"User.h"
#include"Interface.h"
#include"Manager.h"
using namespace std;
extern User* gl_User_Head;
extern Manager man;

int main() {
	Interface test;
	test.Display();
	User t;
	//t.Display();
	return 0;
}