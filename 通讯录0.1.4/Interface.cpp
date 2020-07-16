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
    cout << " |           ************************欢迎进入通讯录管理系统*********************                  |" << endl;
    cout << " |          ----------------------------------------------------------------------                |" << endl;
    cout << " |          ****************************----选择模式----*************************                 |" << endl;
    cout << " |     ------------------------------------------------------------------------------             |" << endl;
    cout << " |     |       ***************      (键入对应编号进入相应模块)  *************       |             |" << endl;
    cout << " |     |         1——普通用户                                 2——管理员          |             |" << endl;
    cout << " |     |      --------------------------------------------------------------        |             |" << endl;
    cout << " |     |         3——注册                                                          |             |" << endl;
    cout << " |     |      ---------------------------按0退出----------------------------        |             |" << endl;
}

void Interface::Display()
{
    int key_ex = 0, lab = 0;	//key控制退出，lab控制清屏
    for (;;) {
        if (lab == 0) {
            system("cls");		    //清屏
            Menu();		//重新打印菜单
        }
        string str_choose;
        cin >> str_choose;
        getchar(); //吃掉回车
        User* key = NULL;//定位指针，用于查找用户
        if (str_choose.length() > 1)
        {
            cout << "输入有误" << endl;
            system("pause");
            continue;
        }
        switch (str_choose[0])
        {
        case '1':
            key = Log_In_User();
            if (key != NULL)
                key->Display();
            lab = 0;
            break;
        case '2':
            if (Log_In_Manager())
                man.Display();
            lab = 0;
            break;
        case '3':
            Register_User();
            lab = 0;
            break;
        case '0':
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
    cout << "输入你的手机号: " << endl;
    while (1)
    {
        cin >> str_Id_Regist;
        getchar();
        if (str_Id_Regist.length() != 11) {
            cout << "您输入的不是11位手机号码,重试" << endl;
            continue;
        }
        for (char c : str_Id_Regist)
        {
            if (!isdigit(c))      //不都是数字or字母
            {
                cout << "账号只能包含数字字符，请重新输入: ";
                b_Flag = false;
                break;
            }
        }


        if (Search_User_ID(str_Id_Regist) != NULL)
        {
            cout << "该账号已经存在，请重新输入: ";
            continue;
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
    while (Iter != NULL)
    {
        if (Iter->Get_Phone_num() == first)    //find
        {
            return Iter;
        }
        Iter = Iter->User_Next;
    }
    return NULL;
}

Interface::Interface()//构造函数 程序开始时读取信息
{
    User* temp = gl_User_Head;
    char buf_phone[15];//缓冲区，通过这个变量将文件中读取的账号存入用户信息
    char buf_key[50];//缓冲区，通过这个变量将文件中读取的密码存入用户信息
    ifstream fin("user.txt");

    if (!fin.is_open())
    {
        cout << """user.txt"" doesn't exit,please add user.";
        system("Pause");
    }

    //打开成功
    else
    {

        fin.seekg(0, ios::end);
        int length = fin.tellg();
        if (length == 0) {
            cout << "there is no user,please add user";
            system("Pause");
        }
        else //文件不为空
        {
            fin.seekg(0, ios::beg);//指针移向文件头

            while (!fin.eof())//没到文件末尾则读取信息
            {

                temp->User_Next = new User;
                temp = temp->User_Next;
                fin.getline(buf_phone, 15, '/');
                temp->Set_Phone_Num(buf_phone);
                fin.getline(buf_key, 50);
                temp->Set_Pwd(buf_key);
            }

            fin.close();

            Read();//读取用户的联系人信息

        }
    }
}

Interface::~Interface()//析构函数 程序结束时自动保存信息
{
    Save();//保存用户的联系人信息
    string filename = "user.txt";
    ofstream fout;
    fout.open(filename);//文件名
    if (!fout.is_open())
    {
        cout << "user.txt open error";
        exit(1);
    }
    //打开成功
    User* temp = gl_User_Head;
    temp = temp->User_Next;
    while (temp)//有用户则保存
    {
        fout << temp->Get_Phone_num() << "/" << temp->Get_Pwd();
        temp = temp->User_Next;
        if (temp)//下一个节点有用户则换行避免读取出错
        {
            fout << endl;
        }
    }
    fout << flush;
    fout.close();//关闭文件
}