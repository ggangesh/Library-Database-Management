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
#include<conio.h>//to use the getch function
#include<climits>//to use INT_MAX value

#include"class.h"

using namespace std;

int main(){
 char d,c,rep;
 while(true){
    cout<<"\n-----------------------------------------------"<<endl;
    cout<<"          Welcome to Library Manager            "<<endl;
    cout<<"-----------------------------------------------\n"<<endl;
    cout<<endl;
    cout<<"To access the program as a Librarian....PRESS 1 "<<endl;
    cout<<"To access the program as a Patron.......PRESS 2 "<<endl;
    cout<<"To exit the program.....................PRESS 3 "<<endl;
	cin >>d;
	switch(d){
        case '1':{rep = '1';
               admin a;
               a.init();
               while(rep!='0'){
               cout<<"\n-----------------------------------------------"<<endl;
               cout<<"               Welcome Librarian                 "<<endl;
               cout<<"-----------------------------------------------\n"<<endl;
               cout<<"To Add a Patron.........................PRESS 1"<<endl;
               cout<<"To Delete a Patron......................PRESS 2"<<endl;
               cout<<"To Issue a book.........................PRESS 3"<<endl;
               cout<<"To Return a book........................PRESS 4"<<endl;
               cout<<"To Add book to data base................PRESS 5"<<endl;
               cout<<"To Delete book From data base...........PRESS 6"<<endl;
               cout<<"To Edit book details in data base.......PRESS 7"<<endl;
               cout<<"To Recieve a mini-statement of info.....PRESS 8"<<endl;
               cout<<"To go to main menu..........PRESS any other key"<<endl;
               cin>>c;
               switch(c){
                case '1':a.add_patron();
                       break;
                case '2':a.delete_patron();
                       break;
                case '3':a.issue_book();
                       break;
                case '4':a.collect_book();
                       break;
                case '5':a.add_book();
                       break;
                case '6':a.delete_book();
                       break;
                case '7':a.book_edit();
                       break;
                case '8':a.mini_statement();
                       break;
                default:cout<<"Redirecting #\n";
                        rep='0';
                        break;
               }
               if(rep=='0'){
                cout<<"Press 0 to Confirm LOG-OUT \n";
                cin>>rep;
               }
               }
               }
               break;
        case '2':{patron* p = password_patron();
                rep = '1';
                if(p==NULL)
                break;
                while(rep!='0'){
                cout<<"\n-----------------------------------------------"<<endl;
                cout<<"                Welcome Patron    "<<endl;
                cout<<"-----------------------------------------------\n"<<endl;
                cout<<"To search book in the library(if available can claim)........PRESS 1"<<endl;
                cout<<"To withdraw a book...........................................PRESS 2"<<endl;
                cout<<"To return a book.............................................PRESS 3"<<endl;
                cout<<"To Edit details in profile...................................PRESS 4"<<endl;
                cout<<"To have a mini-statement about profile.......................PRESS 5"<<endl;
                cout<<"To go back PRESS ANY KEY other than above"<<endl;
                cin>>c;
                switch(c){
                 case '1':p->search();
                        break;
                 case '2':cout<<"Place a claim if the book is available and not claimed by anyone\n";
                        cout<<"This will reserve the book for withdrawal \n";
                        cout<<"Can withdraw it in the library \n"<<"Contact ADMIN for further details \n";
                        break;
                 case '3':cout<<"Report to the Library and contact ADMIN for returning book \n";
                        break;
                 case '4':p->edit_patron();
                        break;
                 case '5':p->mini_statement();
                        break;
                 default:cout<<"Redirecting #\n";
                         rep='0';
                         break;
                }
                if(rep=='0'){
                 cout<<"Enter 0 to Confirm LOG-OUT \n";
                 cin>>rep;
                }
                }
                }
                break;
        case '3':cout<<"Program control REDIRECTED to OS #\n";
               exit(0);
        default:cout<<"Wrong choice !!\n";
                cout<<"Returning to Library Terminal #\n";
                break;
	}
 }
 return 1;
}
















