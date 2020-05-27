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
void borrow_book_windows(int x,int status);
void reader_self_log_Windows();


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
    if(i == readers.size())
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
void borrow_book_success(int x ,int m,int status)//x为reader 序号 ，m为图书序号
{
    cout<<"请输入借书密码"<<endl;
       char password[20];
       cin>>password;
    if(strcmp(password, readers[x].password)==0)
       {
           books[m].status=1;
             borrow_book bob;
             strcpy(bob.theAccount_reader, readers[x].account);
             bob.theID_book=books[m].id;
             cout<<"请输入借书日期"<<endl;
             cin>>bob.borrow_time;
             cout<<"请输入还书日期"<<endl;
             cin>>bob.the_day_need_return;
             readers[x].personal_lib.push_back(bob);
             insert_borrowBook(bob);
             alter_database_book();
       }
  else
  {
      cout<<"密码输入错误，重新输入按Y，退出按R"<<endl;
      char choice;
      cin>>choice;
      if(choice=='Y')
          borrow_book_success(x,m,status);
      else
        {
            if(status==1)
                                   reader_window();
                                   else
                                       reader_self_log_Windows();
        }
  }
}

void search_book_byname_reader(char * name,char * writer,int x,int status)
{
    int count=0;
    for(int i =0;i<books.size();i++)
    {
        if(strcmp(books[i].name, name)==0&&strcmp(books[i].writer, writer)==0)
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
        cout<<"未找到该图书，输入Y重新输入，输入R返回上级菜单"<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
            borrow_book_windows(x,status);
        else
            reader_window();
    }
    else
    {
        cout<<"输入Y借书，输入R退出"<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
        {
            cout<<"请输入要借阅图书的编号:";
            int id ;
            cin>>id;
            int m = get_book_id(id);
            if(m!=-1)
            {
                if(books[m].status==1)
                {
                    cout<<"这本图书已经借出，请重新挑选一本图书"<<endl;
                    search_book_byname_reader(name,writer,x,status);
                }
                else
                {
                    borrow_book_success(x, m,status);
                    cout<<"恭喜，借书成功!!"<<endl;
                    cout<<"输入Y继续借书，输入R返回上层菜单: ";
                    char choice ;
                    cin>>choice;
                    if(choice == 'Y')
                        borrow_book_windows(x,status);
                    else
                    {
                        if(status==1)
                        reader_window();
                        else
                            reader_self_log_Windows();
                    }
                       
                }
                
            }
            else
            {
                cout<<"输入错误"<<endl;
                if(status==1)
                                       reader_window();
                                       else
                                           reader_self_log_Windows();
              
            }
        }
        else
           {
               if(status==1)
                                      reader_window();
                                      else
                                          reader_self_log_Windows();
           }
    }
}

void borrow_book_windows(int x,int status)
{
        cout<<"请输入要借阅图书的名称：";
        char name[20];
        cin>>name;
        cout<<"请输入要借阅图书作者的姓名：";
        char writer[20];
        cin>>writer;
        search_book_byname_reader(name, writer, x,status);
}


