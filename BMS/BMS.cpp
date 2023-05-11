#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>

using namespace std;

class Bank_Account {
    int account_number;
    char name[50];
    char type;
    int money_deposit;
public:
    void report() const;
    int retdeposit() {
        return money_deposit;
    }
    void dep(int amount) {
        money_deposit += amount;
    }
    void draw(int amount) {
        money_deposit -= amount;
    }
    int retacno() {
        return account_number;
    }
    void create_account();
    void display_account();
    void modify();
};

void Bank_Account::modify() {
    cout << "\t Account number: " << account_number << endl;
    cout << "\t Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\t Modify Account Type: ";
    cin >> type;
    type = toupper(type);
    cout << "\t Modify Account Balance: ";
    cin >> money_deposit;
}
void Bank_Account::report() const {
    cout << account_number << setw(10) << " " << name << setw(10) << " " << type << setw(6) << money_deposit << endl;
}
void Bank_Account::create_account() {
    system("cls");
    cout << "\t Enter the account number: ";
    cin >> account_number;
    cout << "\t Enter the name of the account holder: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\t Enter the type of account (C/S): ";
    cin >> type;
    type = toupper(type);
    cout << "\t Enter the initial amount (>=500 for Savings and >= 1000 for current): ";
    cin >> money_deposit;
    cout << endl;
    cout << "\t Account Created";
    cout << endl;
}
void Bank_Account::display_account() {
    system("cls");
    cout << "\t Bank Account Number: " << account_number << endl;
    cout << "\t Account Holder Name: " << name << endl;
    cout << "\t Type of Account: " << type << endl;
    cout << "\t Balance amount: " << money_deposit << endl;
}
void write_account();
void display_details(int n);
void delete_account(int n);
void display_all();
void updation_bank_account(int n);
void money_deposit_withdraw(int n, int option);

int main() {
    char ch;
    int num;
    do {
        cout << "\t\t----------------------------------------";
        cout << "\t\t| Welcome to the Bank Managment System |";
        cout << "\t\t----------------------------------------";
        
        cout << endl;
        cout << "\t --- Main Menu ---";
        cout << endl;
        cout << "\t 1. Create Account" << endl;
        cout << "\t 2. Deposit Money" << endl;
        cout << "\t 3. Withdraw Money" << endl;
        cout << "\t 4. Balance Enquiry" << endl;
        cout << "\t 5. All Account Holder List" << endl;
        cout << "\t 6. Close an Account" << endl;
        cout << "\t 7. Modify an Account" << endl;
        cout << "\t 8. Exit" << endl;
        cout << endl;

        cout << "\t Enter your choice (1-8): ";
        cin >> ch;
        
        switch (ch) {
            case '1':
                write_account();
                break;
            case '2':
                system("cls");
                cout << "\t Enter the account number: ";
                cin >> num;
                money_deposit_withdraw(num, 1); // deposit function
                break;
            case '3':
                system("cls");
                cout << "\t Enter the account number: ";
                cin >> num;
                money_deposit_withdraw(num, 2); // withdraw function
                break;
            case '4':
                system("cls");
                cout << "\t Enter the account number: ";
                cin >> num;
                display_details(num); // balance enquiry function
                break;
            case '5':
                display_all(); 
                break;
            case '6':
                system("cls");
                cout << "\t Enter the account number: ";
                cin >> num;
                delete_account(num); // close account function
                break;
            case '7':
                system("cls");
                cout << "\t Enter the account number: ";
                cin >> num;
                updation_bank_account(num); // modify account function
                break;
            case '8':
                cout << "\t Thanks for using the Bank Managment System" << endl;
                break;
            default:
                cout << "\t Invalid Choice";
                break;
        }
        cin.ignore();
        cin.get();
    } while (ch!= '8');
    return 0;
    // Bank_Account account;
    // account.create_account();
    // account.display_account();
    // return 0;
}

void write_account() {
    Bank_Account account;
    ofstream outFile;
    outFile.open("Bank_Account.dat", ios::binary | ios::app);
    account.create_account();
    outFile.write(reinterpret_cast<char *> (&account), sizeof(Bank_Account));
    outFile.close();
}
void delete_account(int n) {
    Bank_Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("Bank_Account.dat", ios::binary);
    if (!inFile) {
        cout << "\t File could not be opened";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account))) {
        if (ac.retacno() != n) {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Bank_Account.dat");
    rename("Temp.dat", "Bank_Account.dat");
    cout << "\t Record Deleted" << endl;
}
void display_details(int n) {
    Bank_Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("Bank_Account.dat", ios::binary);
    if(!inFile) {
        cout << "\t File could not be opened";
        return;
    }
    cout << "\t Bank Account Details" << endl;
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account))) {
        if (ac.retacno() == n) {
            ac.display_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false) {
        cout << "\t Account number does not exist" << endl;
    }
}
void display_all() {
    Bank_Account ac;
    ifstream inFile;
    inFile.open("Bank_Account.dat", ios::binary);
    if(!inFile) {
        cout << "\t File could not be opened";
        return;
    }
    cout << "\t Bank Account Holder List" << endl;
    cout << "=================================================" << endl;
    cout << "A/c no.         Name         Type         Balance" << endl;
    cout << "=================================================" << endl;
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account))) {
        ac.report();
    }
    inFile.close();
}
void money_deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("Bank_Account.dat", ios::binary|ios::in|ios::out);
    if (!File) {
        cout << "\t File could not be opened";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if (ac.retacno() == n) {
            ac.display_account();
            if (option == 1) {
                cout << "\t Enter the amount to deposit: ";
                cin >> amt;
                ac.dep(amt);
            }   
            if (option == 2) {
                cout << "\t Enter the amount to withdraw: ";
                cin >> amt;
                int balance = ac.retdeposit() - amt;
                if (balance < 0) {
                    cout << "\t Insufficient Balance" << endl;
                } else {
                    ac.draw(amt);
                }
            }
            int pos = (-1)*static_cast<int> (sizeof(Bank_Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
            cout << "\t Record Updated" << endl;
            found = true;
        }
    }
    File.close();
    if (found == false) {
        cout << "\t Record not found" << endl;
    }
}
void updation_bank_account(int n) {
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("Bank_Account.dat", ios::binary|ios::in|ios::out);
    if (!File) {
        cout << "\t File could not be opened";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if (ac.retacno() == n) {
            ac.display_account();
            cout << endl;
            cout << "\t Enter the new details of the account" << endl;
            ac.modify();
            int pos = (-1)*static_cast<int> (sizeof(Bank_Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
            cout << "\t Record Updated" << endl;
            found = true;
        }
    }
    File.close();
    if (found == false) {
        cout << "\t Record not found" << endl;
    }
}

