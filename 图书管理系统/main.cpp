//
//  main.cpp
//  图书管理系统
//
//  Created by cdj990918 on 2020/5/22.
//  Copyright © 2020 cdj990918. All rights reserved.
//


#include <iostream>
#include<fstream>
#include<vector>
#include"super_admin.hpp"
#include"books.hpp"
#include"reader.hpp"
#include"admin.hpp"
using namespace std;





void windows()
{
    char choice='1';
    while (choice!='0') {
        cout<<"****************欢迎进入图书管理系统*******************"<<endl;
        cout<<"***********                           *************"<<endl;
        cout<<"***********                           *************"<<endl;
        cout<<"***********     输入Y进行管理员登陆       *************"<<endl;
        cout<<"***********   输入S进行超级管理员登陆     *************"<<endl;
        cout<<"***********       输入0退出系统         *************"<<endl;
        cout<<"***********                           *************"<<endl;
        cout<<"***********                           *************"<<endl;
        cout<<"***************************************************"<<endl;
        cout<<"请输入: ";
        cin>>choice;
        getchar();
        if(choice == 'Y')
            admin_windows();
        else if(choice == 'S')
            super_admin_windows();
    }
    
}


void init_database()
{
    ifstream file("admin.txt");
    string s;
    while (getline(file,s)) {
        Administrator a ;
        sscanf(&s[0],"%s%s%s%s",a.name,a.account,a.password,a.email);
        admin.push_back(a);
    }
    file.close();
    ifstream bookfile("book.txt");
    while (getline(bookfile,s)) {
        book b;
        sscanf(&s[0],"%d%s%s%d%d",&b.id,b.name,b.writer,&b.cur_amount,&b.status);
           books.push_back(b);
       }
    bookfile.close();
    ifstream readerfile("reader.txt");
    while (getline(readerfile,s)) {
        reader r;
        sscanf(&s[0],"%s%s%s%s%s",r.name,r.account,r.password,r.sex,r.login_date);
           readers.push_back(r);
       }
    readerfile.close();
}
int main(int argc, const char * argv[]) {
    init_database();
    init_super_admin();
    windows();
    
    
}
