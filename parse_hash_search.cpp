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

#include "class.h"

using namespace std;

FILE *fp,*fb,*tp,*tb;

long long int q = 5;

int uniform(char* sentence){
 for(int i=0;i<strlen(sentence);i++){
    sentence[i]=tolower(sentence[i]);
 }
 return 1;
}

void parsing(char token,vector<string>& parsed,string str){
//here the token is the delimiter which is blank space
//the vector is here passed by reference so that cahnges are reflected in the dearch function

 int lastposition,position;

//lastposition is used to maintain the position of the first non blank character in the sentence
 lastposition = str.find_first_not_of(token,0);

//position is used to maintain the position of the blank character in the current iteration
 position = str.find_first_of(token,lastposition);

//the loop runs until the end of sentence
 while(lastposition != str.length()-1 || position != str.length()-1){

//pushing back the word in the senetence to the vector
    parsed.push_back(str.substr(lastposition,position-lastposition));

//repositioning lastposition and position
    lastposition = str.find_last_not_of(token,position);
    position = str.find_first_of(token,lastposition);
 }
}

int hashing_vector(vector<string>& txt,string pat){

//using rabin-karp algorithm for all the strings in the sentence

 int m,n,t,p,h;
//here m is the size of the txt word
//n is size of the pattern
//t is the hash value of the txt
//p is the hash value of the pattern
//h is the parameter in rabin-karp algorithm

const int d = 256;
//d is the no of characters in the input character

//looping till all the words in the sentence are pattern checked
 for(int i=0;i<txt.size();i++){
    m = pat.length();
    n = txt.at(i).length();
    t = 0;
    p = 0;
    h = 1;

//the value of h would be dpow(m-1)%q
    for(int j=0;j<m;j++){
        h = (h*d)%q;
    }

//to calculate the hash values of the txt and the pattern
    for(int j=0;j<m;j++){
        p = (d*p + pat[j])%q;
        t = (d*t + txt.at(i)[j])%q;
    }

//to check the hash values of the pattern and string
    int k;
    for(int j=0;j<=n-m;j++){
        if(p == t){
            for(int k=0;k<m;k++){
                if(pat[k] != txt.at(i)[k+j]){
                    break;
                }
            }

//if the pattern matches returning to the search function
           if(k == m){
              return 1;
           }
        }

//if the pattern does not match then the next hash code is found
        t = (d*(t - txt[i].at(j)*h)) + txt[i].at(j+m)%q;

//when the hash becomes negative then its coneverted positive
        if(t<0){
            t=t+q;
        }
    }
 }
 return 0;
}

int hashing_normal(string txt,string pat){

//using rabin karp algorithm

 int m,n,t,p,h;
//here m is the size of the txt word
//n is size of the pattern
//t is the hash value of the txt
//p is the hash value of the pattern
//h is the parameter in rabin-karp algorithm

const int d = 256;
//d is the no of characters in the input character

    m = pat.length();
    n = txt.length();
    t = 0;
    p = 0;
    h = 1;

//the value of h would be dpow(m-1)%q
    for(int j=0;j<m;j++){
        h = (h*d)%q;
    }

//to calculate the hash values of the txt and the pattern
    for(int j=0;j<m;j++){
        p = (d*p + pat[j])%q;
        t = (d*t + txt[j])%q;
    }

//to check the hash values of the pattern and string
    int k;
    for(int j=0;j<=n-m;j++){
        if(p == t){
            for(k=0;k<m;k++){
                if(pat[k] != txt[k+j]){
                    break;
                }
            }

//if the pattern matches returning to the search function
           if(k==m){
              return 1;
           }
        }

//if the pattern does not match then the next hash code is found
        t = (d*(t - txt[j]*h) + txt[j+m])%q;

//when the hash becomes negative then its coneverted positive
        if(t<0){
            t=t+q;
        }
    }
    return 0;
}

