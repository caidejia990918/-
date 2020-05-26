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
void search_book_windows();
void admin_loggin_windows(int i);
int get_curadmin_id();
struct book
{
    int id;
    char  name[20];
    char writer[20];
    int cur_amount ;
    int status = 0;//status = 1 表示已经借出去
};

vector<book>books;

void add_book_id(book & x)
{
    int temp = (int)books.size()-1;
    if(temp != -1)
    {
        int cur_id = books[temp].id+1;
        x.id=cur_id;
    }
    else
        x.id=1;
}


void book_insert()
{
    cout<<"输入Y进行图书添加，输入R返回上级菜单 "<<endl;
    char choice;
    cin>>choice;
    if(choice == 'Y')
    {
        book b ;
        ofstream Openfile;
        Openfile.open("book.txt",ios::app);
        cout<<"请输入书名"<<endl;
        cin>>b.name;
        cout<<"请输入作者"<<endl;
        cin>>b.writer;
        cout<<"请输馆藏数量"<<endl;
        cin>>b.cur_amount;
        for(int i =0;i<b.cur_amount;i++)
        {
            add_book_id(b);
            books.push_back(b);
            if(Openfile.ios_base::fail())
            {
                cout<<"打开文件失败"<<endl;
                exit(0);
            }
            Openfile<<b.id<<" "<<b.name<<" "<<b.writer<<" "<<b.cur_amount<<" "<<b.status<<endl;
        }
        
        Openfile.close();
        cout<<"添加成功!输入Y继续添加，输入R返回上层菜单 "<<endl;
        char choice;
        cin>>choice;
        if(choice == 'Y')
            book_insert();
        else
            check_book_windows();
    }
    else
        check_book_windows();
}

