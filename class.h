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

using namespace std;

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

class admin{
 private:
     char name[40];
     char id[8];
     char pass[8];
 public:
     void init(){
       strcpy(id,"ADMIN");
       strcpy(name,"ADMIN");
       while(true){
        strcpy(pass,"1");
        char pass_check[8];
        cout<<"Enter PASS \n";
        fflush(stdin);
        gets(pass_check);
        if(strcmp(pass_check,pass)==0) break;
        else{
         cout<<"Password doesn't match ! \n";
         cout<<"Retry #\n";
        }
       }
     }
     char* return_id(){
      return id;
     }
     char* return_pass(){
      return pass;
     }
     char* return_name(){
      return name;
     }
     void mini_statement();//
     int add_book();//
     int delete_book();//
     int add_patron();//
     int delete_patron();//
     int issue_book();//
     int collect_book();//
     int book_edit();//
};

class book{
 private:
     char ref_no[10];
     char title[30];
     char author[30];
     char publications[40];
     bool availability;
     bool claim_status;
     char* dt;
     char with_pat[8];
     char claim_pat[8];
 public:
     void init(){
      cout<<"Enter book's ref_no \n";
      fflush(stdin);
      gets(ref_no);
      cout<<"Enter book's title \n";
      fflush(stdin);
      gets(title);
      cout<<"Enter book's author \n";
      fflush(stdin);
      gets(author);
      cout<<"Enter book's publications \n";
      fflush(stdin);
      gets(publications);
      availability = true;
      claim_status = false;
      dt=NULL;
      strcpy(with_pat,"none");
      strcpy(claim_pat,"none");
      }
      char* return_title(){
       return title;
      }
      char* return_author(){
       return author;
      }
      char* return_publications(){
       return publications;
      }
      char* return_ref_no(){
       return ref_no;
      }
      bool return_availability(){
       return availability;
      }
      char* return_dt(){
       return dt;
      }
      bool return_claim_status(){
       return claim_status;
      }
      void change_claim_status(){
       claim_status=true;
      }
      void change_claim_pat(char claim_id[8]){
       strcpy(claim_pat,claim_id);
      }
      void change_availability(){
       availability=true;
      }
      void change_with_pat(){
       strcpy(with_pat,"none");
      }
      int calc_dt();//
      int status();//
      int withdraw();//
      int edit_book();//
      int withdraw_open(char* actual);//
};

class patron{
 private:
     char id[8];
     char pass[8];
     char name[40];
     int no_withdrawn;
     char withdrawn[3][8];
     char claimed[8];
 public:
     void init(){
       cout<<"Enter patron's id \n";
       fflush(stdin);
       gets(id);
       cout<<"Enter patron's name \n";
       fflush(stdin);
       gets(name);
       while(true){
        char pass_check[8];
        cout<<"Enter patron's password \n";
        fflush(stdin);
        gets(pass);
        cout<<"Re-enter patrons's password \n";
        fflush(stdin);
        gets(pass_check);
        if(strcmp(pass_check,pass)==0) break;
        else{
         cout<<"Password doesn't match ! \n";
         cout<<"Retry #\n";
        }
       }
      for(int i=0;i<3;i++){
       strcpy(withdrawn[i],"none");
      }
       strcpy(claimed,"none");
     }
     char* return_id(){
      return id;
     }
     char* return_pass(){
      return pass;
     }
     char* return_name(){
      return name;
     }
     int return_no_withdrawn(){
      return no_withdrawn;
     }
     char* return_claimed(){
      return claimed;
     }
     int withdrawn_func(book* b);//
     int claim(book* b);//
     int return_book();//
     int edit_patron();//
     int search();//
     void mini_statement();//

};

//These  functions are defined in the parse_hash_search source file whose declarations are given here
int uniform(char* setence);
void parsing(char token,vector<string>& parsed,string str);
int hashing_vector(vector<string>& txt,string pat);
int hashing_normal(string txt,string pat);
int search_ref_no(char* x,patron* p);
int search_title(char* x,patron* p);
int search_author(char* x,patron* p);
int search_publishers(char* x,patron* p);
patron* password_patron();
admin* password_admin();
int save_patron(patron* p);
int save_book(book* b);
book* search_book(char actual[8]);
patron* search_patron(char actual[8]);

#endif // HASH_H_INCLUDED
