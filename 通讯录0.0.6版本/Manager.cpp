#include "Manager.h"
#include"User.h"
#include<iostream>
#include<string>
using namespace std;
extern User* gl_User_Head;
extern Manager man;

bool Manager::Is_Manager(IN_PARAM string strIdInput, IN_PARAM string strPwdInput)
{
    if (strIdInput ==Manager_id && strPwdInput == Manager_Pwd)
    {
        return true;
    }
    return false;
}

void Manager::Del_User(IN_PARAM string str)
{
    User* key = gl_User_Head;
    if (NULL == key->User_Next)
    {
        cout << "通讯录为空" << endl;
        system("pause");
        return;
    }
    
    
    while (key != NULL) {
        if (key->User_phone_num == str) {
            //找到了删除的元素
            User* temp = gl_User_Head;
            while (temp->User_Next != key)
                temp = temp->User_Next;
            temp->User_Next = key->User_Next;
            delete key;
            cout << "删除成功" << endl;
            system("pause");
            return;
        }
        key = key->User_Next;
    }
    cout << "查无此人" << endl;
    system("pause");
}

void Manager::Show_User()
{
    User* key = gl_User_Head->User_Next;
    cout << "当前用户账号" << endl;
    while (NULL != key) {
        cout << key->User_phone_num << endl;
        key = key->User_Next;
    }
    system("pause");
}

void Manager::Push()
{
}

void Manager::Menu()
{
   
        cout << " | ***********欢迎进入通讯录管理系统*************|" << endl;
        cout << " | ----------------------------------------------|" << endl;
        cout << " | ************----管理员模式----****************|" << endl;
        cout << " | ----------------------------------------------|" << endl;
        cout << " | *********  (键入对应编号进入相应模块)  *******|" << endl;
        cout << " | 1——查看总数            2——删除用户        |" << endl;
        cout << " | ----------------------------------------------|" << endl;
        cout << " | 3——推送用户            4——保存信息        |" << endl;
        cout << " | ----------------------------------------------|" << endl;
        cout << " | 5——显示所有用户                             |" << endl;
        cout << " | -----------------按0退出----------------------|" << endl;
}

void Manager::Display()
{
    int n, key = 0, lab = 0;	//key控制退出，lab控制清屏
    for (;;) {
        if (lab == 0) {
            system("cls");		    //清屏
            Menu();		//重新打印菜单
        }
        cin >> n;
        getchar(); //吃掉回车
        switch (n)
        {
        case 1:
            cout << "当前的用户总人数" << endl;
            cout << Get_Sum() << endl;
            system("pause");
            lab = 0;
            break;
        case 2:	
        {
            cout << "输入删除的id" << endl;
            string str_del_id;
            cin >> str_del_id;
            getchar();
            Del_User(str_del_id);
            lab = 0;
            break;
        }
        case 3:
            lab = 0;
            break;
        case 4:
            lab = 0;
            break;
        case 5:
            Show_User();
            lab = 0;
            break;
        case 0:
            key++;
            break;
        default:
            cout << "输入有误，重新输入" << endl;
            lab++;
            break;
        }
        if (key != 0)
            break;//按0退出
    }
}

int Manager::Get_Sum()    //打印用户总数，
{
    int num = 0;
    User* key = gl_User_Head->User_Next;
    while (NULL != key) {
        num++;
        key = key->User_Next;
    }
    return num;
}

void Manager::Change_Pwd()
{
    string strPwdIn;
    cout << "请输入您的密码: ";
    while (1)
    {
        cin >> strPwdIn;
        //getchar();
        if (strPwdIn == Manager_Pwd)
        {
            break;
        }
        else
        {
            cout << endl << "密码错误，请重输: ";
        }

    }
    cout << "请问您是否要修改密码(1)" << endl;
    int ctrl;
    cin >> ctrl;
    getchar();
    if (1 != ctrl) {
        return;
    }
    string str1, str2;
    while (1)
    {
        cout << "请输入新密码： ";
        cin >> str1;
        getchar();
        cout << "请再次输入密码: ";
        cin >> str2;
        getchar();
        if (str1 != str2)
        {
            cout << "密码不匹配，请重新输入: "<<endl;
      
        }
        else
        {
            Manager_Pwd = str1;
            break;
        }
    }
}


