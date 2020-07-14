#include"User.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
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
            system("cls");
            AddUser();
            lab = 0;
            break;
        case 2:	//显示信息
            system("cls");
            Showdata();
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


void User::Showdata() //打印简略信息（名字、id、电话）
    {
         cout << "名字            id               电话    " << endl;
        UserNode* temp = Head->next;//第二个节点开始遍历
        while (temp != NULL)
        {
            cout << left << setw(16) << temp->str_name << setw(17) << temp->str_id << setw(11) << temp->str_phone_num << endl;
            temp = temp->next;
        }
        system("pause");
          
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
    cout << "输入你的专业： ";// input your province
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
            cout << "请重新输入专业";
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
                  //这个东东放头文件
void UserNode::Set_province()
{
    cout << "输入你的省份： ";// input your province
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
            cout << "请重新输入省份：";
        }
    }

}

void UserNode::Set_address()
{
    cout << "输入你的地址： ";// input your address
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
            cout << "请重新输入地址： ";
        }
    }
}
void UserNode::Set_name() {
    cout << "请输入name："; //input your English name 
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
            cout << "请重新输入name：";
        }
    }
}

void UserNode::Set_id() {
    cout << "请输入id(6位)：";
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
            cout << "请重新输入id：";
        }
    }
}

void UserNode::Set_phone_num()
{
    cout << "请输入电话号码：";
   
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
        cout << "重新输入"<<endl;
    }
  }
}


void UserNode::Set_academic()
{
    cout << "请输入academic：";
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
            cout << "请重新输入academic：";
        }
    }
}

void UserNode::Set_e_mail()
{
    cout << "请输入e-mail：";
    string sinput;
    bool b_ch = false;
    while (1)
    {
        cin >> sinput;
        getchar();
        for (char& c : sinput)
        {
            if (c == '@')  //有@即是邮件
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
            cout << "请重新输入e-mail：";
        }
    }
}

void UserNode::Set_company()
{
    cout << "请输入公司";
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