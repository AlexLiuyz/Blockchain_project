#include <cstring>
#include <iostream>
#include<iomanip>
#include "SHA1.cpp"
using namespace std;

struct identity{
    char user_name[100];
    char ID_number[100];
    char age[100];
    char bankaccount[100];
    char bankpassword[90];
    identity *next=NULL;
    char hash_value[41];
};//to make a struct


void menu();
void check_menu();
char* hash_string(char*,char*);
char* hash_identity(identity*);
struct identity* add_information(identity*);
int check_information(identity*);
int check_with_number(identity*);
int check_with_hash_value(identity*);
int check_with_ID_number(identity*);
void print_information(identity*);
int check_integrity(identity*);


void check_menu(){
    cout<<"*******************************"<<endl;
    cout<<"*    please select the way    *"<<endl;
    cout<<"*******************************"<<endl;
    cout<<"*1.check with block number    *"<<endl;
    cout<<"*2.check with hash value      *"<<endl;
    cout<<"*3.check with ID_number       *"<<endl;
    cout<<"*4.click any other key to quit*"<<endl;
    cout<<"*******************************"<<endl;
}//to display the choices


int check_integrity(identity *head){
    if(head->next==NULL){
        cout<<"please add some block first"<<endl;
        return 0;
    }
    identity *monitor=new identity;
    monitor=head;
    int num=0;
    while((monitor->next)->next!=NULL){
        if(strcmp(hash_identity(monitor),(monitor->next)->hash_value)!=0){
            cout<<"it have been invaded at"<<num<<"block"<<endl;
            return 0;
        }
        monitor=monitor->next;
        num++;
    }
    cout<<"No thing happened, fine."<<endl;
}


void print_information(identity* monitor){
    cout<<std::left<<setw(15)<<"user name:"<<monitor->user_name<<endl;
    cout<<std::left<<setw(15)<<"ID number:"<<monitor->ID_number<<endl;
    cout<<std::left<<setw(15)<<"age:"<<monitor->age<<endl;
    cout<<std::left<<setw(15)<<"bank account:"<<monitor->bankaccount<<endl;
    cout<<std::left<<setw(15)<<"password:"<<monitor->bankpassword<<endl;
    system("pause");
    system("cls");
}//to out put the information(we don't display the hash value for safety issue)


void menu(){
    cout<<"**************************************"<<endl;
    cout<<"*Welcome to bankaccount saving center*"<<endl;
    cout<<"**************************************"<<endl;
    cout<<"*      please select ur choice:      *"<<endl;
    cout<<"*      0.u want to quit              *"<<endl;
    cout<<"*      1.add ur information          *"<<endl;
    cout<<"*      2.check information           *"<<endl;
    cout<<"*      3.check the integrity         *"<<endl;
    cout<<"*      4.clean the screen            *"<<endl;
    cout<<"**************************************"<<endl;
}//output the menu for the main function


char* hash_string(char* s,char* hash){
	string input(s);
	SHA1 checksum;
	checksum.update(input);
	strcpy(hash, checksum.final().c_str());
	return hash;
}//to hash a char array


char* hash_identity(identity *point){
    char dest[531];
    strcpy(dest,point->user_name);
    strcat(dest,point->ID_number);
    strcat(dest,point->age);
    strcat(dest,point->bankaccount);
    strcat(dest,point->bankpassword);
    strcat(dest,point->hash_value);
    char hash[41];
    char* m=hash_string(dest,hash);
    return m;
}//to hash a whole block


identity* add_information(identity* head){
    identity* newpoint=new identity;  
    head->next=newpoint;
    cout<<"please enter ur username: "<<endl;
    cin.getline(head->user_name,41);
    cout<<"please enter ur ID: "<<endl;
    cin.getline(head->ID_number,100);
    cout<<"Please enter ur age: "<<endl;
    cin.getline(head->age,100);
    cout<<"Please enter ur account: "<<endl;
    cin.getline(head->bankaccount,100);
    cout<<"please enter ur password:"<<endl;
    cin.getline(head->bankpassword,90);
    strncpy(newpoint->hash_value,hash_identity(head),41);
    cout<<"the hash value is: "<<newpoint->hash_value<<"(please remember it and keep secret)"<<endl;
    head=head->next;
    return head;
}//to input the information


int check_with_number(identity* head){
    int block_number;
    cout<<"please enter the block number(start from 0)"<<endl;
    cin>>block_number;
    int num=0;
    identity* monitor=new identity;
    monitor=head;
    while((monitor->next!=NULL)&&(num<block_number)){
        monitor=monitor->next;
        num++;
    }
    if((monitor->next==NULL)||(block_number<0)){
        cout<<"out of range"<<endl;
        system("pause");
        return 0;
    }
    else{
        print_information(monitor);
    }
}//to let the user to check with the lock number


int check_with_hash_value(identity* head){
    char hash[41];
    cout<<"please enter the hash value:"<<endl;
    cin>>hash;
    cin.ignore();
    identity* monitor=new identity;
    monitor=head;
    while((strcmp((monitor->next)->hash_value,hash)!=0)&&((monitor->next)->next!=NULL)){
        if((monitor->next)->next!=NULL){
            monitor=monitor->next;
        }
    }
    if(strcmp((monitor->next)->hash_value,hash)!=0){
        cout<<"no such block!!!"<<endl;
        system("pause");
        return 0;
    }
    if(strcmp((monitor->next)->hash_value,hash)==0){
        print_information(monitor);
    }
}//check with hash value


int check_with_ID_number(identity* head){
    char num[100];
    cout<<"please enter the ID number:"<<endl;
    cin>>num;
    identity* monitor=new identity;
    monitor=head;
    while((strcmp(monitor->ID_number,num)!=0)&&(monitor->next!=NULL)){
        monitor=monitor->next;
    }
    if(monitor->next==NULL){
        cout<<"No such an ID!!!"<<endl;
        system("pause");
        return 0;
    }
    if(strcmp(monitor->ID_number,num)==0){
        print_information(monitor);
    }
}//check with ID number


int check_information(identity* head){
    if(head->next==NULL){
        cout<<"you haven't input any blocks yet"<<endl;
        system("pause");
        return 0;
    }
    check_menu();
    while(true){
        int condition;
        cin>>condition;
        switch(condition){
            case 1:
                check_with_number(head);
                break;
            case 2:
                check_with_hash_value(head);
                break;
            case 3:
                check_with_ID_number(head);
                break;
            default:
                system("pause");
                return 0;
        }
        check_menu();
    }
}//to order three choices for the user to check the information


int main() {
    identity* head=new identity;
    head->next=NULL;
    identity* first=head;
    int choice;
    while(true){
        menu();
        cin>>choice;
        cin.ignore();
        switch(choice){
            case 0:
                cout<<"Thanks for using our bank account center, have a nice day ^_^"<<endl;
                exit(0);
            case 1:
                first=add_information(first);
                system("pause");
                break;
            case 2:
                check_information(head);
                break;
            case 3:
                check_integrity(head);
                system("pause");
                break;
            case 4:
                fflush(stdin);
                system("cls");
                break;
            default:
                cout<<"WRONG MESSAGE Please try again"<<endl;
        }
    }         
}
