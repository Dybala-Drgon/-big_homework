#ifndef MANAGER_H
#define MANAGER_H
#define IN_PARAM   //��ڲ���
#define OUT_PARAM  //���ڲ���
#include<iostream>
#include<string>
#include"User.h"
using namespace std;

class Manager
{
public:
    Manager() { Manager_id = "scu_seventh"; Manager_Pwd = "666666"; }//����Ա���˻�������
    bool Is_Manager(IN_PARAM string strIdInput, IN_PARAM string strPwdInput);
    void Del_User(IN_PARAM string str);
    void Show_User();
    int Get_Sum();
    void Menu();
    void Change_Pwd();
    void Display();
    User* Link_bet_User_Manager; //����ɾ���û���ָ��
    void Push();//ʵ�����͹��ܵĺ���
    void SaveUser();
    User* Search_User_Precise(IN_PARAM string StrScan);//�����û�
private:
    string Manager_id;
    string Manager_Pwd;
};

#endif