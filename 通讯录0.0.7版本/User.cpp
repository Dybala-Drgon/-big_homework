#include"User.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
using namespace std;
extern User* gl_User_Head;
extern Manager man;

User::~User()               //��ֹ�ڴ�й©
{
    while (Head->next!=NULL) {
        UserNode* key = Head;
        while (key->next != NULL) {
            key = key->next;
        }
        UserNode* before = Head;
        while (before-> next!= key&&before->next!=NULL)
        {
            before = before->next;
        }
        before->next = NULL;
        delete key;
   }
//    cout << "�ͷ�user�Ŀռ�" << endl;
}

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

UserNode* User::SearchUser_node(IN_PARAM string first)
{
    UserNode* temp = Head;
    if (temp->next == NULL) {
    cout << "���޴���" << endl;
    system("pause");
    return NULL; 
    }
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
   cout << "���޴���" << endl;
   //---------------------������ģ������----------------------------------------
   cout << "***************************************************" << endl;
   cout << "����������..." << endl;
   cout << "����            id               �绰    " << endl;
   temp = Head->next;//�ڶ����ڵ㿪ʼ����
   while (temp != NULL)
   {
       string::size_type idx;
       string::size_type idx2;
       idx = temp->str_name.find(first);
       idx2 = temp->str_phone_num.find(first);
       if (idx != string::npos||idx2!=string::npos)//�����Ӵ���
       {
           if (false == temp->b_in_blacklist)
               cout << left << setw(16) << temp->str_name << setw(17) <<
               temp->str_id << setw(11) << temp->str_phone_num << endl;
       }
           temp = temp->next;
   }
    system("pause");
    return NULL;
}


void User::DeleteUserNode(IN_PARAM string first) //ɾ��ͨѶ¼�ڵ�
{
    if(NULL == (Head->next))
    {
        cout << "ͨѶ¼Ϊ��" << endl;
        system("pause");
        return;
    }
    UserNode* temp = SearchUser_node(first);
    if(temp == NULL)
    {
        return;
    }
             UserNode* ptr = Head;
            while(ptr->next != temp)
            {
                ptr = ptr->next;
            }
            ptr->next = temp->next;
            delete temp;
            cout << "ɾ���ɹ�" << endl;
            system("pause");
}

