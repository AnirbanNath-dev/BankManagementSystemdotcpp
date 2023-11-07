
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string name , prof, email, isEmploy, pin , nowCreate;
int age, ph_no;



void saveUserDetails(const string& fname, const string& fpassword,int phonenumber , int fage, const string& femail , string work) {
    ofstream userFile("user_details.txt", ios::app);
    if (userFile.is_open()) {
        userFile << fname << ' ' << fpassword << ' '<< phonenumber << " " << fage << ' ' << femail << ' '<< work << endl;
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
        
        bool found = false;

        while (userFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf ) {
            if (name == storedName) {
                found = true;
                cout << "User Details for " << name << ":" << endl;
                cout << "Password: " << storedPassword << endl;
                cout << "Phone number : " << storedPhoneNo << endl;
                cout << "Age: " << storedAge << endl;
                cout << "Email: " << storedEmail << endl;
                cout << "Profession : " <<  storedProf << endl;
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

        while (userFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf) {
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
        cout<<"You are logged in as \e[1m"<<name<<"\e[0m"<<endl<<endl;
        cout<<"\e[1mMenu:\e[0m"<<endl;
        cout<<"\e[1m^^^^\e[0m"<<endl<<endl;
        cout<<"1. Show user details"<<endl;
        cout<<"2. Deposit Money"<<endl;
        cout<<"3. Withdraw Money"<<endl;
        cout<<"4. Show Balance"<<endl;
        cout<<"5. Close Account"<<endl;
        cout<<"6. Exit"<<endl;
    }
    else if(isRegistered == "not avail"){

        cout<<"Account Not Found"<<endl;
        cout<<"Do you want to create a new account?(Y/N) ";
        cin>>nowCreate;
        if(nowCreate == "Y" || nowCreate == "y"){}
        cout<<"Enter your full name: ";
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

        saveUserDetails(name , pin, ph_no , age , email , prof );
        cout<<"\nYour account is successfully created....";

    }
    

    return 0;
}














