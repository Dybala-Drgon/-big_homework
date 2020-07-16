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
    for (;;) {
        temp->Set_phone_num();
        //查重
        int key = 0;
        UserNode* dection = Head->next;//第二个结点开始
        while (dection != temp) {
            if (dection->str_phone_num == temp->str_phone_num)
            {
                key++;           //有重复
                break;
            }
            dection = dection->next;
        }
        if (0 == key) {
            break;//没有重复
        }
        else {
            cout << "该联系人已存在" << endl;
            system("pause");
            return;
        }
    }
    temp->Set_info();//添加成员要录入信息

}

UserNode* User::SearchUser_node(IN_PARAM string first)
{
    UserNode* temp = Head;
    UserNode* Find_more = Head->next;
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
            Find_more = temp->next;
            int is_print = 0;//检测是否打印表头
            while (Find_more != NULL) {
                if (first == Find_more->str_name) {
                    if (0 == is_print) {
                        cout << "存在同名，打印其他人的信息，默认操作第一个成员详细信息，若非您目标，请输入手机号精确查找" << endl;
                        cout << endl;
                        cout << "名字            id               电话    " << endl;
                     }
                    if (false == Find_more->b_in_blacklist)
                        cout << left << setw(16) << Find_more->str_name << setw(17) <<
                        Find_more->str_id << setw(11) << Find_more->str_phone_num << endl;
                    is_print++;
                }
                Find_more = Find_more->next;
            }
            cout << "-----------------------------------以下是详细信息------------------------------------------" << endl;
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
    cout << " | 12——查看最近联系人     13——查看推送       |" << endl;
    cout << " | ----------------------------------------------|" << endl;
    cout << " | 14——销户（慎重）       15——加密           |" << endl;
    cout << " | -----------------按0退出----------------------|" << endl;
}

