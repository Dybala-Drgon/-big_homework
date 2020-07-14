#pragma once
#include<iostream>
#include<string>
#ifndef USER_H
#define USER_H
#define IN_PARAM   //入口参数
#define OUT_PARAM  //出口参数
using namespace std;
const string sProvinces[34] = { "beijing", "tianjin", "shanghai", "chongqing", "hebei", "shanxi",
                  "neimenggu", "liaoning", "jilin", "heilongjiang", "jiangsu", "zhejiang",
                  "anhui", "fujian", "jiangxi", "shandong" , "henan", "hubei", "hunan", "guangdong"
                  "guangxi", "hainan", "sichuan", "guizhou", "yunnan", "xizang", "shaanxi", "gansu"
                  "qinghai", "ningxia", "xinjiang", "xianggang", "aomen", "taiwan" };

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
    void Show_detail();//打印全部数据
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
   void Showdata();
private:
    UserNode* Head ;
    string User_phone_num;
    string pwd;
};

#endif