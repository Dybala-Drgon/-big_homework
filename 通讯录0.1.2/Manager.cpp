#include "Manager.h"
#include"User.h"
#include<iostream>
#include<string>
using namespace std;
extern User* gl_User_Head;
extern Manager man;

bool Manager::Is_Manager(IN_PARAM string strIdInput, IN_PARAM string strPwdInput)
{
    if (strIdInput == Manager_id && strPwdInput == Manager_Pwd)
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
        cout << "ͨѶ¼Ϊ��" << endl;
        system("pause");
        return;
    }

    while (key != NULL) {
        if (key->User_phone_num == str) {
            //�ҵ���ɾ����Ԫ��
            User* temp = gl_User_Head;
            while (temp->User_Next != key)
                temp = temp->User_Next;
            temp->User_Next = key->User_Next;
            delete key;
            str = str + ".txt";
            const char* savePath = str.c_str();
            if (remove(savePath) == 0)
            {
                cout << "ɾ���ɹ�" << endl;
            }
            else
            {
                cout << "ɾ��ʧ��" << endl;
            }
            system("pause");
            return;
        }
        key = key->User_Next;
    }
    cout << "���޴���" << endl;

}

void Manager::Show_User()
{
    User* key = gl_User_Head->User_Next;
    cout << "��ǰ�û��˺�" << endl;
    while (NULL != key) {
        cout << key->User_phone_num << endl;
        key = key->User_Next;
    }
    //system("pause");
}


void Manager::Menu()
{

    cout << " | ***********��ӭ����ͨѶ¼����ϵͳ*************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | ************----����Աģʽ----****************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | *********  (�����Ӧ��Ž�����Ӧģ��)  *******|" << endl;
    cout << " | 1�����鿴����            2����ɾ���û�        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 3���������û�            4����������Ϣ        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 5������ʾ�����û�                             |" << endl;
    cout << " | -----------------��0�˳�----------------------|" << endl;
}

void Manager::Display()
{
    int  key = 0, lab = 0;	//key�����˳���lab��������
    for (;;) {
        if (lab == 0) {
            system("cls");		    //����
            Menu();		//���´�ӡ�˵�
        }
        string str_choose;
        cin >> str_choose;
        getchar(); //�Ե��س�
        switch (str_choose[0])
        {
        case '1':
            cout << "��ǰ���û�������" << endl;
            cout << Get_Sum() << endl;
            system("pause");
            lab = 0;
            break;
        case '2':
        {
            Show_User();
            cout << "����ɾ����id" << endl;
            string str_del_id;
            cin >> str_del_id;
            getchar();
            Del_User(str_del_id);

            lab = 0;
            break;
        }
        case '3':
            Show_User();
            Push();
            lab = 0;
            break;
        case '4':
            SaveUser();
            cout << "����ɹ�" << endl;
            system("pause");
            lab = 0;
            break;
        case '5':
            Show_User();
            system("pause");
            lab = 0;
            break;
        case '0':
            key++;
            break;
        default:
            cout << "����������������" << endl;
            lab++;
            break;
        }
        if (key != 0)
            break;//��0�˳�
    }
}

void Manager::Push()
{
    User* FirstUser = NULL;
    User* SecondUser = NULL;
    if (Get_Sum() < 2) {
        cout << "�������������������ع���Ա����" << endl;
        system("pause");
        return;
    }

    while (1) {
        cout << "ѡ��������͵��û��� ";
        string first, second;
        cin >> first;
        getchar();
        FirstUser = Search_User_Precise(first);
        if (FirstUser == NULL) {
            cout << "����������" << endl;
            system("pause");
            return;
        }
        cout << "ѡ��������û��� ";
        cin >> second;
        getchar();
        SecondUser = Search_User_Precise(second);
        if (FirstUser != NULL && SecondUser != NULL) {
            break;   //����
        }
        cout << "�� 0 �˳������������ ����������������Ϣ" << endl;
        string judge;
        cin >> judge;
        getchar();
        const char* p = judge.data();
        if ('0' == *p)return;
    }

    UserNode* FirstNode = FirstUser->Head;
    UserNode* SecondNode = SecondUser->Head;
    int Same_Count = 0;
    if (FirstNode->next == NULL)
    {
        cout << "������" << endl;
        system("pause");
        return;
    }
    if (SecondNode->next == NULL)
    {
        cout << "������" << endl;
        system("pause");
        return;
    }
    FirstNode = FirstNode->next;

    UserNode* judge_owned = FirstNode;
    while (judge_owned != NULL) {
        if (judge_owned->str_phone_num == SecondUser->User_phone_num) //�ж��ڶ������Ƿ��ڵ�һ���˵�ͨѶ¼��
        {
            cout << "����ͨѶ¼��Ա��" << endl;
            system("pause");
            return;
        }
        judge_owned = judge_owned->next;
    }

    judge_owned = NULL;//ʹ����Ϻ�����ָ���λ��

    while (FirstNode != NULL)
    {
        SecondNode = SecondNode->next;
        while (SecondNode != NULL)
        {
            if (FirstNode->str_phone_num == SecondNode->str_phone_num)   //�����ֻ��ж���ͬ��ϵ��
            {
                Same_Count++;
                break;
            }
            SecondNode = SecondNode->next;
        }
        SecondNode = SecondUser->Head;   //��ͷ����
        FirstNode = FirstNode->next;     //����һ��
    }
    if (Same_Count >= 3)
    {
        FirstUser->Receive_Push(SecondUser->User_phone_num);
        cout << "������" << endl;
        system("pause");
        return;
    }
    cout << "������" << endl;
    system("pause");
    return;

}

User* Manager::Search_User_Precise(IN_PARAM string StrScan)
{
    //cout << "��������Ҷ���ĺ��� ";
    User* sUser = gl_User_Head;
    if (gl_User_Head->User_Next == NULL)
    {
        cout << "���޴���" << endl;
        system("pause");
        return NULL;
    }
    sUser = sUser->User_Next;
    while (sUser != NULL)
    {
        if (StrScan == sUser->User_phone_num) //��Ԫ�������Է���˽�г�Ա
        {
            return sUser;
        }
        sUser = sUser->User_Next;
    }
    cout << "���޴���" << endl;
    return NULL;
}




int Manager::Get_Sum()    //��ӡ�û�������
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
    cout << "��������������: ";
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
            cout << endl << "�������������: ";
        }

    }
    cout << "�������Ƿ�Ҫ�޸�����(1)" << endl;
    int ctrl;
    cin >> ctrl;
    getchar();
    if (1 != ctrl) {
        return;
    }
    string str1, str2;
    while (1)
    {
        cout << "�����������룺 ";
        cin >> str1;
        getchar();
        cout << "���ٴ���������: ";
        cin >> str2;
        getchar();
        if (str1 != str2)
        {
            cout << "���벻ƥ�䣬����������: " << endl;

        }
        else
        {
            Manager_Pwd = str1;
            break;
        }
    }
}


void Manager::SaveUser()//�����û���Ϣ
{
    string filename = "user.txt";
    ofstream fout;
    fout.open(filename);//�ļ���
    if (!fout.is_open())
    {
        cout << "user.txt open error";
        exit(1);
    }
    //�򿪳ɹ�
    User* temp = gl_User_Head;
    temp = temp->User_Next;
    while (temp)//���û��򱣴�
    {
        fout << temp->Get_Phone_num() << "/" << temp->Get_Pwd();
        temp = temp->User_Next;
        if (temp)//��һ���ڵ����û����б����ȡ����
        {
            fout << endl;
        }
    }
    fout << flush;
    fout.close();//�ر��ļ�
}