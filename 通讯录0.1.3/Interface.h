#ifndef INTERFACE_H
#define INTERFACE_H
#include<iostream>
#include<string>
#include"User.h"
#include"Manager.h"
using namespace std;

//主要是处理登录界面，提供登录或者注册接口;
class Interface {
public:
	Interface();
	~Interface();
	void Menu();
	void Display();
	User* Log_In_User();//登录函数
	bool Log_In_Manager();
	bool Register_User();//注册
	User* Search_User_ID(IN_PARAM string first);

};
#endif