int search_ref_no(char* x,patron* p){
 uniform(x);
 string pat(x);
 int count = 0;
 fb=fopen("book.txt","rb+");
 if(fb==NULL){
    cout<<"Error in opening the file 'book.txt' !!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 rewind(fb);
 book* b = new book;
 if(b==NULL){
    cout<<"Error in searching !!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 long int bsize = sizeof(*b);
 delete b;
 while(!feof(fb)){
    fread(b,bsize,1,fb);
    char* y = b->return_ref_no();
    uniform(y);
    string txt(y);
    int i=hashing_normal(txt,pat);
    if(i){
        count++;
        b->status();
        cout<<"Enter 1 to claim this book if available :\n";
        cin>>i;
        if(i==1){
            p->claim(b);
        }
    }
 }
 fclose(fb);
 if(count){
    cout<<"These are the matching searches !\n";
 }
 else
    cout<<"The keyword is not found in the database !!\n";
 cout<<"Returning to the PATRON Terminal #\n";
 return 1;
}

int search_title(char* x,patron* p){
 uniform(x);
 string pat(x);
 int count =0;
 fb=fopen("book.txt","rb+");
 if(fb==NULL){
    cout<<"Error in opening the file 'book.txt'!!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 rewind(fb);
 book* b = new book;
 if(b==NULL){
    cout<<"Error in searching !!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 long int bsize = sizeof(*b);
 delete b;
 while(!feof(fb)) {
    fread(b,bsize,1,fb);
    char* y;
    y=b->return_title();
    uniform(y);
    string str(y);
    vector<string> parsed;
    parsing(' ',parsed,str);
    int i=hashing_vector(parsed,x);
    if(i){
        count++;
        b->status();
        cout<<"Enter 1 to claim this book if available :\n";
        cin>>i;
        if(i==1){
            p->claim(b);
        }
    }
 }
 if(count){
    cout<<"These are the matching searches !\n";
 }
 else
    cout<<"The keyword is not found in the database !! \n";
 cout<<"Returning to PATRON Terminal #";
 fclose(fb);
 return 1;
}

int search_author(char* x,patron* p){
 uniform(x);
 string pat(x);
 int count =0;
 fb=fopen("book.txt","rb+");
 if(fb==NULL){
    cout<<"Error in opening the file 'book.txt' !!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 rewind(fb);
 book* b = new book;
 if(b==NULL){
    cout<<"Error in searching !!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 long int bsize = sizeof(*b);
 delete b;
 while(!feof(fb)) {
    fread(b,bsize,1,fb);
    char* y;
    y=b->return_author();
    uniform(y);
    string str(y);
    vector<string> parsed;
    parsing(' ',parsed,str);
    int i=hashing_vector(parsed,x);
    if(i){
        count++;
        b->status();
        cout<<"Enter 1 to claim this book if available :\n";
        cin>>i;
        if(i==1){
            p->claim(b);
        }
    }
 }
 if(count){
    cout<<"These are the matching searches !\n";
 }
 else
    cout<<"The keyword is not found in the database !! \n";
 cout<<"Returning to PATRON Terminal #";
 fclose(fb);
 return 1;
}

int search_publishers(char* x,patron* p){
 uniform(x);
 string pat(x);
 int count =0;
 fb=fopen("book.txt","rb+");
 if(fb==NULL){
    cout<<"Error in opening the file 'book.txt' !!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 rewind(fb);
 book* b = new book;
 if(b==NULL){
    cout<<"Error in searching !!\n";
    cout<<"Returning to PATRON Terminal \n";
    return -1;
 }
 long int bsize = sizeof(*b);
 delete b;
 while(!feof(fb)) {
    fread(b,bsize,1,fb);
    char* y;
    y=b->return_publications();
    uniform(y);
    string str(y);
    vector<string> parsed;
    parsing(' ',parsed,str);
    int i=hashing_vector(parsed,x);
    if(i){
        count++;
        b->status();
        cout<<"Enter 1 to claim this book if available :\n";
        cin>>i;
        if(i==1){
            p->claim(b);
        }
    }
 }
 if(count){
    cout<<"These are the matching searches !\n";
 }
 else
    cout<<"The keyword is not found in the database !! \n";
 cout<<"Returning to PATRON Terminal #";
 return 1;
}

patron* password_patron(){
 string y,actual_pass,actual_id;
 char c;
 cout<<"Enter your ID :\n";
 cin>>actual_id;
 long int size;
    fp=fopen("patron.txt","rb+");
    if(fp==NULL){
     cout<<"Error opening file !!\n";
     cout<<"Returning to Library Database #\n";
     return NULL;
    }
    patron* z=new patron;
    if(z==NULL){
     cout<<"Error in pass check !!\n";
     cout<<"Returning to Library Database #\n";
     return NULL;
    }
    size = sizeof(*z);
    delete z;
 rewind(fp);
 while(!feof(fp)){
  fread(z,size,1,fp);
  string x(z->return_id());
  int k=hashing_normal(actual_id,x);
  if(k==1){
   actual_pass.assign(z->return_pass());
   for(int j=0;j<3;j++){
    cout<<"Enter your PASSWORD :\n";
    for(int i=0;i<actual_pass.length();i++){
       c = getch();
       cout<<"*";
       y+=c;
    }
    if(!y.compare(actual_pass)){
      cout<<"Password match !!\n";
      return z;
    }
   }
   cout<<"Maximum NO of tries exceeded !\n";
   cout<<"Returning to Library Database #";
   return NULL;
  }
 }
 cout<<"Input ID Error(Not found in database) !!\n";
 cout<<"Returning to Library Database #\n";
 return NULL;
}

admin* password_admin(){
 string y,actual_pass,actual_id;
 char c;
 cout<<"Enter your ID :\n";
 cin>>actual_id;
 long int size;
    fp=fopen("admin.txt","rb+");
    if(fp==NULL){
     cout<<"Error opening file !!\n";
     cout<<"Returning to Library Database #\n";
     return NULL;
    }
    admin* z=new admin;
    if(z==NULL){
     cout<<"Error in pass check !!\n";
     cout<<"Returning to Library Database #\n";
     return NULL;
    }
    size = sizeof(*z);
    delete z;
 rewind(fp);
 while(!feof(fp)){
  fread(z,size,1,fp);
  string x(z->return_id());
  int k=hashing_normal(actual_id,x);
  if(k==1){
   actual_pass.assign(z->return_pass());
   for(int j=0;j<3;j++){
    cout<<"Enter your PASSWORD :\n";
    for(int i=0;i<8;i++){
       c = getch();
       cout<<"*";
       y+=c;
    }
    if(!y.compare(actual_pass)){
      cout<<"Password match !!\n";
      return z;
    }
   }
   cout<<"Maximum NO of tries exceeded !\n";
   cout<<"Returning to Library Database #";
   return NULL;
  }
 }
 cout<<"Input ID Error(Not found in database) !!\n";
 cout<<"Returning to Library Database #\n";
 return NULL;
}

int save_patron(patron* p){
 fp = fopen("patron.txt","wb+");
 if(fp == NULL){
    cout<<"Error saving data in Data Base !!\n";
    cout<<"RETRY !!\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
 string actual_id(p->return_id());
 long int psize=sizeof(*p);
 int z;
 rewind(fp);
 while(!feof(fp)){
    fread(p,psize,1,fp);
    string x(p->return_id());
    z=hashing_normal(x,actual_id);
    if(z==1){
     break;
    }
 }
 fseek(fp,-1*psize,SEEK_CUR);
 fwrite(p,psize,1,fp);
 fclose(fp);
 return 1;
}

int save_admin(admin* a){
 fp = fopen("admin.txt","wb+");
 if(fp == NULL){
    cout<<"Error saving data in Data Base !!\n";
    cout<<"RETRY !!\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
 string actual_id(a->return_id());
 long int asize=sizeof(*a);
 int z;
 rewind(fp);
 while(!feof(fp)){
    fread(a,asize,1,fp);
    string x(a->return_id());
    z=hashing_normal(x,actual_id);
    if(z==1){
     break;
    }
 }
 fseek(fp,-1*asize,SEEK_CUR);
 fwrite(a,asize,1,fp);
 fclose(fp);
 return 1;
}

int save_book(book* b){
 fb=fopen("book.txt","wb+");
 if(fb==NULL){
    cout<<"Error saving data in Data Base !!\n";
    cout<<"RETRY !!\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return -1;
 }
 string actual_ref_no(b->return_ref_no());
 long int bsize=sizeof(*b);
 int z;
 rewind(fb);
 while(!feof(fb)){
    fread(b,bsize,1,fb);
    string x(b->return_ref_no());
    z=hashing_normal(x,actual_ref_no);
    if(z==1){
     break;
    }
 }
 fseek(fb,-1*bsize,SEEK_CUR);
 fwrite(b,bsize,1,fb);
 fclose(fb);
 return 1;
}

book* search_book(char actual[8]){
 fb = fopen("book.txt","rb+");
 if(fb==NULL){
    cout<<"Error in copying changes in Data Base !!\n";
    cout<<"RETRY !!\n";
    cout<<"Returning back to TERMINAL #\n";
    return NULL;
 }
 book* b = new book;
    if(b==NULL){
     cout<<"Error in Searching !!\n";
     cout<<"RETRY !!\n";
     cout<<"Returning to Terminal #\n";
     return NULL;
    }
 long int bsize = sizeof(*b);
 delete b;
 int i;
 string actual_string(actual);
 rewind(fb);
 while(!feof(fb)){
    fread(b,bsize,1,fb);
    string x(b->return_ref_no());
    i=hashing_normal(x,actual_string);
    if(i==1){
     fclose(fb);
     return b;
    }
 }
 if(i!=1){
    cout<<"Match not found !! \n";
    fclose(fb);
    return NULL;
 }
}

patron* search_patron(char actual[8]){
 fp = fopen("patron.txt","rb+");
 if(fp==NULL){
    cout<<"Error in copying changes in Data Base !!\n";
    cout<<"RETRY !!\n";
    cout<<"Returning back to TERMINAL #\n";
    return NULL;
 }
 patron* p = new patron;
    if(p==NULL){
     cout<<"Error  !!\n";
     cout<<"RETRY !!\n";
     cout<<"Returning to ADMIN Terminal #\n";
     return NULL;
    }
 long int psize = sizeof(*p);
 delete p;
 int i;
 string actual_string(actual);
 rewind(fp);
 while(!feof(fp)){
    fread(p,psize,1,fp);
    string x(p->return_id());
    i=hashing_normal(x,actual_string);
    if(i==1){
     fclose(fp);
     return p;
    }
 }
 if(i!=1){
    cout<<"Match not found !! \n";
    fclose(fp);
    return NULL;
 }
}

int admin::add_book()
{
    fb=fopen("book.txt","ab+");
    if(fb==NULL){
        cout<<"Cannot open file 'book.txt' ! \n";
        cout<<"Returning to ADMIN Terminal # \n";
        return -1;
    }
    cout<<"------------------------------------------------"<<endl;
    cout<<"              ADDITION OF BOOK                  "<<endl;
    cout<<"------------------------------------------------"<<endl;
    book* b=new book;
    if(b==NULL){
     cout<<"Record creation Error !!\n";
     cout<<"RETRY !!\n";
     cout<<"Returning to ADMIN Terminal #\n";
     return -1;
    }
    b->init();
    b->status();
    long int bsize=sizeof(*b);
    fseek(fb,0,SEEK_END);
    fwrite(b,bsize,1,fb);
    cout<<"Book successfully added to File !! \n";
    cout<<"Returning to ADMIN Terminal # \n";
    return 1;
}

int admin::delete_book()
{
    fb=fopen("book.txt","wb+");
    if(fb==NULL){
        cout<<"Cannot open file book.txt ! \n";
        cout<<"Returning to ADMIN Terminal # \n";
        return -1;
    }
	tb=fopen("temp.txt","wb+");
    if(fb==NULL){
        cout<<"Cannot open file temp.txt ! \n";
        cout<<"Returning to ADMIN Terminal # \n";
        return -1;
    }
    char a[10];
    rewind(tb);
	cout<<"-----------------------------------------------"<<endl;
    cout<<"             DELETION OF BOOK                  "<<endl;
    cout<<"-----------------------------------------------"<<endl;
	cout<<"Give the reference no. of the book to be deleted"<<endl;
	fflush(stdin);
	gets(a);
	rewind(fb);
	book* b=new book;
	long int bsize = sizeof(*b);
	delete b;

	while (fread(b,bsize,1,fb)==1)//the function fread and fwrite gives out 1 as output when the file is read and returns 0 so the loop will terminate
		{
		if (strcmp(a,b->return_ref_no())!=0){
		    fwrite(b,bsize,1,tb);
		    }
		else{
		    cout<<"The required book found and deleted"<<endl;}
            }
	fclose(fb);
	fclose(tb);
	if(remove("book.txt")!=0){
        cout<<"Error in deleting the book!"<<endl;
    }
	char oldname[]="temp.txt";
	char newname[]="book.txt";
	if(rename(oldname,newname)!=0){
        cout<<"Error in deleting the book!"<<endl;
    }
	return 1;
}

int admin::add_patron(){
    cout<<"-----------------------------------------"<<endl;
    cout<<"            ADDING A PATRON              "<<endl;
    cout<<"-----------------------------------------"<<endl;
    fp=fopen("patron.txt","ab+");
    if(fp==NULL){
        cout<<"Cannot open file temp.txt ! \n";
        cout<<"Returning to ADMIN Terminal # \n";
        return -1;
    }
    patron* p=new patron;
    if(p==NULL){
     cout<<"Record creation Error !!\n";
     cout<<"RETRY !!\n";
     cout<<"Returning to ADMIN Terminal #\n";
     return -1;
    }
    p->init();
    p->mini_statement();
    long int psize=sizeof(*p);
    fseek(fp,0,SEEK_END);
    fwrite(p,psize,1,fp);
    fclose(fp);
    cout<<"Successfully added Patron to the Library !\n";
    cout<<"Returning to ADMIN Terminal #\n";
    return 1;
}

int admin::delete_patron(){
    cout<<"-----------------------------------------"<<endl;
    cout<<"            REMOVING A PATRON            "<<endl;
    cout<<"-----------------------------------------"<<endl;
    char str[8];
    char oldname[] ="temp.txt";
    char newname[] ="patron.txt";
	fp=fopen("patron.txt","a+");
    if(fp==NULL){
        cout<<"Cannot open file patron.txt ! \n";
        cout<<"Returning to ADMIN Terminal # \n";
        return -1;
    }
	tp=fopen("temp.txt","wb+");
    if(tp==NULL){
        cout<<"Cannot open file temp.txt ! \n";
        cout<<"Returning to ADMIN Terminal # \n";
        return -1;
    }
    rewind (tp);

	cout<<"Enter Patron ID to be deleted \n"<<endl;
	cin>>(str);
	rewind (fp);
	patron* p=new patron;
	long int psize = sizeof(*p);
	delete p;

	while (fread(p,psize,1,fp)==1)
		{
		if (strcmp(str,p->return_id())!=0)
			{
                fwrite(p,psize,1,tp);
			}
		}
    cout<<"Patron successfully deleted \n";
    cout<<"Returning to ADMIN Terminal #\n";
	fclose(fp);
	fclose(tp);
	remove( "patron.txt" );
	rename( oldname , newname );
	return 1;
}
