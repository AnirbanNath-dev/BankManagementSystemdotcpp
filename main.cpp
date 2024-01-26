#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<ctime>

using namespace std;

string name , prof, email, isEmploy, pin , nowCreate;
int age;
double ph_no;
float balance = 100;

class Bank{

    private:
    string u_name;
    string choice;
    float dep_money, with_money;

    void deleteUserByName(const string& x);
    void findUserDetailsByName(const string& x);
    void deposit();
    void balance();
    void withdraw();
    void close_acc();
    void appendBalanceForUser(const string& x, const float& y);
    void sleep(float seconds){
        clock_t startClock = clock();
        float secondsAhead = seconds * CLOCKS_PER_SEC;
        while(clock() < startClock+secondsAhead);
        return;
    }

    public:
    Bank(string user){
        u_name = user;
    }
    

    void menu(){
        
        cout<<"You are logged in as \e[1;36m"<<u_name<<"\e[0m"<<endl<<endl;
        
        while(true){
            sleep(1);
            cout<<"\n\e[1mMenu:\e[0m"<<endl;
            cout<<"\e[1m^^^^\e[0m"<<endl<<endl;
            sleep(0.7);
            cout<<"1. \033[35mShow user details\033[0m"<<endl;
            cout<<"2. \033[35mDeposit Money\033[0m"<<endl;
            cout<<"3. \033[35mWithdraw Money\033[0m"<<endl;
            cout<<"4. \033[35mShow Balance\033[0m"<<endl;
            cout<<"5. \033[35mClose Account\033[0m"<<endl;
            cout<<"6. \033[35mExit\033[0m"<<endl<<endl;

            cout<<"> Enter choice: ";
            cin>>choice;
            cout<<endl;
            if(choice == "1"){
                findUserDetailsByName(u_name);
                continue;
            }
            else if(choice == "2"){
                balance();
                deposit();
                continue;
            }
            else if(choice == "3"){
                balance();
                withdraw();
                continue;
            }
            else if(choice == "4"){
                balance();
                cout<< "Your current balance: Rs.\e[1m" << ::balance << "\e[0m" << endl;
                continue;
            }
            else if(choice == "5"){
                string opinion;
                while(true){
                    cout<<"\e[1m>\e[0m Are you sure you want to close account ?(Y/N) ";
                    cin>>opinion;
                    cout<<endl;
                    if(opinion == "Y" || opinion == "y"){
                        close_acc();
                        break;
                    }
                    else if(opinion == "N" || opinion == "n"){
                        cout<<"\033[32mDeletion is terminated \033[0m!";
                        break;
                    }
                    else{
                        cout<<"\033[31Request declined !\033[0m";
                        continue;
                    }
                }
                
                cout<<"\n\033[32mThanks for choosing our services\033[0m \e[1m!\e[0m"<<endl<<endl;
                break;
            }
            else if(choice == "6"){
                sleep(1);
                cout<<"\033[32mHope you like our service\033[0m \e[1m!\e[0m \033[32mCome back again\033[0m"<<endl<<endl;
                break;
            }
            else{
                cout<<"\n\033[31mInvalid option !\033[0m"<<endl<<endl;
                continue;
            } 
        }
    }
    
    
};

void Bank::deleteUserByName(const string& username) {
    
        ifstream inputFile("user_details.txt");
        ofstream tempFile("temp_file.txt");
        if (inputFile.is_open() && tempFile.is_open()) {
            string storedName, storedEmail, storedProf, storedPassword;
            int storedPhoneNo, storedAge;
            float storedMoney;
            bool found = false;

            while (inputFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf >> storedMoney) {
                if (username == storedName) {
                    found = true;
                } else {
                    tempFile << storedName << ' ' << storedPassword << ' '<< storedPhoneNo << " " << storedAge << ' ' << storedEmail << ' '<< storedProf << " " << storedMoney <<endl;
                }
            }

            inputFile.close();
            tempFile.close();

            if (found) {
                remove("user_details.txt");
                rename("temp_file.txt", "user_details.txt");
                cout<<endl;
                cout<<"\033[33mDeletion of account is in progress.......\033[0m";
                sleep(2);
                cout << "\n\nAccount by the name \e[1m" << storedName << "\e[0m has been deleted succesfully." << endl;
                sleep(0.9);
            } else {
                remove("temp_file.txt");
                cout << "Account by the name \e[1m" << storedName << "\e[0m is not found." << endl;
            }
        } else {
            cout << "Error: Could not open the file for reading or writing." << endl;
        }
    }