void search_book_byname()
{
    char name [20];
    cout<<"请输入要查询的书籍名称"<<endl;
    cin>>name;
    int count=0;
    for(int i =0;i<books.size();i++)
    {
        if(strcmp(books[i].name, name)==0)
        {
            count++;
            if(count==1)
                cout<<"图书编号"<<"    "<<"图书名称"<<"        "<<"图书作者"<<"     "<<"是否可借"<<endl;
            cout<<"  "<<books[i].id<<"    "<<books[i].name<<"   "<<books[i].writer<<"    ";
            if(books[i].status==0)
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
    }
    if (count==0)
           {
               cout<<"未找到该图书，输入Y重新输入，输入R返回上级菜单 "<<endl;
               char choice;
               cin>>choice;
               if(choice=='Y')
                   search_book_byname();
               else
                   search_book_windows();
           }
           else
           {
               cout<<"输入Y继续，输入R返回上级菜单 ";
               char choice;
               cin>>choice;
               if(choice=='Y')
                   search_book_byname();
               else
                   search_book_windows();
           }
}
 
void search_book_byId()
{
    cout<<"请输入要查询的图书ID"<<endl;
    int id;
    cin>>id;
    int count =0;
    for(int i =0;i<books.size();i++)
       {
           if(books[i].id == id)
           {
               count++;
               if(count==1)
                   cout<<"图书编号"<<"    "<<"图书名称"<<"        "<<"图书作者"<<"     "<<"是否可借"<<endl;
               cout<<"  "<<books[i].id<<"    "<<books[i].name<<"   "<<books[i].writer<<"    ";
               if(books[i].status==0)
                   cout<<"Yes"<<endl;
               else
                   cout<<"No"<<endl;
               break;
           }
       }
       if (count==0)
              {
                  cout<<"未找到该图书，输入Y重新输入，输入R返回上级菜单 "<<endl;
                  char choice;
                  cin>>choice;
                  if(choice=='Y')
                      search_book_byname();
                  else
                      search_book_windows();
              }
              else
              {
                  cout<<"输入Y继续，输入R返回上级菜单 ";
                  char choice;
                  cin>>choice;
                  if(choice=='Y')
                      search_book_byId();
                  else
                      search_book_windows();
              }
}
void alter_book_amount(int i)
{
    char name [20];
    char writer [20];
    strcpy(name, books[i].name);
    strcpy(writer, books[i].writer);
    for(int j =0;j<books.size();j++)
        if((strcmp(books[j].name, name)==0)&&(strcmp(books[j].writer, writer)==0))
            books[j].cur_amount--;
}

void search_book_windows()
{
    cout<<"**************************************************"<<endl;
    cout<<endl;
    cout<<"                 输入A通过书名进行查询        "<<endl;
    cout<<"               输入B通过图书编号进行查询       "<<endl;
    cout<<"                     输入R返回              "<<endl;
    cout<<endl;
    cout<<"**************************************************"<<endl;
    cout<<"请输入 ";
    char choice;
    cin>>choice;
    if(choice == 'A')
        search_book_byname();
    else if (choice == 'B')
        search_book_byId();
    else
        check_book_windows();
}
void alter_database_book()
{
    ofstream OpenFile;
    OpenFile.open("book.txt",ios::trunc);
    if(OpenFile.fail())
    {
        cout<<"打开文件错误";
        exit(0);
    }
    OpenFile<<"";
    OpenFile.close();
    OpenFile.open("book.txt",ios::app);
    for(book b :books)
        OpenFile<<b.id<<" "<<b.name<<" "<<b.writer<<" "<<b.cur_amount<<" "<<b.status<<endl;
    OpenFile.close();
    
}
int get_book_id(int id)
{
    for(int i =0;i<books.size();i++)
    {
        if(books[i].id==id)
            return i;
    }
    return -1;
}
void delete_book()
{
    cout<<"按Y确认进行图书删除，按R返回上层菜单 "<<endl;
    char choice;
    cin>>choice;
    if(choice == 'Y')
    {
        cout<<"请输入要删除的图书ID"<<endl;
        int id;
        cin>>id;
        int count =0;
        int i;
          for(i =0;i<books.size();i++)
             {
                 if(books[i].id == id)
                 {
                     count++;
                     if(count==1)
                         cout<<"图书编号"<<"    "<<"图书名称"<<"        "<<"图书作者"<<"     "<<"是否可借"<<endl;
                     cout<<"  "<<books[i].id<<"    "<<books[i].name<<"   "<<books[i].writer<<"    ";
                     if(books[i].status==0)
                         cout<<"Yes"<<endl;
                     else
                         cout<<"No"<<endl;
                     break;
                 }
             }
        if (count==0)
        {
            cout<<"未找到该图书，输入Y重新输入，输入R返回上级菜单 "<<endl;
            char choice;
            cin>>choice;
            if(choice=='Y')
                delete_book();
            else
                check_book_windows();
            
        }
        else
        {
           cout<<"输入Y确定删除，R返回"<<endl;
                  char temp;
                  cin>>temp;
                  if(temp=='Y')
                  {
                      cout<<"删除图书成功后"<<endl;
                      alter_book_amount(i);
                      books.erase(books.begin()+i);
                      alter_database_book();
                      char temp1;
                      cout<<"输入Y继续删除图书，R返回上级菜单 "<<endl;
                      cin>>temp1;
                      if(temp1=='Y')
                          delete_book();
                      else
                          check_book_windows();
                  }
            else
                delete_book();
        }
       
        
    }
}

void checkoutAllBooks()
{
    for(int i =0;i<books.size();i++)
       {
               if(i==0)
                   cout<<"图书编号"<<"    "<<"图书名称"<<"        "<<"图书作者"<<"     "<<"是否可借"<<endl;
               cout<<"  "<<books[i].id<<"    "<<books[i].name<<"   "<<books[i].writer<<"    ";
               if(books[i].status==0)
                   cout<<"Yes"<<endl;
               else
                   cout<<"No"<<endl;
           }
    char choice;
    cout<<"输入任意见返回上级菜单:";
    cin>>choice;
    check_book_windows();
}
void check_book_windows()
{
    cout<<"****************欢迎进入图书管理界面*******************"<<endl;
    cout<<endl;
    cout<<"                输入A进行图书查询             "<<endl;
    cout<<"                输入B进行图书添加              "<<endl;
    cout<<"                输入C进行图书注销              "<<endl;
    cout<<"               输入D查看所有馆藏图书             "<<endl;
    cout<<"                   输入R返回                 "<<endl;
    cout<<endl;
    cout<<"***************************************************"<<endl;
    cout<<"请输入 ";
    char choice;
    cin>>choice;
    if(choice=='B')
        book_insert();
    else if (choice == 'A')
        search_book_windows();
    else if(choice == 'C')
        delete_book();
    else if(choice == 'D')
        checkoutAllBooks();
    else
        admin_loggin_windows(get_curadmin_id());
    
}
