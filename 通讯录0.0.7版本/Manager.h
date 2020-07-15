#ifndef MANAGER_H
#define MANAGER_H
#define IN_PARAM   //入口参数
#define OUT_PARAM  //出口参数
#include<iostream>
#include<string>
#include"User.h"
using namespace std;

class Manager
{
public:
    Manager() { Manager_id = "scu_seventh"; Manager_Pwd = "666666"; }//管理员的账户与密码
    bool Is_Manager(IN_PARAM string strIdInput, IN_PARAM string strPwdInput);
    void Del_User(IN_PARAM string str);
    void Show_User();
    int Get_Sum();
    void Push();
    void Menu();
    void Change_Pwd();
    void Display();
    User* Link_bet_User_Manager; //用于删除用户的指针
private:
    string Manager_id;
    string Manager_Pwd;
};

#endif