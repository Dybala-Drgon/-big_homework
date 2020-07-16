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
    for (;;) {
        temp->Set_phone_num();
        //����
        int key = 0;
        UserNode* dection = Head->next;//�ڶ�����㿪ʼ
        while (dection != temp) {
            if (dection->str_phone_num == temp->str_phone_num)
            {
                key++;           //���ظ�
                break;
            }
            dection = dection->next;
        }
        if (0 == key) {
            break;//û���ظ�
        }
        else {
            cout << "����ϵ���Ѵ���" << endl;
            system("pause");
            return;
        }
    }
    temp->Set_info();//��ӳ�ԱҪ¼����Ϣ

}

UserNode* User::SearchUser_node(IN_PARAM string first)
{
    UserNode* temp = Head;
    UserNode* Find_more = Head->next;
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
            Find_more = temp->next;
            int is_print = 0;//����Ƿ��ӡ��ͷ
            while (Find_more != NULL) {
                if (first == Find_more->str_name) {
                    if (0 == is_print) {
                        cout << "����ͬ������ӡ�����˵���Ϣ��Ĭ�ϲ�����һ����Ա��ϸ��Ϣ��������Ŀ�꣬�������ֻ��ž�ȷ����" << endl;
                        cout << endl;
                        cout << "����            id               �绰    " << endl;
                     }
                    if (false == Find_more->b_in_blacklist)
                        cout << left << setw(16) << Find_more->str_name << setw(17) <<
                        Find_more->str_id << setw(11) << Find_more->str_phone_num << endl;
                    is_print++;
                }
                Find_more = Find_more->next;
            }
            cout << "-----------------------------------��������ϸ��Ϣ------------------------------------------" << endl;
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
    cout << " | 12�����鿴�����ϵ��     13�����鿴����       |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 14�������������أ�       15��������           |" << endl;
    cout << " | -----------------��0�˳�----------------------|" << endl;
}

