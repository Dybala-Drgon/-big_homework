#include<iostream>
#include<string>
#ifndef USER_H
#define USER_H
#define IN_PARAM   //入口参数
#define OUT_PARAM  //出口参数
using namespace std;


class UserNode
{
public:
    UserNode();
    string str_name;
    string str_id;          //学号
    string str_academic;    //院系
    string str_major;       //专业
    string str_province;    //籍贯
    string str_address;     //地址
    string str_phone_num;   //电话号码
    string str_company;     //工作单位
    string str_e_mail;      //邮件
    bool   b_is_printed;    //判断是否打印，true是打印过
    bool   b_is_classmate;
    bool   b_is_colleague;
    bool   b_is_relative;
    bool   b_is_important;  //是否星标联系人
    bool   b_in_blacklist;
    string str_latly_call;  //最近通话信息
    UserNode* next;

    void Set_info();
    void Set_name();//输入名字
    void Set_id();//输入学号
    void Set_academic();//输入院系
    void Set_major();//输入专业
    void Set_province();//输入籍贯
    void Set_address();//输入地址
    void Set_phone_num();//输入电话号码
    void Set_company();//输入工作单位
    void Set_e_mail();//输入电子邮件
    void Set_Group();
    void Show_detail();//打印全部数据

    void Set_Black_List();//设置黑名单
    void Set_Black_List_Out();//移除黑名单
};


class User {
public:
    ~User() {}
    User() {
        Head = new UserNode;
    }

    void AddUser();
    UserNode* SearchUser(IN_PARAM string first);
    //查找函数
    void DeleteUserNode(IN_PARAM string first);
     //删除函数
    void ReviseUser(IN_PARAM string first);
    //修改用户


    void Main_view();
    void Display();
    void Choose_Show(int first);//选择查看类别
     void Showdata();    //全部打印
     void Show_star();  //打印星标联系人
     void Show_relative();  //家人
     void Show_classmate();//同学
     void Show_colleague();//同事
     void Show_blacklist();//黑名单

     void Change_Pwd();
private:
    UserNode* Head ;
    string User_phone_num;
    string str_pwd;
};

#endif