void Bank::deposit(){
    cout<<"> Enter the amount to be deposited: ";
    cin>>dep_money;
    appendBalanceForUser(u_name , dep_money);
    ::balance += dep_money;
    
    cout<<"Money deposited: Rs.\e[1m"<<dep_money<<"\e[0m"<<endl;
    
}

void Bank::withdraw(){
    cout<<"> Enter the amount to be withdrawn: ";
    cin>>with_money;

    

    if(::balance >= with_money){
        ::balance -= with_money;
        appendBalanceForUser(u_name , -with_money);
        cout<<"Money withdrawn: Rs.\e[1m"<<with_money<<"\e[0m"<<endl;

    }
    else{
        cout<<"Insufficient Money"<<endl;
    }
    
    
}



void Bank::balance() {
    ifstream userFile("user_details.txt");
    if (userFile.is_open()) {
        string storedName, storedPassword, storedEmail, storedProf;
        int storedPhoneNo, storedAge;
        float storedMoney;
        bool found = false;

        while (userFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf >> storedMoney) {
            if (u_name == storedName) {
                found = true;
                ::balance = storedMoney; 
                
                break;
            }
        }

        userFile.close();

        if (!found) {
            cout << "User with name " << u_name << " not found." << endl;
        }
    } else {
        cout << "Error: Could not open the file for reading." << endl;
    }
}



void Bank::close_acc(){

    deleteUserByName(u_name);
}



