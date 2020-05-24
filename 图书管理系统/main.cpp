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
#include"admin.hpp"
using namespace std;





void windows()
{
    char choice='1';
    while (choice!='0') {
        cout<<"****************欢迎进入图书管理系统*******************"<<endl;
        cout<<"***********                           *************"<<endl;
        cout<<"***********                           *************"<<endl;
        cout<<"***********     输入Y进行管理员登陆      *************"<<endl;
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
    //    for(Administrator a : admin)
    //     cout<<a.name<<" "<<a.account<<" "<<a.password<<" "<<a.email<<endl;
}
int main(int argc, const char * argv[]) {
    init_database();
    init_super_admin();
    windows();
    
    
}
