#include "Interface.h"
#include"Manager.h"
#include"User.h"
#include<string>
using namespace std;
User* gl_User_Head = new User;//维护一个公共的用户链表
Manager man;
 //extern Manager man;
//extern User* User_Head
void Interface::Menu()
{
    cout << " | ***********欢迎进入通讯录管理系统*************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | ************----选择登录模式----**************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | *********  (键入对应编号进入相应模块)  *******|" << endl;
    cout << " | 1——普通用户            2——管理员          |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 3——注册                                     |" << endl;
    cout << " | -----------------按0退出----------------------|" << endl;
}

void Interface::Display()
{
    int n, key_ex = 0, lab = 0;	//key控制退出，lab控制清屏
    for (;;) {
        if (lab == 0) {
            system("cls");		    //清屏
            Menu();		//重新打印菜单
        }
        cin >> n;
        getchar(); //吃掉回车
        User* key = NULL;//定位指针，用于查找用户
        switch (n)
        {
        case 1:
            key=Log_In_User();
            if (key != NULL)
                key->Display();
            lab = 0;
            break;
        case 2:
            if (Log_In_Manager())
                man.Display();
            lab = 0;
            break;
        case 3:
            Register_User();
            lab = 0;
            break;
        case 0:
            lab = 0;
            key_ex++;
            break;
        default:
            cout << "输入有误，重新输入" << endl;
            lab++;
            break;
        }
        if (key_ex != 0)
            break;//按0退出
    }
}

User* Interface::Log_In_User()
{
    system("cls");
    string str1;//保证账号
    string str2;//保证密码
    cout << "输入账号:";
    cin >> str1;
    getchar();
    cout << "输入密码:";
    cin >> str2;
    getchar();
    User* temp = gl_User_Head;
    while (temp != NULL)
    {
        if (temp->Is_User(str1, str2))
        {
            cout << "登录成功" << endl;
            system("pause");
            return temp;
        }
        temp = temp->User_Next;
    }

    cout << "登录失败,即将返回主菜单" << endl;
    system("pause");
    return NULL;
}

bool Interface::Log_In_Manager()
{
    system("cls");
    string str1;//保证账号
    string str2;//保证密码
    cout << "输入账号:";
    cin >> str1;
    cout << "输入密码:";
    cin >> str2;
    if (man.Is_Manager(str1, str2))
    {
        cout << "登录成功" << endl;
        system("pause");
        return true;
    }
    cout << "登录失败,即将返回主菜单" << endl;
    system("pause");
    return false;
}

bool Interface::Register_User()
{
    system("cls");
    string str_Id_Regist;     //account number
    string str_Pwd_Regist;    //you password
    string str_Pwd_Again;     //input passwd again
    bool b_Flag = true;
    cout << "输入你的账号: " << endl;
    while (1)
    {
        cin >> str_Id_Regist;
        //getchar();
        for (char c : str_Id_Regist)
        {
            if (!isalnum(c))      //不都是数字or字母
            {
                cout << "账号只能包含字母和数字字符，请重新输入: ";
                b_Flag = false;
                break;
            }
        }
        if (Search_User_ID(str_Id_Regist) != NULL)
        {
            cout << "该账号已经存在，请重新输入: ";
            break;
        }
        if (b_Flag)
        {
            cout << "输入成功，接下来请输入密码:";
            break;
        }
        else
        {
            b_Flag = true;
            continue;
        }
    }
    int cnt = 3;
    cin >> str_Pwd_Regist;
    cout << "请再次确认密码：（您共有3次机会）" << endl;
    while (1)
    {
        cin >> str_Pwd_Again;
        if (str_Pwd_Again != str_Pwd_Regist)
        {
            cnt--;
            cout << "再次输入的密码不匹配，请再次输入：（您还有 "
                << cnt << " 次机会）" << endl;
        }
        if (0 == cnt)
        {
            cout << "注册失败" << endl;
            system("pause");
            system("cls");
            return false;
        }
        if (str_Pwd_Again == str_Pwd_Regist)
        {
            User* Iter = gl_User_Head;
            while (Iter->User_Next != NULL)
            {
                Iter = Iter->User_Next;
            }
            Iter->User_Next = new User;
            Iter = Iter->User_Next;       //进入新的user
            Iter->Set_Phone_Num(str_Id_Regist);
            Iter->Set_Pwd(str_Pwd_Regist);
            return true;
        }
    }

    return false;

}

User* Interface::Search_User_ID(IN_PARAM string first)
{
   User* Iter = gl_User_Head;
    while(Iter->User_Next != NULL)
    {
        if(Iter->Get_Phone_num() == first)    //find
        {
            return Iter; 
        }
        Iter = Iter->User_Next;
    }
    return NULL;
}