void User::Main_view()
{
    cout << " | ***********��ӭ����ͨѶ¼����ϵͳ*************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | ************----����ģʽ----******************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | *********  (�����Ӧ��Ž�����Ӧģ��)  *******|" << endl;
    cout << " | 1����¼����Ϣ            2������ʾ��Ϣ        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 3��������ͨѶ¼��Ϣ      4����ɾ����Ϣ        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 5�����޸���Ϣ            6����������Ϣ        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 7������ȡ��Ϣ           8/9��������/������    |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 10�����޸�����           11����������Ϣ       |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 12�����鿴�����ϵ��     13�������������أ�   |" << endl;
    cout << " | -----------------��0�˳�----------------------|" << endl;
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
            cout << "1.ȫ��չʾ   2.չʾ�Ǳ���ϵ��   3.չʾͬѧ   4.չʾ����    5.չʾͬ��   6.������" << endl;
            int n;
            cin >> n;
            getchar();
            Choose_Show(n);
            lab = 0;
            break;
        case 3:	//���� 
        {
            cout << "���������Ϣ�����ֻ��ߵ绰��" << endl;

            cin >> first;
            UserNode* T = SearchUser_node(first);
            if(NULL!=T)
            T->Show_detail();
            lab = 0;
            break;
        }
        case 4:	 //ɾ��
            cout << "����ɾ������Ϣ�����ֻ��ߵ绰��" << endl;

            cin >> first;
            getchar();
            DeleteUserNode(first);
            lab = 0;

            break;
        case 5:	//  �޸�
            cout << "�����޸ĵ���Ϣ�����ֻ��ߵ绰��" << endl;

            cin >> first;
            getchar();
            ReviseUser(first);
            lab = 0;
            break;
        case 6:	//  ����
            lab = 0;
            break;
        case 7:	//  ��ȡ
            lab = 0;
            break;
        case 8://����
        {
            cout << "�����޸ĵ���Ϣ�����ֻ��ߵ绰��" << endl;
            cin >> first;
            getchar();
            UserNode* T = SearchUser_node(first);
            if (NULL != T)
                T->Set_Black_List();
            
            lab = 0;
            break;
        }
        case 9://������
        {
            cout << "�����޸ĵ���Ϣ�����ֻ��ߵ绰��" << endl;
            cin >> first;
            getchar();
            UserNode* T = SearchUser_node(first);
            if (NULL != T)
                T->Set_Black_List_Out();
            
            lab = 0;
            break;
        }
        case 10:
            cout << "�޸�����:" << endl;
            Change_Pwd();
            lab = 0;
            break;
        case 13:
            cout << "����" << endl;
            if(Del_Myself())//��������ɹ���ֱ���˳����棬��Ч������0
            key++;
            lab = 0;
            break;
        case 11://����Ϣ
            Send_Message();
            lab = 0;
            break;
        case 12:
            Show_last_call();
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

void User::Choose_Show(int first)
{
    switch (first)
    {
    case 1:         //ȫ��
        Showdata();
        break;
    case 2:         //�Ǳ�
        Show_star();
        break;
    case 3:         //ͬѧ
        Show_classmate();
        break;
    case 4:         //����
        Show_relative();
        break;
    case 5:         //ͬ��
        Show_colleague();
        break;
    case 6:
        Show_blacklist();
        break;
    default:
        cout << "��������,������������˵�" << endl;
        system("pause");
        break;
    }
}


void User::Showdata() //��ӡ������Ϣ�����֡�id���绰��
    {
         cout << "����            id               �绰    " << endl;
        UserNode* temp = Head->next;//�ڶ����ڵ㿪ʼ����
        while (temp != NULL)
        {
            if(false==temp->b_in_blacklist)
            cout << left << setw(16) << temp->str_name << setw(17) <<
             temp->str_id << setw(11) << temp->str_phone_num << endl;
            temp = temp->next;
        }
        system("pause");
          
    }

void User::Show_star()
{
    cout << "����            id               �绰    " << endl;
    UserNode* temp = Head->next;//�ڶ����ڵ㿪ʼ����
    while (temp != NULL)
    {
        if(true==temp->b_is_important&& false == temp->b_in_blacklist) //���Ǳ�ʹ�ӡ
        cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");

}


void User::Show_relative()
{
    cout << "����            id               �绰    " << endl;
    UserNode* temp = Head->next;//�ڶ����ڵ㿪ʼ����
    while (temp != NULL)
    {
        if (true == temp->b_is_relative&& false == temp->b_in_blacklist) //�Ǽ��˾ʹ�ӡ
            cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");
}

void User::Show_classmate()
{
    cout << "����            id               �绰    " << endl;
    UserNode* temp = Head->next;//�ڶ����ڵ㿪ʼ����
    while (temp != NULL)
    {
        if (true == temp->b_is_classmate&& false == temp->b_in_blacklist) //��ͬѧ�ʹ�ӡ
            cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");
}

void User::Show_colleague()
{
    cout << "����            id               �绰    " << endl;
    UserNode* temp = Head->next;//�ڶ����ڵ㿪ʼ����
    while (temp != NULL)
    {
        if (true == temp->b_is_colleague&& false == temp->b_in_blacklist) //��ͬ�¾ʹ�ӡ
            cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");
}

void User::Show_blacklist()
{
    cout << "����            id               �绰    " << endl;
    UserNode* temp = Head->next;//�ڶ����ڵ㿪ʼ����
    while (temp != NULL)
    {
        if (true == temp->b_in_blacklist) //�Ǻ������ʹ�ӡ
            cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");
}

void User::Change_Pwd()
{
    string str1;
    string str2;
    while (1) {
        cin >> str1;
        cout << "��ȷ������" << endl;
        cin >> str2;
        if (str1 == str2) {
            cout << "�޸ĳɹ�" << endl;
            str_pwd = str1;
            break;
        }
        else {
            cout << "�������벻һ��,��������" << endl;
        }
    }
    system("pause");
}

bool User::Is_User(IN_PARAM string strIdInput, IN_PARAM string strPwdInput)
{
    if (strIdInput == User_phone_num && strPwdInput == str_pwd)
        return true;
    return false;
}


void User::ReviseUser(IN_PARAM string first) { //�޸��û�
    if (NULL == (Head->next))
    {
        cout << "ͨѶ¼Ϊ��" << endl;
        system("pause");
        return;
    }
    UserNode* temp = SearchUser_node(first);
    if (temp == NULL)
    {
        return;
    }
    system("cls");
    temp->Show_detail();
    cout << "�������֣�������ϣ�ѡ���޸ĵ�Ŀ�꣨��������0�˳���" << endl;
    string strInput;
    bool b_Flag = true;
    cout << "1:name  2:id  3:academic  4:major  5:province  6:address" << endl;
    cout << "7:phone num:  8:company   9:e-mail x:Group     0:quit" << endl;

    while (1)
    {
        cin >> strInput;
        getchar();
        const char* p = strInput.data();
        if ('0' == *p)return;
        for (char c : strInput)
        {
            if (!(c <= '9' && c >= '1')&&c!='x')  //��ֹ�û�������
            {
                b_Flag = false;
            }
        }
        if (b_Flag == true)              //��ȷ����
        {
            for (char c : strInput)
            {
                switch (c)
                {
                case '1': 
                    temp->Set_name();
                    break;
                case '2': 
                    temp->Set_id();
                    break;
                case '3': 
                    temp->Set_academic();
                    break;
                case '4': 
                    temp->Set_major();
                    break;
                case '6':
                    temp->Set_address();
                    break;
                case '7':
                    temp->Set_phone_num();
                    break;
                case '8':
                    temp->Set_company();
                    break;
                case '9':
                    temp->Set_e_mail();
                case 'x':
                    temp->Set_Group();
                }
            }
            cout << "�޸ĳɹ�" << endl;
            system("pause");
            return;
        }
        else                        //����
        {
            b_Flag = true;
            cout << "��������" << endl;
        }
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
    b_in_blacklist = false;
    b_is_last_call = false;
}

void UserNode::Set_info()
{
    Set_name();
    Set_phone_num();
    Set_id();
    Set_academic();
    Set_major();
    Set_province();
    Set_address();
    Set_company();
    Set_e_mail();
    Set_Group();
}


void UserNode::Set_Group()
{
    int intRelationShip = 0;
    b_is_important = false;
    b_is_colleague = false;
    b_is_relative = false;
    b_is_classmate = false;
    cout << "������һ������1234��������ȷ������ " << endl
        << "����������1���Ǳ���ϵ�ˣ�  "
        << "��2:ͬѧ   " << "��3:����  "
        << "��4:ͬ��      ��������0:����"  << endl;
    string strInput;
    bool b_Flag = true;
    while (1)
    {
        cin >> strInput;
        getchar();
       const char* p = strInput.data();
       if ('0' == *p)return;
        for (char c : strInput)
        {
            if (!(c <= '4' && c >= '1'))  //��ֹ�û�������
            {
                b_Flag = false;
            }
        }
        if (b_Flag == true)              //��ȷ����
        {
            for (char c : strInput)
            {
                switch (c)
                {
                case '1': b_is_important = true;
                    break;
                case '2': b_is_classmate = true;
                    break;
                case '3': b_is_relative = true;
                    break;
                case '4': b_is_colleague = true;
                    break;
                }
            }

            cout << "�����ɹ�" << endl;
            system("pause");
            return;
        }
        else                        //����
        {
            b_Flag = true;
            cout << "��������" << endl;
        }
    }
}

void UserNode::Set_major()
{
    cout << "����ó�Ա��רҵ�� ";// input your province
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

const string sProvinces[34] = {"beijing", "tianjin", "shanghai", "chongqing", "hebei", "shanxi",
                  "neimenggu", "liaoning", "jilin", "heilongjiang", "jiangsu", "zhejiang",
                  "anhui", "fujian", "jiangxi", "shandong" , "henan", "hubei", "hunan", "guangdong"
                  "guangxi", "hainan", "sichuan", "guizhou", "yunnan", "xizang", "shaanxi", "gansu"
                  "qinghai", "ningxia", "xinjiang", "xianggang", "aomen", "taiwan"};
                 
void UserNode::Set_province()
{
    cout << "����ó�Աʡ�ݣ� ";// input your province
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
    cout << "����ó�Ա���ֵ�ַ�� ";// input your address
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
            cout << "��������" << endl;
        }
    }
}
void UserNode::Show_detail()
{
    system("cls");
    cout << "name                id          phone_num                   e_mail" << endl;
    cout << left << setw(20) << str_name << setw(12) << str_id << setw(28) << str_phone_num << str_e_mail << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "major                           academic                    province" << endl;
    cout << left << setw(32) << str_major << setw(28) << str_academic << str_province << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "company                         adress" << endl;
    cout << left << setw(32) << str_company << str_address << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    system("pause");

}


void UserNode::Set_Black_List()
{
    if (b_in_blacklist == true)
    {
        cout << "�������ں�������" << endl;
        system("pause");
        return;
    }
    cout << "�Ƿ񽫸ö�������������?" << endl
        << "��y����" << endl;
    char chr[100];
    cin >> chr;
    getchar();
    if (chr[0] == 'y' || chr[0] == 'Y')
    {
        b_in_blacklist = true;
        cout << "�����ɹ�" << endl;
        system("pause");
        return;
    }
}

void UserNode::Set_Black_List_Out()
{
    if (b_in_blacklist == false)
    {
        cout << "����δ������" << endl;
        system("pause");
        return;
    }
    cout << "�Ƿ񽫸ö����Ƴ�������?" << endl
        << "��y�Ƴ�" << endl;
    char chr[100];
    cin >> chr;
    getchar();
    if (chr[0] == 'y' || chr[0] == 'Y')
    {
        b_in_blacklist = false;
        cout << "�����ɹ�" << endl;
        system("pause");
        return;
    }
}

string User::Get_Phone_num()
{
    return User_phone_num;
}



void User::Set_Phone_Num(IN_PARAM string str)
{
    User_phone_num = str;
}

bool User::Del_Myself()
{
    cout << "����yȷ�ϣ�������ĸԭ�ط���" << endl;
    string str_input;
    cin >> str_input;
    getchar();//�Ե��س�
    const char* p = str_input.data();//�������ĸ
    if ('y' == (*p) || 'Y' == (*p)) {
        User* key = gl_User_Head;  //��һ���Ƿ���manager��ɾ�������ģ����ܴ���bug�����ǲ����˼��ξ�ͨ��
        while (key != NULL) {
            if (key->User_phone_num == this->User_phone_num) {
                //�ҵ���������Ԫ��
                User* temp = gl_User_Head;
                while (temp->User_Next != key)
                    temp = temp->User_Next;
                temp->User_Next = key->User_Next;
                delete key;
                cout << "�����ɹ�" << endl;
                system("pause");
                return true;
            }
            key = key->User_Next;
        }
        return true;
    }
    cout << "ȡ������" << endl;
    system("pause");
    return false;
}

void User::Set_Pwd(IN_PARAM string str)
{
    str_pwd = str;
}

 void UserNode::Set_Last_Message(IN_PARAM string first)
{
    this->str_latly_call = first;
}

 void User::Send_Message()
 {
     cout << "�������뷢�͵Ķ��� ";
     string NameOrPhone;
     cin >> NameOrPhone;
     //getchar();
     UserNode* yourObject = SearchUser_node(NameOrPhone);
     if (yourObject == NULL)
     {
         return;
     }
     cout << "�������뷢�͵���Ϣ: ";
     string message;
     cin >> message;
     getchar();
     yourObject->Set_Last_Message(message);
     yourObject->b_is_last_call = true;
     cout << "�ѷ���" << endl;
     system("pause");
 }

 void User::Show_last_call()
 {
     UserNode* yourObject = Head;
     while (NULL != yourObject) {
         if (yourObject->b_is_last_call) {
             cout << yourObject->str_phone_num << "  "<<yourObject->str_name
                 <<"  " << yourObject->str_latly_call << endl;
          
         }

         yourObject = yourObject->next;
     }
     system("pause");
 }

