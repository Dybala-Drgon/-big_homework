#include"User.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
using namespace std;
extern User* gl_User_Head;
extern Manager man;

User::~User()               //防止内存泄漏
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
//    cout << "释放user的空间" << endl;
}

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

UserNode* User::SearchUser_node(IN_PARAM string first)
{
    UserNode* temp = Head;
    if (temp->next == NULL) {
    cout << "查无此人" << endl;
    system("pause");
    return NULL; 
    }
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
   cout << "查无此人" << endl;
   //---------------------以下是模糊查找----------------------------------------
   cout << "***************************************************" << endl;
   cout << "宁可能想找..." << endl;
   cout << "名字            id               电话    " << endl;
   temp = Head->next;//第二个节点开始遍历
   while (temp != NULL)
   {
       string::size_type idx;
       string::size_type idx2;
       idx = temp->str_name.find(first);
       idx2 = temp->str_phone_num.find(first);
       if (idx != string::npos||idx2!=string::npos)//存在子串。
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


void User::DeleteUserNode(IN_PARAM string first) //删除通讯录节点
{
    if(NULL == (Head->next))
    {
        cout << "通讯录为空" << endl;
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
            cout << "删除成功" << endl;
            system("pause");
}

void User::Main_view()
{
    cout << " | ***********欢迎进入通讯录管理系统*************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | ************----个人模式----******************|" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | *********  (键入对应编号进入相应模块)  *******|" << endl;
    cout << " | 1——录入信息            2——显示信息        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 3——查找通讯录信息      4——删除信息        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 5——修改信息            6——保存信息        |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 7——读取信息           8/9——拉黑/反拉黑    |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 10——修改密码           11——发送信息       |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 12——查看最近联系人     13——销户（慎重）   |" << endl;
    cout << " | -----------------按0退出----------------------|" << endl;
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
            cout << "1.全部展示   2.展示星标联系人   3.展示同学   4.展示家人    5.展示同事   6.黑名单" << endl;
            int n;
            cin >> n;
            getchar();
            Choose_Show(n);
            lab = 0;
            break;
        case 3:	//查找 
        {
            cout << "输入查找信息（名字或者电话）" << endl;

            cin >> first;
            UserNode* T = SearchUser_node(first);
            if(NULL!=T)
            T->Show_detail();
            lab = 0;
            break;
        }
        case 4:	 //删除
            cout << "输入删除的信息（名字或者电话）" << endl;

            cin >> first;
            getchar();
            DeleteUserNode(first);
            lab = 0;

            break;
        case 5:	//  修改
            cout << "输入修改的信息（名字或者电话）" << endl;

            cin >> first;
            getchar();
            ReviseUser(first);
            lab = 0;
            break;
        case 6:	//  保存
            lab = 0;
            break;
        case 7:	//  读取
            lab = 0;
            break;
        case 8://拉黑
        {
            cout << "输入修改的信息（名字或者电话）" << endl;
            cin >> first;
            getchar();
            UserNode* T = SearchUser_node(first);
            if (NULL != T)
                T->Set_Black_List();
            
            lab = 0;
            break;
        }
        case 9://反拉黑
        {
            cout << "输入修改的信息（名字或者电话）" << endl;
            cin >> first;
            getchar();
            UserNode* T = SearchUser_node(first);
            if (NULL != T)
                T->Set_Black_List_Out();
            
            lab = 0;
            break;
        }
        case 10:
            cout << "修改密码:" << endl;
            Change_Pwd();
            lab = 0;
            break;
        case 13:
            cout << "销户" << endl;
            if(Del_Myself())//如果销户成功，直接退出界面，等效于输入0
            key++;
            lab = 0;
            break;
        case 11://发信息
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
            cout << "输入有误，重新输入" << endl;
            lab++;
            break;
        }
        if (key != 0)
            break;//按0退出
    }
}

void User::Choose_Show(int first)
{
    switch (first)
    {
    case 1:         //全部
        Showdata();
        break;
    case 2:         //星标
        Show_star();
        break;
    case 3:         //同学
        Show_classmate();
        break;
    case 4:         //家人
        Show_relative();
        break;
    case 5:         //同事
        Show_colleague();
        break;
    case 6:
        Show_blacklist();
        break;
    default:
        cout << "输入有误,任意键返回主菜单" << endl;
        system("pause");
        break;
    }
}


void User::Showdata() //打印简略信息（名字、id、电话）
    {
         cout << "名字            id               电话    " << endl;
        UserNode* temp = Head->next;//第二个节点开始遍历
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
    cout << "名字            id               电话    " << endl;
    UserNode* temp = Head->next;//第二个节点开始遍历
    while (temp != NULL)
    {
        if(true==temp->b_is_important&& false == temp->b_in_blacklist) //是星标就打印
        cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");

}


void User::Show_relative()
{
    cout << "名字            id               电话    " << endl;
    UserNode* temp = Head->next;//第二个节点开始遍历
    while (temp != NULL)
    {
        if (true == temp->b_is_relative&& false == temp->b_in_blacklist) //是家人就打印
            cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");
}

void User::Show_classmate()
{
    cout << "名字            id               电话    " << endl;
    UserNode* temp = Head->next;//第二个节点开始遍历
    while (temp != NULL)
    {
        if (true == temp->b_is_classmate&& false == temp->b_in_blacklist) //是同学就打印
            cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");
}

void User::Show_colleague()
{
    cout << "名字            id               电话    " << endl;
    UserNode* temp = Head->next;//第二个节点开始遍历
    while (temp != NULL)
    {
        if (true == temp->b_is_colleague&& false == temp->b_in_blacklist) //是同事就打印
            cout << left << setw(16) << temp->str_name << setw(17) <<
            temp->str_id << setw(11) << temp->str_phone_num << endl;
        temp = temp->next;
    }
    system("pause");
}

void User::Show_blacklist()
{
    cout << "名字            id               电话    " << endl;
    UserNode* temp = Head->next;//第二个节点开始遍历
    while (temp != NULL)
    {
        if (true == temp->b_in_blacklist) //是黑名单就打印
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
        cout << "请确认密码" << endl;
        cin >> str2;
        if (str1 == str2) {
            cout << "修改成功" << endl;
            str_pwd = str1;
            break;
        }
        else {
            cout << "两次密码不一致,重新输入" << endl;
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


void User::ReviseUser(IN_PARAM string first) { //修改用户
    if (NULL == (Head->next))
    {
        cout << "通讯录为空" << endl;
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
    cout << "键入数字（包含组合）选择修改的目标（首先输入0退出）" << endl;
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
            if (!(c <= '9' && c >= '1')&&c!='x')  //防止用户乱输入
            {
                b_Flag = false;
            }
        }
        if (b_Flag == true)              //正确输入
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
            cout << "修改成功" << endl;
            system("pause");
            return;
        }
        else                        //重输
        {
            b_Flag = true;
            cout << "重新输入" << endl;
        }
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
    cout << "请输入一个仅含1234的整数来确定分组 " << endl
        << "若该整数含1：星标联系人，  "
        << "含2:同学   " << "含3:家人  "
        << "含4:同事      首先输入0:跳过"  << endl;
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
            if (!(c <= '4' && c >= '1'))  //防止用户乱输入
            {
                b_Flag = false;
            }
        }
        if (b_Flag == true)              //正确输入
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

            cout << "操作成功" << endl;
            system("pause");
            return;
        }
        else                        //重输
        {
            b_Flag = true;
            cout << "重新输入" << endl;
        }
    }
}

void UserNode::Set_major()
{
    cout << "输入该成员的专业： ";// input your province
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

const string sProvinces[34] = {"beijing", "tianjin", "shanghai", "chongqing", "hebei", "shanxi",
                  "neimenggu", "liaoning", "jilin", "heilongjiang", "jiangsu", "zhejiang",
                  "anhui", "fujian", "jiangxi", "shandong" , "henan", "hubei", "hunan", "guangdong"
                  "guangxi", "hainan", "sichuan", "guizhou", "yunnan", "xizang", "shaanxi", "gansu"
                  "qinghai", "ningxia", "xinjiang", "xianggang", "aomen", "taiwan"};
                 
void UserNode::Set_province()
{
    cout << "输入该成员省份： ";// input your province
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
    cout << "输入该成员的现地址： ";// input your address
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
            cout << "重新输入" << endl;
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
        cout << "对象已在黑名单内" << endl;
        system("pause");
        return;
    }
    cout << "是否将该对象拉进黑名单?" << endl
        << "按y拉入" << endl;
    char chr[100];
    cin >> chr;
    getchar();
    if (chr[0] == 'y' || chr[0] == 'Y')
    {
        b_in_blacklist = true;
        cout << "操作成功" << endl;
        system("pause");
        return;
    }
}

void UserNode::Set_Black_List_Out()
{
    if (b_in_blacklist == false)
    {
        cout << "对象未被拉黑" << endl;
        system("pause");
        return;
    }
    cout << "是否将该对象移出黑名单?" << endl
        << "按y移出" << endl;
    char chr[100];
    cin >> chr;
    getchar();
    if (chr[0] == 'y' || chr[0] == 'Y')
    {
        b_in_blacklist = false;
        cout << "操作成功" << endl;
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
    cout << "输入y确认，其他字母原地返回" << endl;
    string str_input;
    cin >> str_input;
    getchar();//吃掉回车
    const char* p = str_input.data();//获得首字母
    if ('y' == (*p) || 'Y' == (*p)) {
        User* key = gl_User_Head;  //这一段是仿造manager的删除函数的，可能存在bug，但是测试了几次均通过
        while (key != NULL) {
            if (key->User_phone_num == this->User_phone_num) {
                //找到了销户的元素
                User* temp = gl_User_Head;
                while (temp->User_Next != key)
                    temp = temp->User_Next;
                temp->User_Next = key->User_Next;
                delete key;
                cout << "销户成功" << endl;
                system("pause");
                return true;
            }
            key = key->User_Next;
        }
        return true;
    }
    cout << "取消销户" << endl;
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
     cout << "输入你想发送的对象： ";
     string NameOrPhone;
     cin >> NameOrPhone;
     //getchar();
     UserNode* yourObject = SearchUser_node(NameOrPhone);
     if (yourObject == NULL)
     {
         return;
     }
     cout << "输入你想发送的信息: ";
     string message;
     cin >> message;
     getchar();
     yourObject->Set_Last_Message(message);
     yourObject->b_is_last_call = true;
     cout << "已发送" << endl;
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

