//
// Created by 16963 on 2021/2/20.
//

#ifndef UNTITLED5_HANDLE_H
#define UNTITLED5_HANDLE_H
#include "bookstore.h"
#include <queue>
#define cd(x)  (char*)&x
#define MAXNUL  50
#define MAXNBL 80
myblocklist ISBN;
myblocklist name;
myblocklist keyword;
myblocklist author;
myblocklist users;
const int uid_len=30;
const int pwd_len=30;
const int u_n_len=30;
const int ISBN_len=20;
const int au_len=60;
const int name_lem=60;
const int keyw_len=60;
const int quantity_m=100000;
struct user{
    //int numofuser;
    int priviledge;
    char name[MAXNUL];
    char userid[MAXNUL];
    char passwd[MAXNUL];
};
struct book{
    int quantity;
    char IBSN[MAXNBL];
    char name[MAXNBL];
    char author[MAXNBL];
    char keyword[MAXNBL];
    double price;
};
class handle {
private:
    const int i = sizeof(int);
    const int b = sizeof(block);
    const int n = sizeof(node);
    const int u = sizeof(user);
    const int bo = sizeof(book);
    int userpri=0;
    int anoupri;
    string allbofile;
    string addufile;
    fstream abos;
    fstream aus;
    int numofboall = 0;
    int numofuall = 0;
    int slmainpos;
    finance fi;
    stack<pair<user, int>> userstack;//int为选中的ISBN的绝对位置
    unordered_map<string, int> count;//string为userid int为计数
    void abosinsert(book boo) {
        abos.seekp(0);
        numofboall++;
        abos.write(cd(numofboall), i);
        abos.seekp(i + numofboall * bo);
        abos.write(cd(boo), u);
    }

