//
//  admin.hpp
//  图书管理系统
//
//  Created by cdj990918 on 2020/5/24.
//  Copyright © 2020 cdj990918. All rights reserved.
//

#ifndef admin_hpp
#define admin_hpp

#include <stdio.h>


#endif /* admin_hpp */
void admin_log();
void admin_loggin_windows(int i);

int cur_id;

void admin_windows()
{
    cout<<"***************欢迎进入管理员登陆界面*******************"<<endl;
    cout<<"***********                             ************"<<endl;
    cout<<"***********          输入Y登陆           ************"<<endl;
    cout<<"***********          输入R返回           ************"<<endl;
    cout<<"***********                            ************"<<endl;
    cout<<"***************************************************"<<endl;
    cout<<"请输入：";
    char choice;
    cin>>choice;
    if(choice == 'Y')
    {
        admin_log();
        getchar();
    }
    else
        return;
}

void admin_loggin_windows(int i)
{
    cout<<"欢迎您,管理员"<<admin[i].name<<endl;
    cout<<"*******************************************************"<<endl;
    cout<<"******               输入A以进行书库维护            ******"<<endl;
    cout<<"******               输入B以进行读者维护            ******"<<endl;
    cout<<"******                  输入0退出                 ******"<<endl;
    cout<<"*******************************************************"<<endl;
    cout<<"请输入：";
    char choice ;
    cin>>choice;
    getchar();
    if(choice == 'A')
        check_book_windows();
    if(choice == 'B')
        reader_window();
}


int get_curadmin_id()
{
    return cur_id;
}

void admin_log()
{
    cout<<"***************欢迎进入管理员登陆界面*****************"<<endl;
    cout<<"请输入管理员账号"<<endl;
    char account [30];
    cin>>account;
    getchar();
    int i ;
    for(i=0;i<admin.size();i++)
        if(strcmp(admin[i].account, account)==0)
            break;
    if(i==admin.size())
    {
        cout<<"管理员账号不存在"<<endl;
        admin_windows();
    }
    else
    {
        cout<<"请输入管理员密码"<<endl;
        char password [20];
        cin>>password;
        getchar();
        while (strcmp(admin[i].password, password)!=0) {
            cout<<"输入密码错误，请重新输入！(输入R退出)"<<endl;
            memset(password, 0, sizeof(password));
            cin>>password;
            getchar();
            if(password[0]=='R')
                admin_windows();
        }
        cur_id=i;
        admin_loggin_windows(i);
    }
}
