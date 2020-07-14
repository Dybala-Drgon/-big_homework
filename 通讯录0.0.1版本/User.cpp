#include"User.h"
#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;


void User::AddUser()
{
    UserNode* temp = Head;
    while (temp->next != NULL)   //找到链表末尾
    {
        temp = temp->next;
    }
    temp ->next = new UserNode; 
    temp = temp->next;
    temp->Set_info();//添加成员要录入信息
}

UserNode* User::SearchUser(IN_PARAM string first)
{
    UserNode* temp = Head;
    if (temp->next == NULL)return NULL;
    temp = temp->next;//从第二个节点开始遍历
    while(temp != NULL)
    {
        if(first == temp->str_name)
        {
            return temp;
        }
        if (first == temp->str_phone_num)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//arch里面组合了del和revise函数
void User::DeleteUserNode(IN_PARAM string first) //删除用户
{
    if(NULL == (Head->next))
    {
        cout << "通讯录为空" << endl;
        return;
    }
    UserNode* temp = SearchUser(first);
    if(temp == NULL)
    {
        cout << "查无此人" <<endl;
        return;
    }
             UserNode* ptr = Head;
            while(ptr->next != temp)
            {
                ptr = ptr->next;
            }
            ptr->next = temp->next;
            delete temp;
}

void User::Main_view()
{
    cout << " | ***********欢迎进入通讯录管理系统*************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | ************----个人模式----******************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | *********  (键入对应编号进入相应模块)  *******|" << endl;
    cout << " | 1——录入信息            2——显示全部信息    |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 3——查找通讯录信息      4——删除信息        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 5——修改信息            5——展示星标        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 6——展示分组            7——保存信息        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 8——读取信息          按0退出                |" << endl;
    cout << " | ----------------------------------------------|" << endl;
}

void User::Display()
{

    int n, key = 0, lab = 0;	//key控制退出，lab控制清屏
    for (;;) {
        if (lab == 0) {
            system("cls");		    //清屏
            Main_view();		//重新打印菜单
        }
        cin >> n;
        getchar(); //吃掉回车
        string first;
        switch (n)
        {
        case 1:
            AddUser();
            lab = 0;
            break;
        case 2:	//显示信息
            //Show();
            lab = 0;
            break;
        case 3:	//查找
            cout << "输入查找信息（名字或者电话）" << endl;
               
              cin >> first;
            SearchUser(first);
            lab = 0;
            break;
        case 4:	 //删除
            cout << "输入删除的信息（名字或者电话）" << endl;
            
            cin >> first;
            DeleteUserNode(first);
            lab = 0;

            break;
        case 5:	//  修改
            cout << "输入修改的信息（名字或者电话）" << endl;

            cin >> first;
            ReviseUser(first);
            lab = 0;
            break;
        case 6:	//  分组
            lab = 0;
            break;
        case 7:	//  保存
            lab = 0;
            break;
        case 8://读取
            lab = 0;
            break;

        case 0:
            key++;
            lab = 0;
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

void User::ReviseUser(IN_PARAM string first) { //修改用户
    if (NULL == (Head->next))
    {
        cout << "通讯录为空" << endl;
        return;
    }
    UserNode* temp = SearchUser(first);
    if (temp == NULL)
    {
        cout << "查无此人" << endl;
        return;
    }

    /*修改信息*/

}

UserNode::UserNode()
{
    next = NULL;
    b_is_classmate = false;
    b_is_colleague = false;
    b_is_important = false;
    b_is_relative = false;
    b_is_printed = false;

}

void UserNode::Set_info()
{
}