void Bank::findUserDetailsByName(const string& name) {
    ifstream userFile("user_details.txt");
    if (userFile.is_open()) {
        string storedName , storedEmail , storedProf , storedPassword;
        int storedPhoneNo , storedAge;
        float storedMoney ;
        bool found = false;

        while (userFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf >> storedMoney) {
            if (name == storedName) {
                char dump;
                found = true;
                cout << "\e[1mUser Details\e[0m: "<<endl; 
                cout<<"\e[1m^^^^^^^^^^^^\e[0m"<<endl<<endl;
                cout << "\e[1m>\e[0m Name: \033[33m" << name <<"\033[0m"<<  endl;
                cout << "\e[1m>\e[0m Password: \033[33m" << storedPassword <<"\033[0m"<< endl;
                cout << "\e[1m>\e[0m Phone number : \033[33m" << storedPhoneNo <<"\033[0m"<< endl;
                cout << "\e[1m>\e[0m Age: \033[33m" << storedAge <<"\033[0m"<< endl;
                cout << "\e[1m>\e[0m Email: \033[33m" << storedEmail <<"\033[0m"<< endl;
                cout << "\e[1m>\e[0m Profession : \033[33m" <<  storedProf <<"\033[0m"<< endl;
                cout << "\e[1m>\e[0m Balance: \033[33m" << storedMoney <<"\033[0m"<< endl<<endl;
                cout<<"Enter \e[1mAny Key\e[0m to continue: ";
                cin>>dump;
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


void Bank::appendBalanceForUser(const string& name, const float& addedBalance) {
        ifstream inputFile("user_details.txt");
        ofstream tempFile("temp_file.txt");
        if (inputFile.is_open() && tempFile.is_open()) {
            string storedName, storedPassword, storedEmail, storedProf;
            int storedPhoneNo, storedAge;
            float storedMoney;
            bool found = false;

            while (inputFile >> storedName >> storedPassword >> storedPhoneNo >> storedAge >> storedEmail >> storedProf >> storedMoney) {
                if (name == storedName) {
                    found = true;
                    storedMoney += addedBalance;
                    tempFile << storedName << ' ' << storedPassword << ' ' << storedPhoneNo << ' ' << storedAge << ' ' << storedEmail << ' ' << storedProf << ' ' << storedMoney << endl;
                } else {
                    tempFile << storedName << ' ' << storedPassword << ' ' << storedPhoneNo << ' ' << storedAge << ' ' << storedEmail << ' ' << storedProf << ' ' << storedMoney << endl;
                }
            }

            inputFile.close();
            tempFile.close();

            if (found) {
                remove("user_details.txt");
                rename("temp_file.txt", "user_details.txt");
                
            } else {
                remove("temp_file.txt");
                cout << "User " << name << " not found." << endl;
            }
        } else {
            cout << "Error: Could not open the file for reading or writing." << endl;
        }
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




void sleep(float seconds){
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    while(clock() < startClock+secondsAhead);
    return;
}

int main(){


    cout<<"\n\n\t\t\e[1m=====================\e[0m";
    cout<<"\n\t\t\e[1;34mWELCOME TO ANBIT BANK\e[0m";
    cout<<"\n\t\t\e[1m=====================\e[0m"<<endl<<endl;

    cout<<"\e[1mLogin\e[0m"<<endl;
    cout<<"\e[1m~~~~~\e[0m"<<endl;
    sleep(0.7);
    cout<<"> Enter your name: ";
    cin>>name;
    sleep(0.5);
    cout<<"> Enter your pin: ";
    cin>>pin;
    sleep(0.5);
    cout<<endl;

    
    

    string isRegistered = isUserRegistered(name , pin);

    if(isRegistered == "avail"){
        Bank Anbit1(name);
        Anbit1.menu();
    }
    
    else if(isRegistered == "not avail"){

        cout<<"\033[31mAccount Not Found \e[1m:(\e[0m\033[0m"<<endl<<endl;
        sleep(0.8);
        while(true){
            cout<<"Do you want to create a new account?(Y/N) ";
            cin>>nowCreate;
            if(nowCreate == "Y" || nowCreate == "y"){
                cout<<"\n> Enter your name: ";
                cin>>name;
                sleep(0.5);
                cout<<"> Enter your age: ";
                cin>>age;
                sleep(0.5);

                cout<<"> Enter your phone number: ";
                cin>>ph_no;
                
                sleep(0.5);

                cout << "> Enter your email address: ";
                cin>>email;


                sleep(0.5);
                cout<<"> Are you employed ?(Y/N): ";
                
                cin>>isEmploy;
                if(isEmploy == "y" || isEmploy == "Y"){
                    
                    sleep(0.5);
                    cout<<"> Enter you profession: ";
                    cin>>prof;

                }
                else if(isEmploy == "n" || isEmploy == "N"){
                    sleep(0.5);
                    prof = "Unemployed";

                }
                cout<<"> Enter a pin for your account (0-9): ";
                cin>>pin;
                cout<<endl;
                cout<<"\033[0;33mProcessing.....\033[0m"<<endl;  //Yellow color used
                saveUserDetails(name , pin, ph_no , age , email , prof , balance);
                sleep(2);
                cout<<"\n\033[1;32mYour account is successfully created....\033[0m"<<endl<<endl;
                sleep(1);
                Bank Anbit2(name);
                Anbit2.menu();
                break;

            }
            else if(nowCreate == "N" || nowCreate == "n"){
                cout<<"\n\033[32mThank you\033[0m \e[1m!\e[0m \033[32mCome back again\033[0m"<<endl<<endl;
                break;
            }
            else{
                cout<<"\n\033[31mInvalid Option\033[0m"<<endl;
                sleep(0.8);
                cout<<"\033[33mTry again....\033[0m"<<endl<<endl;
                sleep(0.8);
                continue;
            }
        }
    }

    return 0;
}
