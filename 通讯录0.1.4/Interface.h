#ifndef INTERFACE_H
#define INTERFACE_H
#include<iostream>
#include<string>
#include"User.h"
#include"Manager.h"
using namespace std;

//��Ҫ�Ǵ����¼���棬�ṩ��¼����ע��ӿ�;
class Interface {
public:
	Interface();
	~Interface();
	void Menu();
	void Display();
	User* Log_In_User();//��¼����
	bool Log_In_Manager();
	bool Register_User();//ע��
	User* Search_User_ID(IN_PARAM string first);

};
#endif