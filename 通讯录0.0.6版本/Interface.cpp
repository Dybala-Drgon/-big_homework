#include "Interface.h"
#include"Manager.h"
#include"User.h"
#include<string>
using namespace std;
User* gl_User_Head = new User;//ά��һ���������û�����
Manager man;
 //extern Manager man;
//extern User* User_Head
void Interface::Menu()
{
    cout << " | ***********��ӭ����ͨѶ¼����ϵͳ*************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | ************----ѡ���¼ģʽ----**************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | *********  (�����Ӧ��Ž�����Ӧģ��)  *******|" << endl;
    cout << " | 1������ͨ�û�            2��������Ա          |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 3����ע��                                     |" << endl;
    cout << " | -----------------��0�˳�----------------------|" << endl;
}

void Interface::Display()
{
    int n, key_ex = 0, lab = 0;	//key�����˳���lab��������
    for (;;) {
        if (lab == 0) {
            system("cls");		    //����
            Menu();		//���´�ӡ�˵�
        }
        cin >> n;
        getchar(); //�Ե��س�
        User* key = NULL;//��λָ�룬���ڲ����û�
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
            cout << "����������������" << endl;
            lab++;
            break;
        }
        if (key_ex != 0)
            break;//��0�˳�
    }
}

User* Interface::Log_In_User()
{
    system("cls");
    string str1;//��֤�˺�
    string str2;//��֤����
    cout << "�����˺�:";
    cin >> str1;
    getchar();
    cout << "��������:";
    cin >> str2;
    getchar();
    User* temp = gl_User_Head;
    while (temp != NULL)
    {
        if (temp->Is_User(str1, str2))
        {
            cout << "��¼�ɹ�" << endl;
            system("pause");
            return temp;
        }
        temp = temp->User_Next;
    }

    cout << "��¼ʧ��,�����������˵�" << endl;
    system("pause");
    return NULL;
}

bool Interface::Log_In_Manager()
{
    system("cls");
    string str1;//��֤�˺�
    string str2;//��֤����
    cout << "�����˺�:";
    cin >> str1;
    cout << "��������:";
    cin >> str2;
    if (man.Is_Manager(str1, str2))
    {
        cout << "��¼�ɹ�" << endl;
        system("pause");
        return true;
    }
    cout << "��¼ʧ��,�����������˵�" << endl;
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
    cout << "��������˺�: " << endl;
    while (1)
    {
        cin >> str_Id_Regist;
        //getchar();
        for (char c : str_Id_Regist)
        {
            if (!isalnum(c))      //����������or��ĸ
            {
                cout << "�˺�ֻ�ܰ�����ĸ�������ַ�������������: ";
                b_Flag = false;
                break;
            }
        }
        if (Search_User_ID(str_Id_Regist) != NULL)
        {
            cout << "���˺��Ѿ����ڣ�����������: ";
            break;
        }
        if (b_Flag)
        {
            cout << "����ɹ�������������������:";
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
    cout << "���ٴ�ȷ�����룺��������3�λ��ᣩ" << endl;
    while (1)
    {
        cin >> str_Pwd_Again;
        if (str_Pwd_Again != str_Pwd_Regist)
        {
            cnt--;
            cout << "�ٴ���������벻ƥ�䣬���ٴ����룺�������� "
                << cnt << " �λ��ᣩ" << endl;
        }
        if (0 == cnt)
        {
            cout << "ע��ʧ��" << endl;
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
            Iter = Iter->User_Next;       //�����µ�user
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
