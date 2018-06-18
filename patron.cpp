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

void patron::mini_statement(){//completed
 cout<<"UID of the patron : "<<id<<"\n";
 cout<<"Name of the patron : "<<name<<"\n";
 cout<<"No of books withdrawn : "<<no_withdrawn<<"\n";
 cout<<"Books withdrawn are : ";
 book* b;
 for(int i=0;i<no_withdrawn;i++){
    b = search_book(withdrawn[i]);
    cout<<"Book's Title : "<<b->return_title()<<"\t";
    cout<<"Book's Reference NO : "<<b->return_ref_no()<<"\t";
    cout<<"Date and time of Withdrawal : "<<b->return_dt()<<"\n";
 }
 if(!no_withdrawn)
    cout<<"NONE \n";
 cout<<"Book claim status : ";
 if(strcmp(claimed,"none")){
    b = search_book(claimed);
    cout<<"TRUE \n";
    cout<<"Book's Title : "<<b->return_title()<<"\t";
    cout<<"Book's Reference NO : "<<b->return_ref_no()<<"\n";
 }
 else cout<<"FALSE \n";
}

int patron::edit_patron(){//completed
 int i;
 while(true){
    cout<<"Enter 1: Name 2: ID,3: Password, for editing the particular field of detail of the patron \n";
    cout<<"Enter any other NO to return \n";
    cin>>i;
    switch(i){
     case 1:{cout<<"Enter new Name of the Patron : ";
            char x[40];
            fflush(stdin);
            gets(x);
            strcpy(name,x);
            cout<<"Successfully changed # \n";
            }
            break;
     case 2:{cout<<"Enter new ID of the Patron : ";
            char x[8];
            fflush(stdin);
            gets(x);
            strcpy(id,x);
            cout<<"Successfully changed # \n";
            }
            break;
     case 3:{cout<<"Enter new Password for Patron : ";
            char x[8];
            fflush(stdin);
            gets(x);
            strcpy(pass,x);
            cout<<"Successfully changed # \n";
            }
            break;
     default:cout<<"RETURNING TO PATRON TERMINAL # \n";
             return 1;
    }
  save_patron(this);
  return 1;
 }
}

int patron::claim(book* b){//completed
 if(strcmp(claimed,"none")){
    cout<<"Have already claimed a book (NOT more than one claim is permitted)!! \n";
    cout<<"Returning to Patron terminal #\n";
    return -1;
 }
 else if(b->return_claim_status()){
    cout<<"The book has already been claimed !! \n";
    cout<<"Returning to Patron terminal #\n";
    return -1;
 }
 else{
    b->change_claim_status();
    b->change_claim_pat(this->return_id());
    strcpy(claimed,b->return_ref_no());
    save_book(b);
    save_patron(this);
    cout<<"Claim successful ! \n";
    return 1;
 }
}

int patron::withdrawn_func(book* b){//completed
 if(no_withdrawn<3){
  strcpy(withdrawn[no_withdrawn],b->return_ref_no());
  no_withdrawn++;
  save_patron(this);
 }
 else{
    cout<<"Maximum NO of books withdrawn by patron !!\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
}

int patron::return_book(){//completed
 int i;
 if(no_withdrawn==0){
    cout<<"NO books are withdrawn yet !! \n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
 else{
    book* b=search_book(withdrawn[0]);
    for(i=0;i<no_withdrawn;i++){
        if(b==NULL) break;
        else{
            cout<<"Enter "<<i+1<<" to return this book \n";
            b->status();
            if(i<no_withdrawn-1){
             b = search_book(withdrawn[i]);
            }
        }
    }
    int j;
    cin>>j;
    if(j>i){
        cout<<"Invalid choice !!\n";
        cout<<"Returning to ADMIN Terminal #\n";
        return -1;
    }
    char temp_next[8];
    switch(i){
        case 1:{b = search_book(withdrawn[0]);
               b->change_availability();
               b->change_with_pat();
               save_book(b);
               for(j=0;j<no_withdrawn-1;j++){
                strcpy(withdrawn[j],withdrawn[j+1]);
               }
               strcpy(withdrawn[j],"none");
               no_withdrawn--;
               cout<<"Book successfully returned !\n";
               cout<<"Returning to ADMIN Terminal #\n";
               break;
               }
        case 2:{b = search_book(withdrawn[1]);
               b->change_availability();
               b->change_with_pat();
               for(j=1;j<(no_withdrawn-1);j++){//so many changes have to be made
                strcpy(withdrawn[j],withdrawn[j+1]);
               }
               strcpy(withdrawn[j],"none");
               no_withdrawn--;
               cout<<"Book successfully returned !\n";
               cout<<"Returning to ADMIN Terminal #\n";
               break;
               }
        case 3:{b = search_book(withdrawn[2]);
               b->change_availability();
               b->change_with_pat();
               save_book(b);
               strcpy(withdrawn[2],"none");
               no_withdrawn--;
               break;
               }
    }
    cout<<"Book successfully returned !\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return 1;
 }
}

int patron::search(){//completed
 while(true){
 cout<<"Enter corresponding NO for searching through desired field \n";
 cout<<"SEARCH BY \t 1:REF_NO \t 2.Title \t 3.Author_Name \t 4.Publications \n";
 cout<<"Enter any other NO to return \n";
 int k;
 cin>>k;
 switch(k){
  case 1:{cout<<"Enter REF_NO \n";
         char x[8];
         cin>>x;
         search_ref_no(x,this);
         }
         break;
  case 2:{cout<<"Enter the Title \n";
         char x[30];
         cin>>x;
         search_title(x,this);
         }
         break;
  case 3:{cout<<"Enter the Author_Name \n";
         char x[30];
         cin>>x;
         search_author(x,this);
         }
         break;
  case 4:{cout<<"Enter the Publisher_Name \n";
         char x[40];
         cin>>x;
         search_publishers(x,this);
         }
         break;
  default:cout<<"Returning to PATRON Terminal #\n";
          return -1;
 }
 }
}
