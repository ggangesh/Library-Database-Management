#include<iostream>//to use standard input output commands like cin and cout
#include<cstdio>//to redirect the input output operations to stdin and stdout
#include<string>//to use the string class
#include<cstdlib>//for searching sorting converting random no generation and dynamic memory allocation
#include<ctime>//getting system and computer date and time
#include<cstring>//to use character and string manipulation functions in the library
#include<dos.h>
#include<cctype>//to use the tolower function
#include<vector>//to use the container vector for dynamic memory allocation
#include<string>//to use the string class
#include<windows.h>//to use colour in the terminal
#include<process.h>//to use exit function
#include<conio.h>//to use getch function
#include<climits>//to use INT_MAX value

#include"class.h"

using namespace std;

void admin::mini_statement(){
 cout<<"ID of administrator : "<<id<<" \n ";
 cout<<"Name of the administrator : "<<name<<" \n ";
}

int admin::book_edit(){//completed
 cout<<"Enter the REF_NO of the book to be modified \n";
 char* x;
 book* b;
 b = search_book(x);
 if(b==NULL){
    cout<<"The keyword is not found in the database !!\n";
    cout<<"Returning to the ADMIN Terminal #\n";
    return -1;
 }
 b->edit_book();
 b->status();
 save_book(b);
 cout<<"Returning to ADMIN Terminal #\n";
 return 1;
}

int admin::collect_book(){//completed
 cout<<"PATRON DETAILS SECURE CHECK \n";
 patron* p=password_patron();
 if(p==NULL){
    return -1;
 }
 p->return_book();
 p->mini_statement();
 save_patron(p);
 return 1;
}

int admin::issue_book(){//completed
 cout<<"PATRON DETAILS SECURE CHECK \n";
 patron* p=password_patron();
 if(p==NULL){
    return -1;
 }
 cout<<"Enter REF_NO of Book :\n";
 char x[10];
 fflush(stdin);
 gets(x);
 book* b = search_book(x);
 if(b==NULL){
    cout<<"No Book exists with the given REF_NO !!\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
 cout<<"If patron has a claim.........PRESS 1\n";
 cout<<"Else..........................PRESS 2\n";
 int count;
 cin>>count;
 switch(count){
  case 1:if(b->return_ref_no() == p->return_claimed()){
          b->withdraw();
          b->status();
          p->mini_statement();
          return 1;
         }
         else{
          cout<<"Sorry !Wrong Choice !! \n";
          cout<<"Returning to ADMIN Terminal \n";
          return -1;
         }
  case 2:b->withdraw_open(p->return_id());
         b->status();
         p->mini_statement();
         return 1;
  default:cout<<"Sorry !Wrong Choice !! \n";
          cout<<"Returning to ADMIN Terminal \n";
          return -1;
 }
}












