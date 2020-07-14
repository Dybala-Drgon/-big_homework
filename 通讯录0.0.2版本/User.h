#pragma once
#include<iostream>
#include<string>
#ifndef USER_H
#define USER_H
#define IN_PARAM   //��ڲ���
#define OUT_PARAM  //���ڲ���
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
    string str_id;          //ѧ��
    string str_academic;    //Ժϵ
    string str_major;       //רҵ
    string str_province;    //����
    string str_address;     //��ַ
    string str_phone_num;   //�绰����
    string str_company;     //������λ
    string str_e_mail;      //�ʼ�
    bool   b_is_printed;    //�ж��Ƿ��ӡ��true�Ǵ�ӡ��
    bool   b_is_classmate;
    bool   b_is_colleague;
    bool   b_is_relative;
    bool   b_is_important;  //�Ƿ��Ǳ���ϵ��
    string str_latly_call;  //���ͨ����Ϣ
    UserNode* next;

    void Set_info();
    void Set_name();//��������
    void Set_id();//����ѧ��
    void Set_academic();//����Ժϵ
    void Set_major();//����רҵ
    void Set_province();//���뼮��
    void Set_address();//�����ַ
    void Set_phone_num();//����绰����
    void Set_company();//���빤����λ
    void Set_e_mail();//��������ʼ�
    void Show_detail();//��ӡȫ������
};


class User {
public:
    ~User() {}
    User() {
        Head = new UserNode;
    }

    void AddUser();
    UserNode* SearchUser(IN_PARAM string first);
    //���Һ���
    void DeleteUserNode(IN_PARAM string first);
     //ɾ������
    void ReviseUser(IN_PARAM string first);
    //�޸��û�


    void Main_view();
    void Display();
   void Showdata();
private:
    UserNode* Head ;
    string User_phone_num;
    string pwd;
};

#endif