void User::Display()
{

    int num=0, key = 0, lab = 0;	//key控制退出，lab控制清屏
    for (;;) {
        num = 0;
        if (lab == 0) {
            system("cls");		    //清屏
            Main_view();		//重新打印菜单
        }
        string str_choose;
        cin >> str_choose;
        getchar(); //吃掉回车
        if (str_choose.length() > 2) {
            cout << "重新输入" << endl;
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
            cout << "返回主界面" << endl;
            system("pause");
            lab = 0;
            break;
        case 2:	//显示信息
        {
            system("cls");
            cout << "1.全部展示   2.排序展示   3.展示星标联系人   4.展示同学   5.展示家人    6.展示同事   7.黑名单" << endl;

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
        case 3:	//查找 
        {
            cout << "输入查找信息（名字或者电话）" << endl;

            cin >> first;
                system("cls");
            UserNode* T = SearchUser_node(first);
            if (NULL != T) {
                T->Show_detail();
            }
            lab = 0;
            break;
        }
        case 4:	 //删除
            cout << "输入删除的电话(如果仅知道名字，请通过查询功能获得电话号码):" << endl;

            cin >> first;
            getchar();
            DeleteUserNode(first);
            lab = 0;

            break;
        case 5:	//  修改
            cout << "输入修改的电话（如果仅知道名字，请通过查询功能获得电话号码）" << endl;

            cin >> first;
            getchar();
            system("cls");
            ReviseUser(first);
            lab = 0;
            break;
        case 6:	//  保存
            SaveData(User_phone_num);
            cout << "保存成功" << endl;
            system("Pause");
            lab = 0;
            break;
        case 7:	//  读取
            ReadData(User_phone_num);
            cout << "读取成功" << endl;
            system("Pause");
            lab = 0;
            break;
        case 8://拉黑
        {
            cout << "输入拉黑者的电话（如果仅知道名字，请通过查询功能获得电话号码）" << endl;
            cin >> first;
            getchar();
            system("cls");
            UserNode* T = SearchUser_node(first);
            if (NULL != T)
                T->Set_Black_List();
            
            lab = 0;
            break;
        }
        case 9://反拉黑
        {
            cout << "输入移除拉黑的信息（名字或者电话）" << endl;
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
            cout << "修改密码:" << endl;
            Change_Pwd();
            lab = 0;
            break;
        case 11://发信息
            Send_Message();
            lab = 0;
            break;
        case 12: //最近联系
            Show_last_call();
            lab = 0;
            break;
        case 13:
            Deal_Push();
            lab = 0;
            break;
        case 14:
            cout << "销户" << endl;
            if (Del_Myself())//如果销户成功，直接退出界面，等效于输入0
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
    case 3:         //星标
        Show_star();
        break;
    case 4:         //同学
        Show_classmate();
        break;
    case 5:         //家人
        Show_relative();
        break;
    case 6:         //同事
        Show_colleague();
        break;
    case 7:
        Show_blacklist();
        break;
    case 2:
        Show_Usernode_With_Sort();
        break;
    default:
        cout << "输入有误,即将返回主菜单" << endl;
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
    //system("cls");
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
                    cout << "修改姓名" << endl;
                    temp->Set_name();
                    break;
                case '2': 
                    cout << "修改id" << endl;
                    temp->Set_id();
                    break;
                case '3': 
                    cout << "修改academic" << endl;
                    temp->Set_academic();
                    break;
                case '4': 
                    cout << "修改major" << endl;
                    temp->Set_major();
                    break;
                case '6':
                    cout << "修改地址" << endl;
                    temp->Set_address();
                    break;
                case '7':
                    for (;;) {
                        cout << "修改电话" << endl;
                        temp->Set_phone_num();
                        //查重
                        int key = 0;
                        UserNode* dection = Head->next;//第二个结点开始
                        if (dection == temp)
                            dection = dection->next;
                        while (dection != NULL) {
                            if (dection->str_phone_num == temp->str_phone_num)
                            {
                                key++;           //有重复
                                break;
                            }
                            dection = dection->next;
                            if (dection == temp)
                                dection = dection->next;
                            
                        }
                        if (0 == key) {
                            break;//没有重复
                        }
                        else {
                            cout << "该联系人已存在" << endl;
                            //system("pause");
                        }
                    }
                    
                  //  temp->Set_phone_num();
                    break;
                case '8':
                    cout << "修改公司" << endl;
                    temp->Set_company();
                    break;
                case '9':
                    cout << "修改邮箱" << endl;
                    temp->Set_e_mail();
                case 'x':
                    cout << "修改分组" << endl;
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
    cout << endl;
    cout << "以下仅允许字母，汉字，数字出现，禁止符号使用，如需分隔，请使用下划线" << endl;
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
    cout << "请输入一个仅含1234的整数来确定分组 " << endl
        << "若该整数\n含1:星标联系人，  "
        << "含2:同学   " << "\n含3:家人  "
        << "        含4:同事      首先输入0:跳过"  << endl;
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
            cout << "请重新输入专业：";
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
    cout << "输入该成员省份(sichuan henan)： ";// input your province
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
    //查重


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
    cout << "请输入公司：";
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
            cout << "重新输入" << endl;
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
    else {
        cout << "取消拉黑" << endl;
        system("pause");
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

                string str;
                str = ((this->User_phone_num) + ".txt");
                const char* savePath = str.c_str();
                if (remove(savePath) == 0)
                {
                    cout << "销户成功" << endl;
                }
                else
                {
                    cout << "删除文件失败" << endl;
                }
                system("pause");
                delete key;
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
     /*
     
     这里留一个接口给正真的网络发送函数，
     可能会用到网络编程，暂时没有涉及，
     特意注释留下接口
     
     */
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

 void User::Receive_Push(IN_PARAM string pushed)
 {
     str_push_phone = pushed;
 }


 void User::Show_Usernode_With_Sort() {
     if (Head->next == NULL)
     {
         cout << "无联系人，无法打印" << endl;
         system("pause");
         return;
     }
     Clear_Print();           //清理痕迹
     cout << "按电话号码升序打印" << endl;
     cout << "名字            id               电话    " << endl;
     UserNode* U_Print_Ctrl = Head->next;        //初始化从次节点开始遍历
     //要先找到最大的那个
     UserNode* User_Iter = Head->next;
     UserNode* num_max = NULL;
     while (User_Iter != NULL)                    //每个循环找出最大并标记
     {
         if (((User_Iter->str_phone_num) > (U_Print_Ctrl->str_phone_num)) )   //电话号码最大
         {
             U_Print_Ctrl = User_Iter;  //电话号码更大
         }
         User_Iter = User_Iter->next;
     }
     num_max = U_Print_Ctrl;
     while (!All_Printed())                           //先判断是否打印完，每次循环打印一个
     {
         U_Print_Ctrl = num_max;
         User_Iter = Head->next;
         while (User_Iter != NULL)                    //每个循环找出最小并标记
         {
             if (((User_Iter->str_phone_num) < (U_Print_Ctrl->str_phone_num ))&& !(User_Iter->b_is_printed))   //电话号码更小且未打印
             {
                 U_Print_Ctrl = User_Iter;  //找到要打印的元素，电话号码更小
             }
             User_Iter = User_Iter->next;
         }
         cout << left << setw(16) << U_Print_Ctrl->str_name << setw(17)                    //简略打印
             << U_Print_Ctrl->str_id << setw(11) << U_Print_Ctrl->str_phone_num << endl;
         U_Print_Ctrl->b_is_printed = true;                                                //标记打印过
     }
     system("pause");
 }

 void User::Clear_Print()
 {
     UserNode* Uprint_clearer = Head;
     if (NULL == Head->next)
     {
         cout << "通讯录为空，无需清理！ " << endl;
         system("pause");
         return;
     }
     Uprint_clearer = Uprint_clearer->next;  //第二个节点
     while (Uprint_clearer != NULL)
     {
         Uprint_clearer->b_is_printed = false;        //清空打印痕迹
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
         if (!(Uprint_Scan->b_is_printed) ) //有没打印的
         {
             return false;               //就没打印完
         }
         Uprint_Scan = Uprint_Scan->next;
     }
     return true;                        //否则全部打印
 }

 void User::Deal_Push()
 {
     if (str_push_phone.length() == 0) {
         cout << "无推送对象" << endl;
         system("pause");
         return;
     }
     else {
         cout << "可能认识的人为:" << str_push_phone << endl;
         system("pause");
         return;
     }

 }


 void User::SaveData(string user_phone)//保存单个用户的数据到文件
 {
     ofstream fout;
     string filename = user_phone + ".txt";
     fout.open(filename);//文件名
     if (!fout.is_open())
     {
         cout << filename << "open error";
         exit(1);
     }
     //打开成功
     fout << "name/id/phone_num/e_mail/academic/major/province/company/address/flag";//打印表头
     UserNode* temp = Head->next;
     if (temp)//若有用户则换行打印，避免读取出错
     {
         fout << endl;
     }
     while (temp)//有用户则打印用户信息，不同信息用/隔开
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
     fout.close();//关闭文件
 }


 void User::ReadData(string user_phone) //从单个文件里读取单个用户的数据
 {
     string filename = user_phone + ".txt";
     UserNode* temp = Head;
     char buf[50];//缓冲区存放读取的数据
     char tool[100];//吃掉表头无实际用处
     ifstream fin(filename);

     if (!fin.is_open())
     {
         cout << filename << "open error";
         exit(1);
     }

     //打开成功
     fin.getline(tool, 100);//读取表头

     while (!fin.eof())//没到文件末尾则读取一行数据
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
         string str = "1";//用来判断标志位是否为1
         fin.getline(buf, 50, '/');
         if (buf == str)//为1
         {
             temp->b_is_important = true;
         }
         else
         {
             temp->b_is_important = false;
         }
         fin.getline(buf, 50, '/');
         if (buf == str)//为1
         {
             temp->b_is_classmate = true;
         }
         else
         {
             temp->b_is_classmate = false;
         }
         fin.getline(buf, 50, '/');
         if (buf == str)//为1
         {
             temp->b_is_relative = true;
         }
         else
         {
             temp->b_is_relative = false;
         }
         fin.getline(buf, 50, '/');
         if (buf == str)//为1
         {
             temp->b_is_colleague = true;
         }
         else
         {
             temp->b_is_colleague = false;
         }
         fin.getline(buf, 50);
         if (buf == str)//为1
         {
             temp->b_in_blacklist = true;
         }
         else
         {
             temp->b_in_blacklist = false;
         }
     }
     fin.close();//关闭文件
 }


 void Read()//读取函数
 {
     User* temp = gl_User_Head;

     temp = temp->User_Next;
     while (temp)//若有用户则读取对应文件的信息
     {

         string phone_num = temp->Get_Phone_num();

         temp->ReadData(phone_num);

         temp = temp->User_Next;
     }

 }

 void Save()//保存函数
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



 void EnCode(string filename)//加密函数
 {
     fstream BeforeFile, AfterFile;
     string fileNameBefore = filename, fileNameAfter = "s_" + filename;
     //打开待加密文件					
     BeforeFile.open(fileNameBefore, ios::in | ios::binary);
     //打开加密后文件
     AfterFile.open(fileNameAfter, ios::out | ios::binary);

     BeforeFile.seekg(0, ios::end);//定位文件内容指针到末尾
     streamoff  size = BeforeFile.tellg();	//获取大小
     BeforeFile.seekg(0, ios::beg);//定位文件内容指针到文件头
     for (streamoff i = 0; i < size; i++) {
         //把BeforeFile的内容处理后放入AfterFile中
         AfterFile.put(BeforeFile.get() ^ 0x88);//加密或解密编码  0x88 
     }

     //关闭文件
     BeforeFile.close();
     AfterFile.close();
     cout << "加密或解密成功" << endl;
     const char* savePath = filename.c_str();
     if (remove(savePath) == 0)//删除原文件
     {
         cout << "删除原文件成功" << endl;
         system("Pause");
     }
     else
     {
         cout << "删除原文件失败" << endl;
         system("Pause");
     }
 }

 UserNode* User::SearchUser_node_black(IN_PARAM string first)
 {
     UserNode* temp = Head;
     UserNode* Find_more = Head->next;
     if (temp->next == NULL) {
         cout << "查无此人" << endl;
         system("pause");
         return NULL;
     }
     temp = temp->next;//从第二个节点开始遍历
     while (temp != NULL)
     {
         if (first == temp->str_name&&temp->b_in_blacklist==true)
         {
             Find_more = temp->next;
             int is_print = 0;//检测是否打印表头
             while (Find_more != NULL) {
                 if (first == Find_more->str_name&&Find_more->b_in_blacklist==true) {
                     if (0 == is_print) {
                         cout << "存在同名，打印其他人的信息，默认操作第一个成员详细信息，若非您目标，请输入手机号精确查找" << endl;
                         cout << endl;
                         cout << "名字            id               电话    " << endl;
                     }
                     if (false == Find_more->b_in_blacklist)
                         cout << left << setw(16) << Find_more->str_name << setw(17) <<
                         Find_more->str_id << setw(11) << Find_more->str_phone_num << endl;
                     is_print++;
                 }
                 Find_more = Find_more->next;
             }
             cout << "-----------------------------------以下是详细信息------------------------------------------" << endl;
             return temp;
         }
         if (first == temp->str_phone_num&&temp->b_in_blacklist==true)
         {
             return temp;
         }
         temp = temp->next;
     }
     cout << "查无此人" << endl;
     system("pause");
     return NULL;
 }