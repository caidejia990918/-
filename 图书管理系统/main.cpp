//
//  main.cpp
//  图书管理系统
//
//  Created by cdj990918 on 2020/5/22.
//  Copyright © 2020 cdj990918. All rights reserved.
//

#include <iostream>
#include<fstream>
#include<time.h>
#include<vector>
#include"super_admin.hpp"
#include"books.hpp"
#include"book_borrow_info.hpp"
#include"reader.hpp"
#include"admin.hpp"
using namespace std;





void windows()
{
    char choice='1';
    while (choice!='0') {
        cout<<"*******************欢迎进入图书管理系统******************"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"                   输入Y进行管理员登陆                  "<<endl;
        cout<<"                  输入S进行超级管理员登陆               "<<endl;
        cout<<"                    输入R进行读者访问               "<<endl;
        cout<<"                     输入0退出系统                     "<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"*****************************************************"<<endl;
        cout<<"请输入: ";
        cin>>choice;
        getchar();
        if(choice == 'Y')
            admin_windows();
        else if(choice == 'S')
            super_admin_windows();
        else if(choice == 'R')
                   reader_self_log_Windows();
    }
    
}

void init_reader_borrowBook(borrow_book b)
{
    char account [20];
    strcpy(account, b.theAccount_reader);
    int m=get_reader(account);
    readers[m].personal_lib.push_back(b);
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
        sscanf(&s[0],"%s%s%s%s%s%s",r.name,r.account,r.password,r.sex,r.login_date,r.phoneNumber);
        readers.push_back(r);
    }
    readerfile.close();
    ifstream borrowBookfile("BorrowBook.txt");
    while (getline(borrowBookfile,s)) {
        borrow_book bob;
        sscanf(&s[0],"%s%d%s%s",bob.theAccount_reader,&bob.theID_book,bob.borrow_time,bob.the_day_need_return);
        borr_books.push_back(bob);
        init_reader_borrowBook(bob);
    }
    borrowBookfile.close();
}


void get_curr_time()
{
    char str[80];
    struct tm * cur_time;
    time_t it ;
    it = time(NULL);
    cur_time = localtime(&it);
    cout<<"当前时间为:";
    strftime(str, 100, "%F %T\n", cur_time);
    cout<<str;
}


int main(int argc, const char * argv[]) {
    init_database();
    init_super_admin();
    windows();

    get_curr_time();
}