    void ausinsert(user& us) {
        aus.seekp(0);
        numofuall++;
        aus.write(cd(numofuall), i);
        aus.seekp(i);
        aus.write(cd(us), u);
    }

public:
    handle(){}
    void initial(const char *adname,const char *auname,const char *ISBNname,
                 const char *namename,const char *keyname, const char *authorname,
                 const char *usersname,const char* financename,const char* ISBNpool,
                 const char* namepool,const char* keypool,const char* authorpool,
                 const char* userpool) {
        abos.open(adname, ios::in | ios::out | ios::binary);
        aus.open(auname, ios::in | ios::out | ios::binary);
        if (!abos.is_open()) {
            ofstream f1;
            f1.open(adname, ios::out | ios::binary);
            ofstream f2;
            f2.open(auname, ios::out | ios::binary);
            f1.seekp(0);
            int zero = 0;
            f1.write(cd(zero), i);
            numofboall=0;
            f2.seekp(0);
            int one=1;
            f2.write(cd(one), i);
            numofuall=1;
            ISBN.initial(ISBNname, ISBNpool);
            name.initial(namename, namepool);
            author.initial(authorname, authorpool);
            keyword.initial(keyname, keypool);
            users.initial(usersname, userpool);
            fi.initialf(financename);
            string strname = "root";
            string passwd = "sjtu";
            string userid = "root";
            user root;
            strcpy(root.userid, userid.c_str());
            //cout<<root.userid<<endl;
            //cout<<strname<<endl;
            strcpy(root.name, strname.c_str());
            strcpy(root.passwd, passwd.c_str());
            root.priviledge = 7;
            users.insert(strname.c_str(), 1);
            f2.write(cd(root),u);
            f1.close();
            f2.close();
        } else {
            ISBN.initial(ISBNname, ISBNpool);
            name.initial(namename, namepool);
            author.initial(authorname, authorpool);
            keyword.initial(keyname, keypool);
            users.initial(usersname, userpool);
            fi.initialf(financename);
            abos.seekg(0);
            abos.read(cd(numofboall), i);
            aus.seekg(0);
            aus.read(cd(numofuall), i);
           // cout<<numofuall<<endl;
        }
        user zero;
        zero.priviledge=0;
        zero.userid[0]='\0';
        zero.passwd[0]='\0';
        zero.name[0]='\0';
        userstack.push(pair<user,int>(zero,-1));
        abos.close();
        aus.close();
    }
    int judge(string order) {
        if(order=="su") return 1;
        else if(order=="register")  return 2;
        else if(order=="logout")  return 3;
        else if(order=="buy") return 4;
        else if(order=="show")return 5;
        else if(order=="passwd")  return 6;
        else if(order=="select")   return 7;
        else if(order=="modify")  return 8;
        else if(order=="import")  return 9;
        else if(order=="useradd")  return 10;
        else if(order=="delete")  return 11;
        else if(order=="quit"||order=="exit") return 0;
        else{
            throw Error();
        }
    }
    int getpri(){
      //  cout<<anoupri<<endl;
        return userpri;
    }
    queue<string>* is_correct(int op){//根据op 读入，拆解字符串
        queue<string>* streamstr=new queue<string>;
        switch (op) {
            case 1:{
                string userid;
                int pos;
                cin>>userid;//待拆解字符串
                //pos=todo.find(' ');
                char flag;
                cin.get(flag);
                if(flag=='\r'){
                    if(userid.length()>uid_len)  delete streamstr,throw Error();
                    if(userpri==7) streamstr->push(userid);
                    else throw Error();
                }
                else{
                   //加长度疑问
                   cin.putback(flag);
                    string passwd;
                    cin>>passwd;
                    if(userid.length()>uid_len)  delete streamstr,throw Error();
                    if(passwd.length()>pwd_len)  delete streamstr,throw Error();
                    streamstr->push(userid);
                    streamstr->push(passwd);
                    //strncpy(userid.c_str(),todo.c_str(),pos);
                }
                return streamstr;
            }
            case 2:{
                string userid;
                string passwd;
                string name;
                int pos;
                cin>>userid;//待拆解字符串
                cin>>passwd;
                cin>>name;
                if(userid.length()>uid_len) delete streamstr,throw Error();
                if(passwd.length()>pwd_len) delete streamstr,throw Error();
                if(name.length()>u_n_len)  delete streamstr,throw Error();
                streamstr->push(userid);
                streamstr->push(passwd);
                streamstr->push(name);
                return streamstr;
            }
            case 3:{
             //   cout<<userpri<<endl;
                if(userpri<1){string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                delete streamstr;
                return nullptr;
            }
            case 4:{
                if(userpri<1) {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string ISBN;
                int quantity;//待拆解字符串
                cin>>ISBN;
                cin>>quantity;
                string strquan=to_string(quantity);
                if(ISBN.length()>ISBN_len)   delete streamstr,throw Error();
                if(strquan[0]>'9'||strquan[0]<'0') delete streamstr, throw Error();
                streamstr->push(ISBN);
                streamstr->push(strquan);
                //strncpy(userid.c_str(),todo.c_str(),pos);
                return streamstr;
            }
            case 5:{
                if(userpri<1)  {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string todo;
                int pos;
                char flag;
                cin.get(flag);
                if(flag==' ')  cin>>todo;
                else cin.putback(flag);
                if(todo.length()==0)  {streamstr->push("showall");return streamstr;}
                if(todo[0]=='-'){
                    if(todo[1]=='I'){
                        pos=todo.find('=');
                        string ISBN="";
                        for(int i=pos+1;todo[i]!='\0';i++) ISBN+=todo[i];
                        if(ISBN.length()>ISBN_len) delete streamstr,throw Error();
                        streamstr->push("I");
                        streamstr->push(ISBN);
                    }
                    else if(todo[1]=='a'){
                        pos=todo.find('"');
                        string author="";
                        for(int i=pos+1;todo[i]!='"';i++) author+=todo[i];
                        if(author.length()>au_len) delete streamstr,throw Error();
                        streamstr->push("a");
                        streamstr->push(author);
                    }
                    else if(todo[1]=='k'){
                        pos=todo.find('"');
                        string keyword="";
                        for(int i=pos+1;todo[i]!='"';i++) keyword+=todo[i];
                        //strcpy(keyword,todo.c_str()+pos+2);
                        if(keyword.length()>keyw_len) delete streamstr,throw Error();
                        streamstr->push("k");
                        streamstr->push(keyword);
                    }
                    else if(todo[1]=='n'){
                        pos=todo.find('"');
                        string name="";
                        for(int i=pos+1;todo[i]!='"';i++) name+=todo[i];
                        if(name.length()>name_lem) delete streamstr,throw Error();
                        streamstr->push("n");
                        streamstr->push(name);
                    }
                }
                else if(todo[0]=='f'){
                    if(userpri<7) {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                    pos=todo.find(' ');
                    string time;
                    cin.get(flag);
                    if(flag=='\r'){
                        streamstr->push("financeall");
                    }
                    else{
                        cin>>time;
                        streamstr->push("finance");
                        streamstr->push(time);
                    }
                }
                else   delete streamstr,throw Error();
                return streamstr;
            }
            case 6:{//repasswd
                if(userpri<1)  {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string userid;
                int pos;
                cin.get();
                cin>>userid;//待拆解字符串
                if(userid.length()>uid_len) {string unuse;getline(cin,unuse,'\r'); delete streamstr,throw Error();}
                streamstr->push(userid);
                string newpasswd;
                if(userpri==7){
                   cin>>newpasswd;
                    if(newpasswd.length()>pwd_len)  delete streamstr,throw Error();
                    streamstr->push(newpasswd);
                    return streamstr;
                }
                else{
                    string oldpasswd;
                    cin>>oldpasswd;
                    cin>>newpasswd;
                    if(oldpasswd.length()>pwd_len) {string unuse;getline(cin,unuse,'\r'); delete streamstr,throw Error();}
                    if(newpasswd.length()>uid_len)  delete streamstr,throw Error();
                    streamstr->push(oldpasswd);
                    streamstr->push(newpasswd);
                    //strncpy(userid.c_str(),todo.c_str(),pos);
                    return streamstr;
                }
            }
            case 7:{//select
                if(userpri<3){string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string ISBN;
                cin>>ISBN;
                if(ISBN.length()>ISBN_len) delete streamstr,throw Error();
                streamstr->push(ISBN);
                return streamstr;
            }
            case 8:{//modify
                if(userpri<3)  {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string todo;
                char name[MAXNBL];
                char ISBN[MAXNBL];
                char author[MAXNBL];
                char price[20];
                string keyword[20];
                int numofkey=0;
                cin.get();
                getline(cin,todo,'\r');
                int l=todo.length();
                todo[l]='\r';
                for(int i=0;i<l;i++){
                    if(todo[i]=='-'){
                        if(todo[i+1]=='I'){
                            i+=6;
                            int start=i;
                            while(todo[i]!=' '&&todo[i]!='\r')  ISBN[i-start]=todo[i],i++;
                            ISBN[i-start]='\0';
                            if(strlen(ISBN)>ISBN_len) delete streamstr,throw Error();
                            streamstr->push("I");
                            streamstr->push(ISBN);
                        }
                        else if(todo[i+1]=='a'){
                            i+=9;int start=i;
                            while(todo[i]!='"'&&todo[i]!='\r'&&todo[i]!=' ')  author[i-start]=todo[i],i++;
                            if(strlen(author)>au_len) delete streamstr,throw Error();
                            author[i-start]='\0';
                            streamstr->push("a");
                            streamstr->push(author);
                        }
                        else if(todo[i+1]=='k'){
                            i+=10;
                            int length=0;
                            int start=i;
                            string akey="";
                            while(todo[i]!='"'&&todo[i]!=' '&&todo[i]!='\r') {
                                akey+=todo[i];
                                i++,length++;
                                if(todo[i]=='|')keyword[numofkey]=akey,akey="",i++,length++,numofkey++,start=i;
                            }
                            if(length>keyw_len) delete streamstr,throw Error();
                            keyword[numofkey]=akey;
                            numofkey++;
                            streamstr->push("k");
                            streamstr->push(to_string(numofkey));
                            for(int j=0;j<numofkey;j++)  streamstr->push(keyword[j]);
                        }
                        else if(todo[i+1]=='n'){
                            i+=7;
                            int start=i;
                            while(todo[i]!='"'&&todo[i]!='\r'&&todo[i]!=' ') name[i-start]=todo[i],i++;
                            name[i-start]='\0';
                            if(strlen(name)>name_lem) delete streamstr,throw Error();
                            streamstr->push("n");
                            streamstr->push(name);
                        }
                        else if(todo[i+1]=='p'){
                            i+=7;
                            int start=i;
                            while(todo[i]!=' '&&todo[i]!='\r')  price[i-start]=todo[i],i++;
                            price[i-start]='\0';
                            streamstr->push("p");
                            streamstr->push(price);
                        }
                    }
                }
                return streamstr;
            }
            case 9:{//import
                if(userpri<3)  {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string strnum;
                string strprice;
                //double price;
               cin>>strnum;
               //double price;
               cin>>strprice;
                streamstr->push(strnum);
                streamstr->push((strprice));
                //streamstr->push(to_string(price));
                return streamstr;
            }
            case 10:{//useradd
                if(userpri<3) {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string todo;
                cin.get();
                getline(cin,todo,'\r');
                string todo2;
                string todo3;
                char userid[MAXNUL];
                char ctodo2[300];
                char ctodo3[200];
                int pos=todo.find(' ');
                if(pos==todo.npos) throw Error();
                strncpy(userid,todo.c_str(),pos);
                userid[pos]='\0';
                if(strlen(userid)>uid_len)  delete streamstr,throw Error();
                strcpy(ctodo2,todo.c_str()+pos+1);
                todo2=ctodo2;
                char passwd[100];
                pos=todo2.find(' ');
                if(pos==todo2.npos) throw Error();
                strncpy(passwd,todo2.c_str(),pos);
                passwd[pos]='\0';
                if(strlen(passwd)>pwd_len)  delete streamstr,throw Error();
                strcpy(ctodo3,todo2.c_str()+pos+1);
                todo3=ctodo3;
                char pri[20];
                char name[100];
                pos=todo3.find(' ');
                if(pos==todo3.npos) throw Error();
                strncpy(pri,todo3.c_str(),pos);
                pri[pos]='\0';
                strcpy(name,todo3.c_str()+pos+1);
                string strname;
                strname=name;
                pos=strname.find(' ');
                if(pos!=strname.npos)  strncpy(name,strname.c_str(),pos);
                if(strlen(name)>name_lem)  delete streamstr,throw Error();
                if(strlen(pri)!=1) throw Error();
                streamstr->push(userid);
                streamstr->push(passwd);
                streamstr->push(pri);
                streamstr->push(name);
                return streamstr;
            }
            case 11:{//delete
                if(userpri<7) {string unuse;getline(cin,unuse,'\r');delete streamstr,throw Error();}
                string userid;
               cin>>userid;
                if(userid.length()>uid_len) delete streamstr,throw Error();
                streamstr->push(userid);
                return streamstr;
            }
            case 0:return nullptr;
        }
    }
    void login(user& u){
        slmainpos=-1;
        userstack.push(pair<user,int>(u,slmainpos));
        string userid=u.userid;
     //   cout<<"login:"<<u.userid<<' '<<slmainpos<<endl;
     //   cout<<userid<<endl;
        if(!count.count(userid)){
            count.insert(pair<string,int>(userid,1));
         //   cout<<"?"<<endl;
        }
        else{
            pair<string,int>p=*(count.find(userid));
            count.erase(userid);
            p.second++;
            count.insert(p);
        }
        userpri=u.priviledge;
     //  cout<<"userpri:"<<userpri<<endl;
      //  cout<<u.priviledge<<endl;
    };
    void logout(){
        pair<user,int>p=userstack.top();
        userstack.pop();
        //cout<<p.first.userid<<endl;
       // cout<<p.second<<endl;
        //cout<<count.count(p.first.userid)
        pair<string,int>p2=*(count.find(p.first.userid));
        count.erase(p2.first);
        p2.second--;
        if(p2.second>0) count.insert(p2);
        p=userstack.top();
     //   cout<<p.first.userid<<' '<<p.second<<endl;
        slmainpos=p.second;
        userpri=p.first.priviledge;
    };
    bool is_online(string userid){
        if(count.count(userid)) return 1;
        else 0;
    }
    void showfi(int time){
        fi.show(time);
    }
    void insert(double money) {
        fi.insertf(money);
    }
    int getfin(){
        return fi.getsize();
    }
    void setpos(int pos){
        pair<user,int>p=userstack.top();
        slmainpos=pos;
        p.second=pos;
        userstack.pop();
        userstack.push(p);
        //cout<<"setpos"<<slmainpos<<endl;
    }
    int getpos(){
        return slmainpos;
    }
    int getab(){
        return numofboall;
    }
    int newbook(){
        return  (++numofboall);
    }
    int newuser(){
    //    cout<<numofuall<<endl;

        return  (++numofuall);
    }
};
#endif //UNTITLED5_HANDLE_H
