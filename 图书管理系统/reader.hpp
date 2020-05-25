//
//  reader.hpp
//  图书管理系统
//
//  Created by cdj990918 on 2020/5/24.
//  Copyright © 2020 cdj990918. All rights reserved.
//

#ifndef reader_hpp
#define reader_hpp

#include <stdio.h>

#endif /* reader_hpp */

void reader_window();

struct borrow_book
{
    char name [20];
    char writer[20];
    char borrow_time[20];
    char the_day_need_return[20];
};

struct reader
{
    char account[20];
    char name[20];
    char sex[2];
    char password[30];
    char login_date [20];
    vector<borrow_book>personal_lib;
};

vector<reader>readers;

void check_reader_account(reader & x)
{
    char temp [20];
    cin>>temp;
    for(int i =0 ;i<readers.size();i++)
        if(strcmp(readers[i].account, temp)==0)
        {
            cout<<"输入账号重复，请重新输入"<<endl;
            memset(temp, 0, sizeof(temp));
            cin>>temp;
            i=0;
        }
    strcpy(x.account, temp);
}


void reader_regis()
{
    cout<<"***************欢迎进入读者录入界面*****************"<<endl;
    reader r;
    ofstream OpenFile;
    OpenFile.open("reader.txt",ios::app);
    if(OpenFile.fail())
    {
        cout<<"打开文件错误";
        exit(0);
    }
    cout<<"请输入读者姓名"<<endl;
    cin>>r.name;
    cout<<"请输入读者号"<<endl;
    check_reader_account(r);
    cout<<"请输入密码"<<endl;
    char pa1[30],pa2[30];
    cin>>pa1;
    cout<<"请再次输入密码"<<endl;
    cin>>pa2;
    while(strcmp(pa1, pa2)!=0)
    {
        cout<<"两次输入密码不一致，请重新输入密码"<<endl;
        memset(pa1, 0, sizeof(pa1));
        memset(pa2,0,sizeof(pa2));
        cin>>pa1;
        cout<<"请再次输入密码"<<endl;
        cin>>pa2;
    }
    strcpy(r.password,pa1);
    cout<<"请输入读者性别(M代表男F代表女)"<<endl;
    cin>>r.sex;
    cout<<"请输入读者注册时间"<<endl;
    cin>>r.login_date;
    cout<<"读者 "<<r.name<<" 注册成功"<<endl;
    OpenFile<<r.name<<" "<<r.account<<" "<<r.password<<" "<<r.sex<<" "<<r.login_date<<endl;
    OpenFile.close();
    cout<<"输入R返回上级菜单 ";
    char temp;
    cin>>temp;
    readers.push_back(r);
    if(temp=='R')
        reader_window();
}

void alter_database_reader()
{
    ofstream OpenFile;
    OpenFile.open("reader.txt",ios::trunc);
    if(OpenFile.fail())
    {
        cout<<"打开文件错误";
        exit(0);
    }
    OpenFile<<"";
    OpenFile.close();
    OpenFile.open("reader.txt",ios::app);
    for(reader r : readers)
        OpenFile<<r.name<<" "<<r.account<<" "<<r.password<<" "<<r.sex<<" "<<r.login_date<<endl;
    OpenFile.close();
}
void delete_reader()
{
    cout<<"请输入将要删除的读者账号"<<endl;
    char account [20];
    cin>>account;
    int i;
    for(i =0;i<readers.size();i++)
    {
        if(strcmp(readers[i].account, account)==0)
        {
            cout<<"读者姓名:"<<readers[i].name<<" 读者账号:"<<readers[i].account<<endl;
            break;
        }
        
    }
    if(i == admin.size())
    {
        cout<<"输入错误，未找到该读者，输入Y继续操作，输入R返回上级菜单"<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
            delete_reader();
        else
            reader_window();
    }
    else
    {
        cout<<"是否删除该读者，输入Y确认删除"<<endl;
        char temp;
        cin>>temp;
        if(temp=='Y')
        {
            cout<<"删除读者"<<readers[i].name<<"成功"<<endl;
            readers.erase(readers.begin()+i);
            alter_database_reader();
            reader_window();
        }
        else
            reader_window();
    }
}

void check_readerInfo()
{
    cout<<"请输入要查询的读者账号"<<endl;
    char account[20];
    cin>>account;
    int i;
    for(i =0;i<readers.size();i++)
    {
        if(strcmp(readers[i].account, account)==0)
        {
            cout<<"姓名:"<<readers[i].name<<" 读者账号:"<<readers[i].account<<" 性别:"<<readers[i].sex<<
            " 注册时间"<<readers[i].login_date<<" 是否借书:";
            if(readers[i].personal_lib.empty())
                cout<<"否"<<endl;
            else
                cout<<"是"<<endl;
            
            break;
        }
        
    }
    if(i == admin.size())
    {
        cout<<"输入错误，未找到该读者，输入Y继续操作，输入R返回上级菜单"<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
            check_readerInfo();
        else
            reader_window();
    }
}
void alter_reader_info()
{
    cout<<"请输入需要修改密码的读者账号"<<endl;
    char account[20];
    cin>>account;
    int i;
    for(i =0;i<readers.size();i++)
    {
        if(strcmp(readers[i].account, account)==0)
        {
            break;
        }
        
    }
    if(i == admin.size())
    {
        cout<<"输入错误，未找到该读者，输入Y继续操作，输入R返回上级菜单"<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
            alter_reader_info();
        else
            reader_window();
    }
    else{
        cout<<"您将修改读者"<<readers[i].name<<"的密码,输入Y确认,输入其他键返回上级菜单"<<endl;
        char temp ;
        cin>>temp;
        getchar();
        if(temp=='Y')
        {
            cout<<"请输入读者新密码"<<endl;
            char passworld[20];
            cin>>passworld;
            memset(readers[i].password, 0, sizeof(admin[i].password));
            strcpy(readers[i].password, passworld);
            cout<<"修改读者密码成功"<<endl;
            alter_database_reader();
            reader_window();
        }
        else
            reader_window();
    }
    
    
}


void reader_window()
{
    cout<<"******************欢迎进入读者管理系统********************"<<endl;
    cout<<"********                                     *********"<<endl;
    cout<<"********          输入A以录入新的读者           ********"<<endl;
    cout<<"********          输入B以删除读者信息          ********"<<endl;
    cout<<"********          输入C以修改读者密码         ********"<<endl;
    cout<<"********           输入D查看读者信息         ********"<<endl;
    cout<<"********           输入R返回上级菜单        ********"<<endl;
    cout<<"********                                ********"<<endl;
    cout<<"************************************************"<<endl;
    cout<<"请输入：";
    char choice ;
    cin>>choice;
    if(choice=='A')
    {
        reader_regis();
    }
    else if (choice=='B')
    {
        delete_reader();
    }
    else if(choice == 'C')
    {
        alter_reader_info();
    }
    else if(choice== 'D')
    {
        check_readerInfo();
    }
    
}
