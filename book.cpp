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

int book::calc_dt(){//completed
 time_t now = time(0);
 this->dt = ctime(&now);
 return 1;
}

int book::status(){//completed
 cout<<"1: REF NO : "<<ref_no<<"\n";
 cout<<"2: Title : "<<title<<"\n";
 cout<<"3: Author(s) : "<<author<<"\n";
 cout<<"4: Publication(s) : "<<publications<<"\n";
 cout<<"5: Availability : "<<boolalpha<<availability<<"\n";
 if(!availability){
    cout<<"6: Date and Time of withdrawal : "<<dt<<"\n";
 }
 cout<<"7: Claim status : "<<claim_status<<"\n";
 return 1;
}

int book::edit_book(){//completed
 int i;
 while(true){
    cout<<"Enter 1: REF NO, 2: Title,3: Author(s),4: Publication(s) for editing the particular field of detail of the book \n";
    cout<<"Enter any other NO to return \n";
    cin>>i;
    switch(i){
     case 1:{cout<<"Enter new REF NO of the book : ";
            char x[10];
            fflush(stdin);
            gets(x);
            strcpy(ref_no,x);
            save_book(this);
            cout<<"Successfully changed # \n";
            }
            break;
     case 2:{cout<<"Enter new title of the book : ";
            char y[30];
            fflush(stdin);
            gets(y);
            strcpy(title,y);
            save_book(this);
            cout<<"Successfully changed # \n";
            }
            break;
     case 3:{cout<<"Enter new Author name for book : ";
            char z[30];
            fflush(stdin);
            gets(z);
            strcpy(author,z);
            save_book(this);
            cout<<"Successfully changed # \n";
            }
            break;
     case 4:{cout<<"Enter new Publications for the book : ";
            char w[40];
            fflush(stdin);
            gets(w);
            strcpy(publications,w);
            save_book(this);
            cout<<"Successfully changed # \n";
            }
            break;
     default:cout<<"RETURNING TO ADMIN TERMINAL # \n";
             return 1;
    }
 }
}

int book::withdraw(){//completed
 if(availability){
    patron* p;
    p = search_patron(claim_pat);
    int i = p->withdrawn_func(this);
    if(i==1){
        strcpy(with_pat,claim_pat);
        strcpy(claim_pat,"none");
        availability = false;
        claim_status=false;
        this->calc_dt();
        save_book(this);
        cout<<"Book successfully withdrawn \n";
        cout<<"Returning to ADMIN Terminal #\n";
        return 1;
    }
    else if(i==-1){
        cout<<"The book is not available !\n";
        cout<<"Returning to ADMIN Terminal #\n";
        return -1;
    }
    else{
        return -1;
    }
 }
}

int book::withdraw_open(char* actual){//completed
 if(!availability){
    cout<<"The book is not available !\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
 else if (claim_status){
    cout<<"The book is claimed by another patron !\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
 else{
    patron* p = search_patron(actual);
    int i=p->withdrawn_func(this);
    if(i==1){
        strcpy(with_pat,p->return_id());
        availability = false;
        claim_status=false;
        this->calc_dt();
        save_book(this);
        cout<<"Book successfully withdrawn \n";
        cout<<"Returning to ADMIN Terminal #\n";
        return 1;
    }
 }
}