void User::Display()
{

    int num=0, key = 0, lab = 0;	//key�����˳���lab��������
    for (;;) {
        num = 0;
        if (lab == 0) {
            system("cls");		    //����
            Main_view();		//���´�ӡ�˵�
        }
        string str_choose;
        cin >> str_choose;
        getchar(); //�Ե��س�
        if (str_choose.length() > 2) {
            cout << "��������" << endl;
            system("pause");
            lab = 1;
            continue;
        }
        for (int i = 0; i < str_choose.length(); i++) {
            int key = str_choose[i] - '0';
            num = num * 10 + key;
        }
        string first;
        switch (num)
        {
        case 1:
            system("cls");
            AddUser();
            cout << "����������" << endl;
            system("pause");
            lab = 0;
            break;
        case 2:	//��ʾ��Ϣ
        {
            system("cls");
            cout << "1.ȫ��չʾ   2.����չʾ   3.չʾ�Ǳ���ϵ��   4.չʾͬѧ   5.չʾ����    6.չʾͬ��   7.������" << endl;

            int n = 0;
            cin >> str_choose;
            for (int i = 0; i < str_choose.length(); i++) {
                int key = str_choose[i] - '0';
                n = n * 10 + key;
            }
            getchar();
            Choose_Show(n);
            lab = 0;
            break;
        }
        case 3:	//���� 
        {
            cout << "���������Ϣ�����ֻ��ߵ绰��" << endl;

            cin >> first;
                system("cls");
            UserNode* T = SearchUser_node(first);
            if (NULL != T) {
                T->Show_detail();
            }
            lab = 0;
            break;
        }
        case 4:	 //ɾ��
            cout << "����ɾ���ĵ绰(�����֪�����֣���ͨ����ѯ���ܻ�õ绰����):" << endl;

            cin >> first;
            getchar();
            DeleteUserNode(first);
            lab = 0;

            break;
        case 5:	//  �޸�
            cout << "�����޸ĵĵ绰�������֪�����֣���ͨ����ѯ���ܻ�õ绰���룩" << endl;

            cin >> first;
            getchar();
            system("cls");
            ReviseUser(first);
            lab = 0;
            break;
        case 6:	//  ����
            SaveData(User_phone_num);
            cout << "����ɹ�" << endl;
            system("Pause");
            lab = 0;
            break;
        case 7:	//  ��ȡ
            ReadData(User_phone_num);
            cout << "��ȡ�ɹ�" << endl;
            system("Pause");
            lab = 0;
            break;
        case 8://����
        {
            cout << "���������ߵĵ绰�������֪�����֣���ͨ����ѯ���ܻ�õ绰���룩" << endl;
            cin >> first;
            getchar();
            system("cls");
            UserNode* T = SearchUser_node(first);
            if (NULL != T)
                T->Set_Black_List();
            
            lab = 0;
            break;
        }
        case 9://������
        {
            cout << "�����Ƴ����ڵ���Ϣ�����ֻ��ߵ绰��" << endl;
            cin >> first;
            getchar();
            system("cls");
            UserNode* T = SearchUser_node_black(first);
            if (NULL != T) {
                T->Show_detail();
                T->Set_Black_List_Out();
            }
            
            lab = 0;
            break;
        }
        case 10:
            cout << "�޸�����:" << endl;
            Change_Pwd();
            lab = 0;
            break;
        case 11://����Ϣ
            Send_Message();
            lab = 0;
            break;
        case 12: //�����ϵ
            Show_last_call();
            lab = 0;
            break;
        case 13:
            Deal_Push();
            lab = 0;
            break;
        case 14:
            cout << "����" << endl;
            if (Del_Myself())//��������ɹ���ֱ���˳����棬��Ч������0
                key++;
            lab = 0;
            break;
        case 15:
            EnCode(User_phone_num + ".txt");
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
    case 3:         //�Ǳ�
        Show_star();
        break;
    case 4:         //ͬѧ
        Show_classmate();
        break;
    case 5:         //����
        Show_relative();
        break;
    case 6:         //ͬ��
        Show_colleague();
        break;
    case 7:
        Show_blacklist();
        break;
    case 2:
        Show_Usernode_With_Sort();
        break;
    default:
        cout << "��������,�����������˵�" << endl;
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
    //system("cls");
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
                    cout << "�޸�����" << endl;
                    temp->Set_name();
                    break;
                case '2': 
                    cout << "�޸�id" << endl;
                    temp->Set_id();
                    break;
                case '3': 
                    cout << "�޸�academic" << endl;
                    temp->Set_academic();
                    break;
                case '4': 
                    cout << "�޸�major" << endl;
                    temp->Set_major();
                    break;
                case '6':
                    cout << "�޸ĵ�ַ" << endl;
                    temp->Set_address();
                    break;
                case '7':
                    for (;;) {
                        cout << "�޸ĵ绰" << endl;
                        temp->Set_phone_num();
                        //����
                        int key = 0;
                        UserNode* dection = Head->next;//�ڶ�����㿪ʼ
                        if (dection == temp)
                            dection = dection->next;
                        while (dection != NULL) {
                            if (dection->str_phone_num == temp->str_phone_num)
                            {
                                key++;           //���ظ�
                                break;
                            }
                            dection = dection->next;
                            if (dection == temp)
                                dection = dection->next;
                            
                        }
                        if (0 == key) {
                            break;//û���ظ�
                        }
                        else {
                            cout << "����ϵ���Ѵ���" << endl;
                            //system("pause");
                        }
                    }
                    
                  //  temp->Set_phone_num();
                    break;
                case '8':
                    cout << "�޸Ĺ�˾" << endl;
                    temp->Set_company();
                    break;
                case '9':
                    cout << "�޸�����" << endl;
                    temp->Set_e_mail();
                case 'x':
                    cout << "�޸ķ���" << endl;
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
    cout << endl;
    cout << "���½�������ĸ�����֣����ֳ��֣���ֹ����ʹ�ã�����ָ�����ʹ���»���" << endl;
    Set_name();
   // Set_phone_num();
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
        << "��������\n��1:�Ǳ���ϵ�ˣ�  "
        << "��2:ͬѧ   " << "\n��3:����  "
        << "        ��4:ͬ��      ��������0:����"  << endl;
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
            if (c < 0||c=='_') continue;
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
            cout << "����������רҵ��";
        }
    }
}

