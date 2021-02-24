#include "bookstore.h"
#include <queue>
#include "user.h"
class End{};
int main(){
    int line=0;
    Boss me;
 //   in.open("in.txt",ios::in);
  //  out.open("out.txt",ios::out);
    operating.initial(aofb.c_str(),aofu.c_str(),ISBNfile.c_str(),
                      namefile.c_str(),keywordfile.c_str(),authorfile.c_str(),
                      userfile.c_str(),finance.c_str(),ISBNpool.c_str(),
                      namepool.c_str(),keywordpool.c_str(),authorpool.c_str(),userpool.c_str()
                      );

    while(!cin.eof()){
    string order;
  //  cout<<operating.getpri()<<endl;
    int op;
    char flag;
    cin.get(flag);
    if(flag=='\n'){
        cin.get(flag);
        if(flag==EOF) break;
        else cin.putback(flag);}
    else cin.putback(flag);
    cin>>order;
    if(cin.eof()) break;
    //if(cin.tellg()) break;
 // out<<order<<' '<<line;
/* fstream file;
  file.open(aofb,ios::in|ios::out|ios::binary);
  file.seekg(sizeof(int)+9*sizeof(book));
  book tmp;
  file.read(cd(tmp),sizeof(book));
  showbook(tmp);
  file.close();
//ISBN.showall();*/
    line++;
   queue<string>* todos=nullptr;
        try{
    op=operating.judge(order);
 // cout<<"?"<<endl;
    todos=operating.is_correct(op);
    switch (op){
        case 1:{
            me.su(todos);
            break;
        }
        case 2:{
            me.reg(todos);
            break;
        }
        case 3:{
            me.logout();
            break;
        }
        case 4:{
            me.buy(todos);
            break;
        }
        case 5:{
            me.show(todos);
            break;
        }
        case 6:{
            me.repasswd(todos);
            break;
        }
        case 7:{
            me.select(todos);
            break;
        }
        case 8:{
            me.modify(todos);
            break;
        }
        case 9:{
            me.import(todos);
            break;
        }
        case 10:{
            me.useradd(todos);
            break;
        }
        case 11:{
            me.Delete(todos);
            break;
        }
        case 0:{
            delete todos;
            return 0;
        }
    }
    //showalluser();
    //showallbook();
  //  cout<<"adadaada"<<endl;
  //  cout<<"???"<<endl;
        }catch(Error){
           // cout<<"?"<<endl;
            cout<<"Invalid"<<endl;}
        catch(End){break;}
    }
   // in.close();
   // out.close();
}