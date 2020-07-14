#include"User.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
using namespace std;


void User::AddUser()
{
    UserNode* temp = Head;
    while (temp->next != NULL)   //�ҵ�����ĩβ
    {
        temp = temp->next;
    }
    temp ->next = new UserNode; 
    temp = temp->next;
    temp->Set_info();//��ӳ�ԱҪ¼����Ϣ
}

UserNode* User::SearchUser(IN_PARAM string first)
{
    UserNode* temp = Head;
    if (temp->next == NULL)return NULL;
    temp = temp->next;//�ӵڶ����ڵ㿪ʼ����
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

//arch���������del��revise����
void User::DeleteUserNode(IN_PARAM string first) //ɾ���û�
{
    if(NULL == (Head->next))
    {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    UserNode* temp = SearchUser(first);
    if(temp == NULL)
    {
        cout << "���޴���" <<endl;
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
    cout << " | ***********��ӭ����ͨѶ¼����ϵͳ*************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | ************----����ģʽ----******************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | *********  (�����Ӧ��Ž�����Ӧģ��)  *******|" << endl;
    cout << " | 1����¼����Ϣ            2������ʾȫ����Ϣ    |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 3��������ͨѶ¼��Ϣ      4����ɾ����Ϣ        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 5�����޸���Ϣ            5����չʾ�Ǳ�        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 6����չʾ����            7����������Ϣ        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 8������ȡ��Ϣ          ��0�˳�                |" << endl;
    cout << " | ----------------------------------------------|" << endl;
}

void User::Display()
{

    int n, key = 0, lab = 0;	//key�����˳���lab��������
    for (;;) {
        if (lab == 0) {
            system("cls");		    //����
            Main_view();		//���´�ӡ�˵�
        }
        cin >> n;
        getchar(); //�Ե��س�
        string first;
        switch (n)
        {
        case 1:
            system("cls");
            AddUser();
            lab = 0;
            break;
        case 2:	//��ʾ��Ϣ
            system("cls");
            Showdata();
            lab = 0;
            break;
        case 3:	//����
            cout << "���������Ϣ�����ֻ��ߵ绰��" << endl;
               
              cin >> first;
            SearchUser(first);
            lab = 0;
            break;
        case 4:	 //ɾ��
            cout << "����ɾ������Ϣ�����ֻ��ߵ绰��" << endl;
            
            cin >> first;
            DeleteUserNode(first);
            lab = 0;

            break;
        case 5:	//  �޸�
            cout << "�����޸ĵ���Ϣ�����ֻ��ߵ绰��" << endl;

            cin >> first;
            ReviseUser(first);
            lab = 0;
            break;
        case 6:	//  ����
            lab = 0;
            break;
        case 7:	//  ����
            lab = 0;
            break;
        case 8://��ȡ
            lab = 0;
            break;

        case 0:
            key++;
            lab = 0;
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


void User::Showdata() //��ӡ������Ϣ�����֡�id���绰��
    {
         cout << "����            id               �绰    " << endl;
        UserNode* temp = Head->next;//�ڶ����ڵ㿪ʼ����
        while (temp != NULL)
        {
            cout << left << setw(16) << temp->str_name << setw(17) << temp->str_id << setw(11) << temp->str_phone_num << endl;
            temp = temp->next;
        }
        system("pause");
          
    }


void User::ReviseUser(IN_PARAM string first) { //�޸��û�
    if (NULL == (Head->next))
    {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    UserNode* temp = SearchUser(first);
    if (temp == NULL)
    {
        cout << "���޴���" << endl;
        return;
    }

    /*�޸���Ϣ*/

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
    Set_name();
    Set_id();
    Set_academic();
    Set_major();
    Set_province();
    Set_address();
    Set_phone_num();
    Set_company();
    Set_e_mail();
}
void UserNode::Set_major()
{
    cout << "�������רҵ�� ";// input your province
    string strMajorInput = "";
    bool b_Flag = true;
    while (1)  //using a loop to ensure that the user input the message correctly
    {
        cin >> strMajorInput;
        getchar();
        for (char c : strMajorInput)
        {
            if (!isalpha(c))
            {
                b_Flag = false;
            }                 //only contains chars
        }
        if (b_Flag == true)  //input correctly
        {
            this->str_major = strMajorInput;
            return;
        }
        else               //input wrongly
        {
            b_Flag = true;
            cout << "����������רҵ";
        }
    }
}

extern const string sProvinces[34];
/*
const string sProvinces[34] = {"beijing", "tianjin", "shanghai", "chongqing", "hebei", "shanxi",
                  "neimenggu", "liaoning", "jilin", "heilongjiang", "jiangsu", "zhejiang",
                  "anhui", "fujian", "jiangxi", "shandong" , "henan", "hubei", "hunan", "guangdong"
                  "guangxi", "hainan", "sichuan", "guizhou", "yunnan", "xizang", "shaanxi", "gansu"
                  "qinghai", "ningxia", "xinjiang", "xianggang", "aomen", "taiwan"};*/
                  //���������ͷ�ļ�
void UserNode::Set_province()
{
    cout << "�������ʡ�ݣ� ";// input your province
    string strInput;
    bool b_Flag = false;
    while (1)                  //using a loop to ensure that the user input the message correctly
    {
        cin >> strInput;
        getchar();
        for (char& c : strInput)
        {
            c = tolower(c);                            //transfer to lowercase
        }
        for (int i = 0; i < 34; i++)
        {
            if (strInput == sProvinces[i])        //compare with a string array of province
            {
                b_Flag = true;
                break;
            }
        }
        if (b_Flag == true)  //input correctly
        {
            this->str_province = strInput;
            return;
        }
        else               //input wrongly
        {
            b_Flag = false;
            cout << "����������ʡ�ݣ�";
        }
    }

}

void UserNode::Set_address()
{
    cout << "������ĵ�ַ�� ";// input your address
    string strInput;
    bool b_Flag = true;
    while (1)                 //using a loop to ensure that the user input the message correctly
    {
        cin >> strInput;
        getchar();
        for (char c : strInput)
        {
            if (!(isdigit(c) || isalpha(c)))
            {
                b_Flag = false;
            }                     //only contains chars
        }
        if (b_Flag == true)        //input correctly
        {
            this->str_address = strInput;
            return;
        }
        else                     //input wrongly
        {
            b_Flag = false;
            cout << "�����������ַ�� ";
        }
    }
}
void UserNode::Set_name() {
    cout << "������name��"; //input your English name 
    string sinput;
    bool b_ch = true;
    while (1) {        //to make sure the information is right
        cin >> sinput;
        getchar();
        for (char c : sinput)
        {
            if (c < 'A' || (c > 'Z' && c < 'a') || c>'z') 	//only English letters can be entered
            {
                b_ch = false;
                break;
            }

        }
        if (b_ch == true)       //input correctly
        {
            this->str_name = sinput;
            return;
        }
        else              //input error
        {
            b_ch = true;
            cout << "����������name��";
        }
    }
}

void UserNode::Set_id() {
    cout << "������id(6λ)��";
    string sinput;

    bool b_ch = true;
    while (1) {          //to make sure the information is right
        cin >> sinput;
        getchar();
        for (char c : sinput)
        {
            if (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c>'z') 		//only English letters and numbers can be entered
            {
                b_ch = false;
                break;
            }

        }
        if (b_ch == true)               //input correctly
        {
            this->str_id = sinput;
            return;
        }
        else                //input error
        {
            b_ch = true;
            cout << "����������id��";
        }
    }
}

void UserNode::Set_phone_num()
{
    cout << "������绰���룺";
   
    string strInput;
    int i_num = 0;
    bool b_flag = true;
    while (1) {
        cin >> strInput;
        getchar();
        for (char c : strInput)
        {
            if (c < '0' || c>'9')
            {
                b_flag = false;
            }
            i_num++;
        }
        if ( i_num != 11)
        {
            b_flag = false;
        }
    if (b_flag == true)
    {
        this->str_phone_num = strInput;
        return;
    }
    else
    {
        b_flag = true;
        i_num = 0;
        cout << "��������"<<endl;
    }
  }
}


void UserNode::Set_academic()
{
    cout << "������academic��";
    string sinput;
    bool b_ch = true;
    while (1)
    {
        cin >> sinput;
        getchar();
        for (char& c : sinput)
        {
            if (c <= '9' && c >= '0')
            {
                b_ch = false;
                break;
            }
        }
        if (b_ch == true)
        {
            this->str_academic = sinput;
            return;
        }
        else
        {
            b_ch = true;
            cout << "����������academic��";
        }
    }
}

void UserNode::Set_e_mail()
{
    cout << "������e-mail��";
    string sinput;
    bool b_ch = false;
    while (1)
    {
        cin >> sinput;
        getchar();
        for (char& c : sinput)
        {
            if (c == '@')  //��@�����ʼ�
            {
                b_ch = true;
                break;
            }
        }
        if (b_ch == true)
        {
            this->str_e_mail = sinput;
            return;
        }
        else
        {
            b_ch = false;
            cout << "����������e-mail��";
        }
    }
}

void UserNode::Set_company()
{
    cout << "�����빫˾";
    string strInput;
    bool b_flag = true;
    while (1)
    {
        cin >> strInput;
        getchar();
        for (char c : strInput)
        {
            if (!(isdigit(c) || isalpha(c)))
            {
                b_flag = false;
            }
        }
        if (b_flag == true)
        {
            this->str_company = strInput;
            return;
        }
        else
        {
            b_flag = true;
        }
    }
}