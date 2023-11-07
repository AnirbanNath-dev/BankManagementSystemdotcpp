#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string name , prof, email, isEmploy, pin , nowCreate;
int age, ph_no;
float balance=0, dep_money, with_money;

class Bank{

    private:
    string u_name , closeAccName , closeAccPin;

    public:
    Bank(string user){
        u_name = user;
    }
    void menu(){
        cout<<"You are logged in as \e[1m"<<u_name<<"\e[0m"<<endl<<endl;
        cout<<"\e[1mMenu:\e[0m"<<endl;
        cout<<"\e[1m^^^^\e[0m"<<endl<<endl;
        cout<<"1. Show user details"<<endl;
        cout<<"2. Deposit Money"<<endl;
        cout<<"3. Withdraw Money"<<endl;
        cout<<"4. Show Balance"<<endl;
        cout<<"5. Close Account"<<endl;
        cout<<"6. Exit"<<endl;
    }
    void deposit();
    void balance();
    void withdraw();
    void close_acc();
    
};

void Bank::deposit(){
    cout<<"Enter the amount to be deposited: ";
    cin>>dep_money;

    ::balance += dep_money;
    cout<<"Money deposited: Rs.\e[1m"<<dep_money<<"\e[0m"<<endl;
    cout<<"Current Balance: Rs.\e[1m"<<::balance<<"\e[0m"<<endl;
}

void Bank::withdraw(){
    cout<<"Enter the amount to be withdrawn: ";
    cin>>with_money;
    if(::balance >= with_money){
        ::balance -= with_money;
    }
    else{
        cout<<"Insufficient Money"<<endl;
    }
    cout<<"Money withdrawn: Rs.\e[1m"<<with_money<<"\e[0m"<<endl;
    cout<<"Current Balance: Rs.\e[1m"<<::balance<<"\e[0m"<<endl;
}

void Bank::balance(){
    cout<<"Your current balance: Rs.\e[1m"<<::balance<<"\e[0m"<<endl;
}


void Bank::close_acc(){
    cout<<"\e[1mEnter the following information for confirmation-\e[0m ";
    cout<<"Enter name: ";
    cin>>closeAccName;
    cout<<"Enter pin: ";
    cin>>closeAccPin;



}



void saveUserDetails(const string& fname, const string& fpassword,int phonenumber , int fage, const string& femail , string work ,float money) {
    ofstream userFile("user_details.txt", ios::app);
    if (userFile.is_open()) {
        userFile << fname << ' ' << fpassword << ' '<< phonenumber << " " << fage << ' ' << femail << ' '<< work << " " << money <<endl;
        userFile.close();
        
    } else {
        cout << "Error: Could not open the file for writing." << endl;
    }
}



void findUserDetailsByName(const string& name) {
    ifstream userFile("user_details.txt");
    if (userFile.is_open()) {
        string storedName , storedEmail , storedProf , storedPassword;
        int storedPhoneNo , storedAge;
        float storedMoney ;
        bool found = false;

        while (userFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf >> storedMoney) {
            if (name == storedName) {
                found = true;
                cout << "\e[1mUser Details\e[0m: "; 
                cout<<"\e[1m^^^^^^^^^^^^\e[0m"<<endl<<endl;
                cout << "Name" << name <<  endl;
                cout << "Password: " << storedPassword << endl;
                cout << "Phone number : " << storedPhoneNo << endl;
                cout << "Age: " << storedAge << endl;
                cout << "Email: " << storedEmail << endl;
                cout << "Profession : " <<  storedProf << endl;
                cout << "Balance: " << storedMoney << endl;
                break;
            }
        }

        userFile.close();

        if (!found) {
            cout << "User with name " << name << " not found." << endl;
        }
    } else {
        cout << "Error: Could not open the file for reading." << endl;
    }
}


string isUserRegistered(const string& name, const string& password) {
    ifstream userFile("user_details.txt");
    if (userFile.is_open()) {
        string storedName, storedEmail, storedProf, storedPassword;
        int storedPhoneNo, storedAge;
        float storedMoney;

        while (userFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf >> storedMoney) {
            if (name == storedName && password == storedPassword) {
                userFile.close();
                return "avail";
            }
        }
        userFile.close();
    }

    return "not avail";
}


int main(){


    cout<<"\n\n\t\t=====================";
    cout<<"\n\t\t\e[1mWELCOME TO ANBIT BANK\e[0m";
    cout<<"\n\t\t====================="<<endl<<endl;


    cout<<"\e[1mLogin\e[0m"<<endl;
    cout<<"\e[1m^^^^^\e[0m"<<endl;
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter your pin: ";
    cin>>pin;
    cout<<endl;

    
    

    string isRegistered = isUserRegistered(name , pin);

    if(isRegistered == "avail"){
        Bank Anbit1(name);
        Anbit1.menu();
    }
    
    else if(isRegistered == "not avail"){

        cout<<"Account Not Found"<<endl;
        while(true){
            cout<<"Do you want to create a new account?(Y/N) ";
            cin>>nowCreate;
            if(nowCreate == "Y" || nowCreate == "y"){
                cout<<"Enter your name: ";
                cin>>name;
                cout<<"\nEnter your age: ";
                cin>>age;
                cout<<"\nEnter your phone number: ";
                cin>>ph_no;
                cout<<"\nEnter your email address: ";
                cin>>email;
                cout<<"\nAre you employed ?(Y/N): ";
                cin>>isEmploy;
                if(isEmploy == "y" || isEmploy == "Y"){
                
                    cout<<"Enter you profession: ";
                    cin>>prof;

                }
                else if(isEmploy == "n" || isEmploy == "N"){
                
                    prof = "Unemployed";

                }
                cout<<"\nEnter a pin for your account (0-9): ";
                cin>>pin;

                saveUserDetails(name , pin, ph_no , age , email , prof , balance);
                cout<<"\nYour account is successfully created...."<<endl<<endl;

                Bank Anbit2(name);
                Anbit2.menu();
                break;

            }
            else if(nowCreate == "N" || nowCreate == "n"){
                cout<<"Thank you! Come back again"<<endl;
                break;
            }
            else{
                cout<<"Invalid Option"<<endl;
                cout<<"Try again"<<endl<<endl<<endl;
                continue;
            }
        }
    }

    return 0;
}














