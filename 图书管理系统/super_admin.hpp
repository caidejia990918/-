//
//  super_admin.hpp
//  图书管理系统
//
//  Created by cdj990918 on 2020/5/24.
//  Copyright © 2020 cdj990918. All rights reserved.
//

#ifndef super_admin_hpp
#define super_admin_hpp

#include<iostream>
#include<vector>
using namespace std;

#endif /* super_admin_hpp */
struct Administrator
{
    char name [20];
    char account [20];
    char password [30];
    char email [20];
};

struct Super_Administrator
{
    char name[20];
    char account[20];
    char password[30];
}Sup_admin[2];

vector<Administrator>admin;

void super_admin_windows();
void admin_regis(int a);
void init_super_admin();
void Sup_admin_log();
void CheckOutAllAdmin(int a);
void check_admin_byname(int x);
void alter_database();
void admin_delete(int x);

void Sup_admin_login_windows(int a)
{
    cout<<"*******************欢迎您"<<Sup_admin[a].name<<"***********************"<<endl;
    cout<<"******              输入A以查看所有管理员             ******"<<endl;
    cout<<"******           输入B以通过管理员姓名进行查找         ******"<<endl;
    cout<<"******              输入C以进行新的管理员录入         ******"<<endl;
    cout<<"******               输入D以删除管理员              ******"<<endl;
    cout<<"******                  输入0退出                 ******"<<endl;
    cout<<"*******************************************************"<<endl;
    cout<<"请输入：";
    char choice ;
    cin>>choice;
    getchar();
    if(choice == 'A')
    {
        CheckOutAllAdmin(a);
    }
    else if(choice== 'B')
    {
        check_admin_byname(a);
    }
    else if(choice == 'C')
    {
        admin_regis(a);
    }
    else if(choice=='D')
    {
        admin_delete(a);
    }
    else
        return ;
}

void super_admin_windows()
{
    cout<<"***************欢迎进入超级管理员登陆界面*****************"<<endl;
    cout<<"***********                               ***********"<<endl;
    cout<<"******                输入Y登陆                 *******"<<endl;
    cout<<"***********           输入R返回          **************"<<endl;
    cout<<"***********                            ***************"<<endl;
    cout<<"******************************************************"<<endl;
    cout<<"请输入: ";
    char choice;
    cin>>choice;
    getchar();
    if(choice == 'Y')
        Sup_admin_log();
}

void Sup_admin_log()
{
    cout<<"***************欢迎进入超级管理员登陆界面*****************"<<endl;
    cout<<"请输入超级管理员账号 "<<endl;
    char account[20];
    cin>>account;
    getchar();
    if(strcmp(account, Sup_admin[0].account)==0)
    {
        cout<<"请输入登录密码"<<endl;
        char password[20];
        cin>>password;
        getchar();
        while (strcmp(password, Sup_admin[0].password)!=0) {
            cout<<"输入密码错误，请重新输入"<<endl;
            memset(password, 0, sizeof(password));
            cin>>password;
            getchar();
        }
        Sup_admin_login_windows(0);
    }
    else if(strcmp(account, Sup_admin[1].account)==0)
    {
        cout<<"请输入登录密码"<<endl;
        char password[20];
        cin>>password;
        getchar();
        while (strcmp(password, Sup_admin[1].password)!=0) {
            cout<<"输入密码错误，请重新输入"<<endl;
            memset(password, 0, sizeof(password));
            cin>>password;
            getchar();
        }
        Sup_admin_login_windows(1);
    }
    else
    {
        cout<<"输入错误!"<<endl;
        super_admin_windows();
    }
    
}

void init_super_admin()
{
    strcpy(Sup_admin[0].name, "超级管理员1");
    strcpy(Sup_admin[0].account, "a123456");
    strcpy(Sup_admin[0].password, "a123456");
    strcpy(Sup_admin[1].name, "超级管理员2");
    strcpy(Sup_admin[1].account, "b123456");
    strcpy(Sup_admin[1].password, "b123456");
}
void check_same_account(Administrator & x)
{
    char temp [20];
    cin>>temp;
    getchar();
    for(Administrator a:admin)
        if(strcmp(a.account, temp)==0)
        {
            cout<<"输入账号重复，请重新输入"<<endl;
            memset(temp, 0, sizeof(temp));
            cin>>temp;
            getchar();
        }
    strcpy(x.account, temp);
}

void CheckOutAllAdmin(int a)
{
    for(Administrator a : admin)
        cout<<"姓名:"<<a.name<<" 账号:"<<a.account<<" 密码:"<<a.password<<" 绑定邮箱:"<<a.email<<endl;
    cout<<"输入R返回上级菜单 ";
    char temp;
    cin>>temp;
    getchar();
    if(temp=='R')
        Sup_admin_login_windows(a);
}