void check_readerInfo(int status)
{
    cout<<"*******************欢迎进入读者借书系统界面*****************"<<endl;
    cout<<"请输入要借阅图书的读者账号: ";
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
    if(i == readers.size())
    {
        cout<<"输入错误，未找到该读者，输入Y继续操作，输入R返回上级菜单"<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
            check_readerInfo(status);
        else
        {
            if(status==1)
            reader_window();
            else
                reader_self_log_Windows();
        }
    }
    else
    {
        cout<<"输入Y进行借书,输入R返回上级菜单"<<endl;
        char choice;
        cin>>choice;
        if(choice == 'Y')
        {
            borrow_book_windows(i,status);
        }
        else
        {
            if(status==1)
                       reader_window();
                       else
                           reader_self_log_Windows();
            }
        
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
    if(i == readers.size())
    {
        cout<<"输入错误，未找到该读者，输入Y继续操作，输入R返回上级菜单 "<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
            alter_reader_info();
        else
            reader_window();
    }
    else{
        cout<<"您将修改读者"<<readers[i].name<<"的密码,输入Y确认,输入其他键返回上级菜单 "<<endl;
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

int get_reader(char *account)
{
    for(int i =0;i<readers.size();i++)
    {
        if(strcmp(account, readers[i].account)==0)
            return i;
    }
    return -1;
}

int get_per_lib_pos(int x,int id)
{
    for(int i =0;i<readers[x].personal_lib.size();i++)
    {
        if(readers[x].personal_lib[i].theID_book==id)
            return i;
    }
    return -1;
}
void return_book(int x)
{
    cout<<"输入要还的图书编号"<<endl;
    int book_id ;
    cin>>book_id;
    int temp=get_per_lib_pos(x, book_id);
    if(temp!=-1)
    {
        int m = get_book_id(book_id);
        books[m].status = 0 ;
        alter_database_book();
        remove_borrowbook(book_id);
        alter_borrorBook_database();
        readers[x].personal_lib.erase(readers[x].personal_lib.begin()+temp);
        cout<<"还书成功！"<<endl;
        cout<<"继续还书请输入Y，返回请输入R: ";
        char choice;
        cin>>choice;
        if(choice == 'Y')
            return_book(x);
        else
            reader_window();
        
    }
    else
    {
        cout<<"输入错误!!输入Y继续还书，R返回上级菜单: "<<endl;
        char choice ;
        cin>>choice ;
        if(choice=='Y')
            return_book(x);
        else
            reader_window();
        
    }
    
}


void checkup_reader_borrow()
{
    cout<<"请输入要查询读者的账号"<<endl;
    char account[20];
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
    if(i == readers.size())
    {
        cout<<"输入错误，未找到该读者，输入Y继续操作，输入R返回上级菜单 "<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
            checkup_reader_borrow();
        else
            reader_window();
    }
    else
    {
        if(readers[i].personal_lib.empty())
        {
            cout<<"读者"<<readers[i].name<<"未借任何图书"<<endl;
            char choice;
            cout<<"输入Y继续查询其他读者，输入R返回上级菜单 ";
            cin>>choice;
            if(choice=='Y')
                checkup_reader_borrow();
            else
                reader_window();
        }
        else
        {
           
            for(int j =0;j<readers[i].personal_lib.size();j++)
            {
                int book_id = readers[i].personal_lib[j].theID_book;
                if(j==0)
                cout<<"借阅图书编号"<<"    "<<"借阅图书名"<<"    "<<"图书作者"<<" "<<"借阅还书日期"<<" "<<"规定还书日期"<<endl;
                cout<<"    "<<book_id<<"   "<<books[get_book_id(book_id)].name<<" "<<books[get_book_id(book_id)].writer<<" "<<
                readers[i].personal_lib[j].borrow_time<<" "<<readers[i].personal_lib[j].the_day_need_return<<endl;
            }
            cout<<"输入Y进行还书，输入R返回上级菜单 "<<endl;
            char choice;
            cin>>choice ;
            if(choice == 'Y')
            {
               return_book(i);
            }
            else
                reader_window();
                
        }
        
    }
}

void reader_window()
{
    cout<<"******************欢迎进入读者管理系统********************"<<endl;
    cout<<endl;
    cout<<"                  输入A以录入新的读者                 "<<endl;
    cout<<"                  输入B以删除读者信息                 "<<endl;
    cout<<"                  输入C以修改读者密码                 "<<endl;
    cout<<"                  输入D进入读者借书系统                 "<<endl;
    cout<<"              输入E查看读者所借书目信息(还书)           "<<endl;
    cout<<"                    输入R返回上级菜单                  "<<endl;
    cout<<endl;
    cout<<"*****************************************************"<<endl;
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
        check_readerInfo(1);
    }
    else if(choice=='E')
    {
        checkup_reader_borrow();
    }
    
}

void reader_self_log_Windows()
{
    cout<<"******************欢迎进入读者登陆界面********************"<<endl;
    cout<<endl;
    cout<<"                  输入A查看馆藏图书"<<endl;
    cout<<"                    输入B进行借书"<<endl;
    cout<<"                      输入R返回"<<endl;
    cout<<endl;
    cout<<"*****************************************************"<<endl;
       cout<<"请输入：";
       char choice ;
       cin>>choice;
       if(choice=='A')
       {
         checkoutAllBooks(0);
       }
       else if (choice=='B')
       {
           check_readerInfo(0);
       }

}
