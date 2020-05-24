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
        
    }
    else if(choice == 'C')
    {
        admin_regis(a);
    }
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
    Sup_admin_login_windows(x);
}