const string sProvinces[34] = {"beijing", "tianjin", "shanghai", "chongqing", "hebei", "shanxi",
                  "neimenggu", "liaoning", "jilin", "heilongjiang", "jiangsu", "zhejiang",
                  "anhui", "fujian", "jiangxi", "shandong" , "henan", "hubei", "hunan", "guangdong", 
                  "guangxi", "hainan", "sichuan", "guizhou", "yunnan", "xizang", "shaanxi", "gansu" ,
                  "qinghai", "ningxia", "xinjiang", "xianggang", "aomen", "taiwan"};
                 
void UserNode::Set_province()
{
    cout << "����ó�Աʡ��(sichuan henan)�� ";// input your province
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
            if (c < 0||c=='_') continue;
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
            if (c < 0||c=='_') continue;

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
    //����


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
            if (c < 0||c=='_') continue;
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
    cout << "�����빫˾��";
    string strInput;
    bool b_flag = true;
    while (1)
    {
        cin >> strInput;
        getchar();
        for (char c : strInput)
        {
            if (c < 0||c=='_') continue;
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
    //system("cls");
    cout << "name                            phone_num                   e_mail" << endl;
    cout << left << setw(32) << str_name << setw(28) << str_phone_num << str_e_mail << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "major                           academic                    province" << endl;
    cout << left << setw(32) << str_major << setw(28) << str_academic << str_province << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "company                         adress                         id" << endl;
    cout << left << setw(32) << str_company << setw(28)<<str_address <<str_id<< endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    system("pause");

}


void UserNode::Set_Black_List()
{
    Show_detail();
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
    else {
        cout << "ȡ������" << endl;
        system("pause");
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

string User::Get_Pwd()
{
    return str_pwd;
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

                string str;
                str = ((this->User_phone_num) + ".txt");
                const char* savePath = str.c_str();
                if (remove(savePath) == 0)
                {
                    cout << "�����ɹ�" << endl;
                }
                else
                {
                    cout << "ɾ���ļ�ʧ��" << endl;
                }
                system("pause");
                delete key;
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
     /*
     
     ������һ���ӿڸ���������緢�ͺ�����
     ���ܻ��õ������̣���ʱû���漰��
     ����ע�����½ӿ�
     
     */
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

 void User::Receive_Push(IN_PARAM string pushed)
 {
     str_push_phone = pushed;
 }


 void User::Show_Usernode_With_Sort() {
     if (Head->next == NULL)
     {
         cout << "����ϵ�ˣ��޷���ӡ" << endl;
         system("pause");
         return;
     }
     Clear_Print();           //����ۼ�
     cout << "���绰���������ӡ" << endl;
     cout << "����            id               �绰    " << endl;
     UserNode* U_Print_Ctrl = Head->next;        //��ʼ���Ӵνڵ㿪ʼ����
     //Ҫ���ҵ������Ǹ�
     UserNode* User_Iter = Head->next;
     UserNode* num_max = NULL;
     while (User_Iter != NULL)                    //ÿ��ѭ���ҳ���󲢱��
     {
         if (((User_Iter->str_phone_num) > (U_Print_Ctrl->str_phone_num)) )   //�绰�������
         {
             U_Print_Ctrl = User_Iter;  //�绰�������
         }
         User_Iter = User_Iter->next;
     }
     num_max = U_Print_Ctrl;
     while (!All_Printed())                           //���ж��Ƿ��ӡ�꣬ÿ��ѭ����ӡһ��
     {
         U_Print_Ctrl = num_max;
         User_Iter = Head->next;
         while (User_Iter != NULL)                    //ÿ��ѭ���ҳ���С�����
         {
             if (((User_Iter->str_phone_num) < (U_Print_Ctrl->str_phone_num ))&& !(User_Iter->b_is_printed))   //�绰�����С��δ��ӡ
             {
                 U_Print_Ctrl = User_Iter;  //�ҵ�Ҫ��ӡ��Ԫ�أ��绰�����С
             }
             User_Iter = User_Iter->next;
         }
         cout << left << setw(16) << U_Print_Ctrl->str_name << setw(17)                    //���Դ�ӡ
             << U_Print_Ctrl->str_id << setw(11) << U_Print_Ctrl->str_phone_num << endl;
         U_Print_Ctrl->b_is_printed = true;                                                //��Ǵ�ӡ��
     }
     system("pause");
 }

 void User::Clear_Print()
 {
     UserNode* Uprint_clearer = Head;
     if (NULL == Head->next)
     {
         cout << "ͨѶ¼Ϊ�գ��������� " << endl;
         system("pause");
         return;
     }
     Uprint_clearer = Uprint_clearer->next;  //�ڶ����ڵ�
     while (Uprint_clearer != NULL)
     {
         Uprint_clearer->b_is_printed = false;        //��մ�ӡ�ۼ�
         Uprint_clearer = Uprint_clearer->next;
     }
 }

 bool User::All_Printed()
 {
     UserNode* Uprint_Scan = Head;
     if (NULL == Head->next)
     {
         return true;
     }
     Uprint_Scan = Head->next;
     while (Uprint_Scan != NULL)
     {
         if (!(Uprint_Scan->b_is_printed) ) //��û��ӡ��
         {
             return false;               //��û��ӡ��
         }
         Uprint_Scan = Uprint_Scan->next;
     }
     return true;                        //����ȫ����ӡ
 }

 void User::Deal_Push()
 {
     if (str_push_phone.length() == 0) {
         cout << "�����Ͷ���" << endl;
         system("pause");
         return;
     }
     else {
         cout << "������ʶ����Ϊ:" << str_push_phone << endl;
         system("pause");
         return;
     }

 }


 void User::SaveData(string user_phone)//���浥���û������ݵ��ļ�
 {
     ofstream fout;
     string filename = user_phone + ".txt";
     fout.open(filename);//�ļ���
     if (!fout.is_open())
     {
         cout << filename << "open error";
         exit(1);
     }
     //�򿪳ɹ�
     fout << "name/id/phone_num/e_mail/academic/major/province/company/address/flag";//��ӡ��ͷ
     UserNode* temp = Head->next;
     if (temp)//�����û����д�ӡ�������ȡ����
     {
         fout << endl;
     }
     while (temp)//���û����ӡ�û���Ϣ����ͬ��Ϣ��/����
     {
         fout << temp->str_name << "/" << temp->str_id << "/" << temp->str_phone_num << "/" << temp->str_e_mail << "/" << temp->str_academic;
         fout << "/" << temp->str_major << "/" << temp->str_province << "/" << temp->str_company << "/" << temp->str_address;
         fout << "/" << temp->b_is_important << "/" << temp->b_is_classmate << "/" << temp->b_is_relative << "/" << temp->b_is_colleague << "/" << temp->b_in_blacklist;
         temp = temp->next;
         if (temp)
         {
             fout << endl;
         }
     }
     fout << flush;
     fout.close();//�ر��ļ�
 }


 void User::ReadData(string user_phone) //�ӵ����ļ����ȡ�����û�������
 {
     string filename = user_phone + ".txt";
     UserNode* temp = Head;
     char buf[50];//��������Ŷ�ȡ������
     char tool[100];//�Ե���ͷ��ʵ���ô�
     ifstream fin(filename);

     if (!fin.is_open())
     {
         cout << filename << "open error";
         exit(1);
     }

     //�򿪳ɹ�
     fin.getline(tool, 100);//��ȡ��ͷ

     while (!fin.eof())//û���ļ�ĩβ���ȡһ������
     {
         temp->next = new UserNode;
         temp = temp->next;
         fin.getline(buf, 50, '/');
         temp->str_name = buf;
         fin.getline(buf, 50, '/');
         temp->str_id = buf;
         fin.getline(buf, 50, '/');
         temp->str_phone_num = buf;
         fin.getline(buf, 50, '/');
         temp->str_e_mail = buf;
         fin.getline(buf, 50, '/');
         temp->str_academic = buf;
         fin.getline(buf, 50, '/');
         temp->str_major = buf;
         fin.getline(buf, 50, '/');
         temp->str_province = buf;
         fin.getline(buf, 50, '/');
         temp->str_company = buf;
         fin.getline(buf, 50, '/');
         temp->str_address = buf;
         string str = "1";//�����жϱ�־λ�Ƿ�Ϊ1
         fin.getline(buf, 50, '/');
         if (buf == str)//Ϊ1
         {
             temp->b_is_important = true;
         }
         else
         {
             temp->b_is_important = false;
         }
         fin.getline(buf, 50, '/');
         if (buf == str)//Ϊ1
         {
             temp->b_is_classmate = true;
         }
         else
         {
             temp->b_is_classmate = false;
         }
         fin.getline(buf, 50, '/');
         if (buf == str)//Ϊ1
         {
             temp->b_is_relative = true;
         }
         else
         {
             temp->b_is_relative = false;
         }
         fin.getline(buf, 50, '/');
         if (buf == str)//Ϊ1
         {
             temp->b_is_colleague = true;
         }
         else
         {
             temp->b_is_colleague = false;
         }
         fin.getline(buf, 50);
         if (buf == str)//Ϊ1
         {
             temp->b_in_blacklist = true;
         }
         else
         {
             temp->b_in_blacklist = false;
         }
     }
     fin.close();//�ر��ļ�
 }


 void Read()//��ȡ����
 {
     User* temp = gl_User_Head;

     temp = temp->User_Next;
     while (temp)//�����û����ȡ��Ӧ�ļ�����Ϣ
     {

         string phone_num = temp->Get_Phone_num();

         temp->ReadData(phone_num);

         temp = temp->User_Next;
     }

 }

 void Save()//���溯��
 {
     User* temp = gl_User_Head;
     temp = temp->User_Next;
     while (temp)
     {
         string phone_num;
         phone_num = temp->Get_Phone_num();
         
         temp->SaveData(phone_num);
         
         temp = temp->User_Next;

     }
 }



 void EnCode(string filename)//���ܺ���
 {
     fstream BeforeFile, AfterFile;
     string fileNameBefore = filename, fileNameAfter = "s_" + filename;
     //�򿪴������ļ�					
     BeforeFile.open(fileNameBefore, ios::in | ios::binary);
     //�򿪼��ܺ��ļ�
     AfterFile.open(fileNameAfter, ios::out | ios::binary);

     BeforeFile.seekg(0, ios::end);//��λ�ļ�����ָ�뵽ĩβ
     streamoff  size = BeforeFile.tellg();	//��ȡ��С
     BeforeFile.seekg(0, ios::beg);//��λ�ļ�����ָ�뵽�ļ�ͷ
     for (streamoff i = 0; i < size; i++) {
         //��BeforeFile�����ݴ�������AfterFile��
         AfterFile.put(BeforeFile.get() ^ 0x88);//���ܻ���ܱ���  0x88 
     }

     //�ر��ļ�
     BeforeFile.close();
     AfterFile.close();
     cout << "���ܻ���ܳɹ�" << endl;
     const char* savePath = filename.c_str();
     if (remove(savePath) == 0)//ɾ��ԭ�ļ�
     {
         cout << "ɾ��ԭ�ļ��ɹ�" << endl;
         system("Pause");
     }
     else
     {
         cout << "ɾ��ԭ�ļ�ʧ��" << endl;
         system("Pause");
     }
 }

 UserNode* User::SearchUser_node_black(IN_PARAM string first)
 {
     UserNode* temp = Head;
     UserNode* Find_more = Head->next;
     if (temp->next == NULL) {
         cout << "���޴���" << endl;
         system("pause");
         return NULL;
     }
     temp = temp->next;//�ӵڶ����ڵ㿪ʼ����
     while (temp != NULL)
     {
         if (first == temp->str_name&&temp->b_in_blacklist==true)
         {
             Find_more = temp->next;
             int is_print = 0;//����Ƿ��ӡ��ͷ
             while (Find_more != NULL) {
                 if (first == Find_more->str_name&&Find_more->b_in_blacklist==true) {
                     if (0 == is_print) {
                         cout << "����ͬ������ӡ�����˵���Ϣ��Ĭ�ϲ�����һ����Ա��ϸ��Ϣ��������Ŀ�꣬�������ֻ��ž�ȷ����" << endl;
                         cout << endl;
                         cout << "����            id               �绰    " << endl;
                     }
                     if (false == Find_more->b_in_blacklist)
                         cout << left << setw(16) << Find_more->str_name << setw(17) <<
                         Find_more->str_id << setw(11) << Find_more->str_phone_num << endl;
                     is_print++;
                 }
                 Find_more = Find_more->next;
             }
             cout << "-----------------------------------��������ϸ��Ϣ------------------------------------------" << endl;
             return temp;
         }
         if (first == temp->str_phone_num&&temp->b_in_blacklist==true)
         {
             return temp;
         }
         temp = temp->next;
     }
     cout << "���޴���" << endl;
     system("pause");
     return NULL;
 }