//
//  book_borrow_info.hpp
//  图书管理系统
//
//  Created by cdj990918 on 2020/5/25.
//  Copyright © 2020 cdj990918. All rights reserved.
//

#ifndef book_borrow_info_hpp
#define book_borrow_info_hpp

#include <stdio.h>


#endif /* book_borrow_info_hpp */



struct borrow_book
{
    char theAccount_reader [20];
    int theID_book ;
    char borrow_time[20];
    char the_day_need_return[20];
};

vector<borrow_book>borr_books;

void insert_borrowBook(borrow_book b)
{
    borr_books.push_back(b);
    ofstream file;
    file.open("BorrowBook.txt",ios::app);
    file<<b.theAccount_reader<<" "<<b.theID_book<<" "<<b.borrow_time<<" "<<b.the_day_need_return<<endl;
    file.close();
   
}
void alter_borrorBook_database()
{
       ofstream OpenFile;
       OpenFile.open("BorrowBook.txt",ios::trunc);
       if(OpenFile.fail())
       {
           cout<<"打开文件错误";
           exit(0);
       }
       OpenFile<<"";
       OpenFile.close();
       OpenFile.open("BorrowBook.txt",ios::app);
       for(borrow_book b : borr_books)
            OpenFile<<b.theAccount_reader<<" "<<b.theID_book<<" "<<b.borrow_time<<" "<<b.the_day_need_return<<endl;
       OpenFile.close();
}

void remove_borrowbook(int id)
{
    for(int i =0;i<borr_books.size();i++)
    {
        if(borr_books[i].theID_book==id)
        {
            borr_books.erase(borr_books.begin()+i);
            return;
        }
    }
}

int  search_borrow_book_id(int id)
{
    for(int i =0;i<borr_books.size();i++)
    {
        if(borr_books[i].theID_book==id)
        {
            return i;
        }
    }
    return -1;
}
