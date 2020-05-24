//
//  books.hpp
//  图书管理系统
//
//  Created by cdj990918 on 2020/5/24.
//  Copyright © 2020 cdj990918. All rights reserved.
//

#ifndef books_hpp
#define books_hpp

#include <stdio.h>

#endif /* books_hpp */
void check_book_windows();

struct book
{
    char id [6];
    char  name[20];
    char writer[20];
    char theDayJoinLibary [20];
    int status = 0;//status = 1 表示已经借出去
};

vector<book>books;

void check_book_id(book & x)
{
    char temp [20];
    cin>>temp;
    for(book b:books)
        if(strcmp(b.id, temp)==0)
        {
            cout<<"输入图书编号重复，请重新输入"<<endl;
            memset(temp, 0, sizeof(temp));
            cin>>temp;
        }
    strcpy(x.id, temp);
}


void book_insert()
{
    cout<<"输入Y进行图书添加，输入R返回上级菜单"<<endl;
    char choice;
    cin>>choice;
    if(choice == 'Y')
    {
        book b ;
        cout<<"请输入5位图书编号"<<endl;
        check_book_id(b);
        cout<<"请输入书名"<<endl;
        cin>>b.name;
        cout<<"请输入作者"<<endl;
        cin>>b.writer;
        cout<<"请输入入馆时间"<<endl;
        cin>>b.theDayJoinLibary;
        books.push_back(b);
        ofstream Openfile;
        Openfile.open("book.txt",ios::app);
        if(Openfile.ios_base::fail())
        {
            cout<<"打开文件失败"<<endl;
            exit(0);
        }
        Openfile<<b.id<<" "<<b.name<<" "<<b.writer<<" "<<b.theDayJoinLibary<<endl;
        Openfile.close();
    }
    else
        check_book_windows();
}


void check_book_windows()
{
    cout<<"**************欢迎进入图书管理界面********************"<<endl;
    cout<<"***********                          *************"<<endl;
    cout<<"***********    输入A进行图书查询        *************"<<endl;
    cout<<"***********    输入B进行图书添加        *************"<<endl;
    cout<<"***********    输入C进行图书注销        *************"<<endl;
    cout<<"***********                          *************"<<endl;
    cout<<"**************************************************"<<endl;
    cout<<"请输入 ";
    char choice;
    cin>>choice;
    if(choice=='B')
        book_insert();
}