void admin_regis(int x)
{
    cout<<"***************欢迎进入管理员录入界面*****************"<<endl;
    Administrator a;
    ofstream OpenFile;
    OpenFile.open("admin.txt",ios::app);
    if(OpenFile.fail())
    {
        cout<<"打开文件错误";
        exit(0);
    }
    cout<<"请输入管理员姓名"<<endl;
    cin>>a.name;
    getchar();
    cout<<"请输入账号"<<endl;
    check_same_account(a);
    cout<<"请输入密码"<<endl;
    char pa1[30],pa2[30];
    cin>>pa1;
    getchar();
    cout<<"请再次输入密码"<<endl;
    cin>>pa2;
    getchar();
    while(strcmp(pa1, pa2)!=0)
    {
        cout<<"两次输入密码不一致，请重新输入密码"<<endl;
        memset(pa1, 0, sizeof(pa1));
        memset(pa2,0,sizeof(pa2));
        cin>>pa1;
        getchar();
        cout<<"请再次输入密码"<<endl;
        cin>>pa2;
        getchar();
    }
    strcpy(a.password,pa1);
    cout<<"请输入邮箱(找回密码是使用)"<<endl;
    cin>>a.email;
    cout<<"管理员 "<<a.name<<" 注册成功"<<endl;
    OpenFile<<a.name<<" "<<a.account<<" "<<a.password<<" "<<a.email<<endl;
    OpenFile.close();
    cout<<"输入R返回上级菜单 ";
    char temp;
    cin>>temp;
    getchar();
    if(temp=='R')
    Sup_admin_login_windows(x);
}

void alter_adminInfo(int i,int x)
 {
     cout<<"*************************************************"<<endl;
     cout<<"***********    输入A修改管理员密码       ***********"<<endl;
     cout<<"***********   输入B修改管理员绑定邮箱    ***********"<<endl;
     cout<<"***********        输入0退出          ***********"<<endl;
     cout<<"*************************************************"<<endl;
     char choice ;
     cin>>choice;
     getchar();
     if(choice == 'A')
     {
         cout<<"您将修改管理员"<<admin[i].name<<"的密码,输入Y确认,输入其他键返回上级菜单"<<endl;
         char temp ;
         cin>>temp;
         getchar();
         if(temp=='Y')
         {
             cout<<"请输入新的管理员绑定邮箱,并重邮箱中确认此操作"<<endl;
             char email [20];
             cin>>email;
             getchar();
             if(strcmp(email, admin[i].email)==0)
             {
                 cout<<"请输入管理员新密码"<<endl;
                 char passworld[20];
                 cin>>passworld;
                 getchar();
                 memset(admin[i].password, 0, sizeof(admin[i].password));
                 strcpy(admin[i].password, passworld);
                 cout<<"修改管理员密码成功"<<endl;
                 alter_database();
                 Sup_admin_login_windows(x);
             }
             else
             {
                 cout<<"输入绑定邮箱错误错误!"<<endl;
                 alter_adminInfo(i,x);
             }
             
         }
         
     }
    else if(choice =='B')
    {
        cout<<"您将修改管理员"<<admin[i].name<<"的邮箱,输入Y确认,输入其他键返回上级菜单"<<endl;
        cout<<"请输入要修改的新邮箱，并在原邮箱中确认更改"<<endl;
        char email[20];
        cin>>email;
        getchar();
        memset(admin[i].email, 0, sizeof(admin[i].email));
        strcpy(admin[i].email, email);
        alter_database();
        Sup_admin_login_windows(x);
    }
     else
     {
         Sup_admin_login_windows(x);
     }
         
     
}
void check_admin_byname(int x)
{
    cout<<"请输入管理员姓名"<<endl;
    char name[20];
    cin>>name;
    getchar();
    int i;
    for(i =0;i<admin.size();i++)
    {
        if(strcmp(admin[i].name, name)==0)
        {
            cout<<"姓名:"<<admin[i].name<<" 账号:"<<admin[i].account<<" 密码:"<<admin[i].password<<" 绑定邮箱:"<<admin[i].email<<endl;
            break;
        }
            
    }
    if(i == admin.size())
    {
        cout<<"输入错误，未找到该管理员"<<endl;
        Sup_admin_login_windows(x);
    }
    else
    {
        cout<<"输入C修改管理员信息,R返回上级菜单"<<endl;
        char choice;
        cin>>choice;
        getchar();
        if(choice == 'C')
            alter_adminInfo(i,x);
        else
            Sup_admin_login_windows(x);
        
    }
    
    
}

void admin_delete(int x)
{
    cout<<"请输入将要删除的管理员姓名"<<endl;
    char name [20];
    cin>>name;
    getchar();
    int i;
    for(i =0;i<admin.size();i++)
    {
        if(strcmp(admin[i].name, name)==0)
        {
            cout<<"姓名:"<<admin[i].name<<" 账号:"<<admin[i].account<<" 密码:"<<admin[i].password<<" 绑定邮箱:"<<admin[i].email<<endl;
            break;
        }
            
    }
    if(i == admin.size())
    {
        cout<<"输入错误，未找到该管理员"<<endl;
        Sup_admin_login_windows(x);
    }
    else
    {
        cout<<"是否删除该管理员，输入Y确认删除"<<endl;
        char temp;
        cin>>temp;
        getchar();
        if(temp=='Y')
        {
            cout<<"删除管理员"<<admin[i].name<<"成功"<<endl;
            admin.erase(admin.begin()+i);
            alter_database();
            
        }
    }
}

void alter_database()
{
    ofstream OpenFile;
    OpenFile.open("admin.txt",ios::trunc);
    if(OpenFile.fail())
    {
        cout<<"打开文件错误";
        exit(0);
    }
    OpenFile<<"";
    OpenFile.close();
    OpenFile.open("admin.txt",ios::app);
    for(Administrator a : admin)
         OpenFile<<a.name<<" "<<a.account<<" "<<a.password<<" "<<a.email<<endl;
    OpenFile.close();
    
}
