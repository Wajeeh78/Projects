//This is our final project we did in our oop class. This bank system uses the concepts of OOP. Has encapsulation, File handling, Exception Handling,
//Pure and normal virtual function.



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int MAX_ACCOUNTS = 50;
const int MAX_CUSTOMERS = 10;

class Date { // WAJEEH 
// dates class is being compostioned into other classes
public:
    int day, month, year;

    Date(int d = 0, int m = 0, int y = 0) : day(d), month(m), year(y) {}

    string toString() const { // its cons the class varibles cant be changed, dates value cant be changed
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    static Date fromString(const string& dateStr) {
        int d, m, y;
        sscanf(dateStr.c_str(), "%d/%d/%d", &d, &m, &y);
        return Date(d, m, y);
    }
};

class Account { // Wajeeh Ahmed
protected:
    string IBAN;
    unsigned long balance;// range longed it can bshow ,any values to billions
    string password;
    Date created; //composition of dates class

public:
    Account(string iban = "", unsigned long bal = 0, string pwd = "", Date date = Date())
        : IBAN(iban), balance(bal), password(pwd), created(date) {}

    virtual string getType() const = 0;// this is making this class abstract, it will be used in inherited class, checkand savings
    virtual unsigned long getBalance() const { return balance; }

    string getIBAN() const { return IBAN; }
    string getPassword() const { return password; } // only getting the values
    Date getCreatedDate() const { return created; }

    virtual void prettyPrint() const { // normal couting
        cout << "IBAN: " << IBAN << ", Balance: " << balance << ", Created: " << created.toString() << endl;
    }

    virtual void deposit(unsigned long amount) { balance += amount; }
    virtual bool withdraw(unsigned long amount) {
        if (amount > balance) {
            cout << "Insufficient funds." << endl;
            return false;
        }
        
        balance -= amount;
        return true;
    }
};

class CheckingAccount : public Account { 
public: 
    CheckingAccount(string iban = "", unsigned long bal = 0, string pwd = "", Date date = Date())
        : Account(iban, bal, pwd, date) {} 

    string getType() const override { return "Checking"; } // implementation of the gettype 0

    void prettyPrint() const override {
        cout << "Checking Account - IBAN: " << IBAN << ", Balance: " << balance
             << ", Created: " << created.toString() << endl;
    }
};

class CurrentAccount : public Account { 
public:
    CurrentAccount(string iban = "", unsigned long bal = 0, string pwd = "", Date date = Date())
        : Account(iban, bal, pwd, date) {}

    string getType() const override { return "Current"; }

    void prettyPrint() const override {
        cout << "Current Account - IBAN: " << IBAN << ", Balance: " << balance
             << ", Created: " << created.toString() << endl;
    }
};

class Customer { // Isha 
    string username;
    string password;
    Account* accounts[MAX_ACCOUNTS]; // pointer 
    int accountCount;

public:
    Customer(string uname = "", string pwd = "") : username(uname), password(pwd), accountCount(0) { 
        for (int i = 0; i < MAX_ACCOUNTS; ++i) {
            accounts[i] = nullptr;
        }
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    void addAccount(Account* account) {
        if (accountCount < MAX_ACCOUNTS) {
            accounts[accountCount++] = account;
        } else {
            cout << "Maximum accounts reached for customer." << endl;
        }
    }

    Account** getAccounts() { return accounts; } // to return array **
    int getAccountCount() const { return accountCount; }
    
    void showAccounts() const {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i] != nullptr) {   // its a pointer not pointing at anything used if value isnt available
                accounts[i]->prettyPrint();
            }
        }
    }

    Account* findAccount(const string& iban, const string& pwd) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i] != nullptr && accounts[i]->getIBAN() == iban && accounts[i]->getPassword() == pwd) {
                return accounts[i];
            }
        }
        return nullptr;
    }
};

class Database {        
    string customersFile;
    string accountsFile;

public:
    Database(string custFile = "customers.csv", string acctFile = "accounts.csv") // two fields
        : customersFile(custFile), accountsFile(acctFile) {}

    void addCustomerRecord(const Customer& customer) {  // file opening
        try {
            ofstream file(customersFile, ios::app); // opening through ofstream
            if (file.is_open()) {
                file << customer.getUsername() << "," << customer.getPassword() << "\n";
                file.close();
            } else {
                throw runtime_error("Failed to open file: " + customersFile);
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    void addAccountRecord(const Customer& customer, const Account& account) {   // opening file but different file
        try {
            ofstream file(accountsFile, ios::app);
            if (file.is_open()) {
                file << customer.getUsername() << "," << account.getIBAN() << "," << account.getPassword() << ","
                     << account.getType() << "," << account.getBalance() << "," << account.getCreatedDate().toString() << "\n";
                file.close();
            } else {
                throw runtime_error("Failed to open file: " + accountsFile);
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    void loadCustomers(Customer customers[], int& customerCount) { 
        try {
            ifstream file(customersFile);
            if (!file.is_open()) {
                throw runtime_error("Failed to open file: " + customersFile);
            }
            string line;
            customerCount = 0;
            while (getline(file, line)) {
                stringstream ss(line);    
                string username, password;
                getline(ss, username, ',');   
                getline(ss, password, ',');
                customers[customerCount++] = Customer(username, password);
            }
            file.close();
        } catch (const exception& e) {
            cout << e.what() << endl;
            customerCount = 0;
        }
    }

    void loadAccounts(Customer customers[], int customerCount) {  // array is always passed by reference
        try {
            ifstream file(accountsFile);
            if (!file.is_open()) {
                throw runtime_error("Failed to open file: " + accountsFile);
            }
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string username, iban, pwd, type, balanceStr, createdStr;   
                unsigned long balance;
                getline(ss, username, ',');
                getline(ss, iban, ',');
                getline(ss, pwd, ',');
                getline(ss, type, ',');
                getline(ss, balanceStr, ',');
                balance = stoul(balanceStr);
                getline(ss, createdStr, ',');
                Date created = Date::fromString(createdStr);

                Account* account = nullptr;
                if (type == "Checking") {
                    account = new CheckingAccount(iban, balance, pwd, created);
                } else if (type == "Current") {
                    account = new CurrentAccount(iban, balance, pwd, created);
                }

                for (int i = 0; i < customerCount; ++i) {
                    if (customers[i].getUsername() == username) {
                        customers[i].addAccount(account);           
                        break;
                    }
                }
            }
            file.close();
        } catch (const exception& e) { 
            cout << e.what() << endl;
        }
    }
};


class Bank { // Isha                           // data base is aggregated into banks class
    string name;                                          // it is because it can exist independently 
    Database db;
    Customer customers[MAX_CUSTOMERS];
    int customerCount; // customer is a compositon it cant exist independently 

public:
    Bank(Database &db) : db(), customerCount(0) {
        name = "Freelancer Bank";
        db.loadCustomers(customers, customerCount);
        db.loadAccounts(customers, customerCount);
    }

    void addCustomer(const Customer& customer) { // refrence operator it used so that we dont have to copy values agian and agian
        if (customerCount < MAX_CUSTOMERS) {
            customers[customerCount++] = customer;
            db.addCustomerRecord(customer);
        } else {
            cout << "Maximum customers reached for bank." << endl;
        }
    }

    void addAccountToCustomer(const string& username, Account* account) { // account is being associated to customer 
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].getUsername() == username) {
                customers[i].addAccount(account);
                db.addAccountRecord(customers[i], *account); // coming from main()
                break;
            }
        }
    }

    Customer* findCustomer(const string& username, const string& password) {  // coming from main() // pointer
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].getUsername() == username && customers[i].getPassword() == password) {
                return &customers[i];
            }
        }
        return nullptr;
    }

    void prettyPrint() {
        cout << "Welcome to " << name << endl;
    }
};

int main() { // Wajeeh Ahmed
    Database db;
    Bank bank(db); 
    bank.prettyPrint();

    while (true) {
        string username, password;
        cout << "Enter customer username: ";
        cin >> username;
        cout << "Enter customer password: ";
        cin >> password;

        Customer* customer = bank.findCustomer(username, password); // pointer 
        if (!customer) {
            cout << "Customer not found. Creating a new customer." << endl;
            Customer newCustomer(username, password);
            bank.addCustomer(newCustomer);
            customer = bank.findCustomer(username, password);  // Retrieve the newly added customer
        } else {
            cout << "Customer found." << endl;
        }

        char choice;
        do {
            cout << "Do you want to (A)dd an account, (S)how accounts, or (L)og into an account? (A/S/L): ";
            cin >> choice;

            if (choice == 'A' || choice == 'a') {
                char accountType;
                cout << "Enter account type (C for Checking, U for Current): ";
                cin >> accountType;

                string iban, pwd;
                unsigned long balance;
                cout << "Enter IBAN: ";
                cin >> iban;
                cout << "Enter balance: ";
                cin >> balance;
                cout << "Enter account password: ";
                cin >> pwd;

                Date createdDate;
                Account* newAccount = nullptr;
                if (accountType == 'C' || accountType == 'c') {
                    newAccount = new CheckingAccount(iban, balance, pwd, createdDate);
                } else if (accountType == 'U' || accountType == 'u') {
                    newAccount = new CurrentAccount(iban, balance, pwd, createdDate);
                }

                if (newAccount) {
                    customer->addAccount(newAccount);
                    bank.addAccountToCustomer(username, newAccount);
                }

            } else if (choice == 'S' || choice == 's') {
                customer->showAccounts();
            } else if (choice == 'L' || choice == 'l') {
                string iban, accountPassword;
                cout << "Enter IBAN: ";
                cin >> iban;
                cout << "Enter account password: ";
                cin >> accountPassword;

                Account* account = customer->findAccount(iban, accountPassword);
                if (account) {
                    char operation;
                    do {
                        cout << "Do you want to (D)eposit or (W)ithdraw? (D/W): ";
                        cin >> operation;

                        if (operation == 'D' || operation == 'd') {
                            unsigned long amount;
                            cout << "Enter amount to deposit: ";
                            cin >> amount;
                            account->deposit(amount);
                            cout << "Deposit successful. New balance: " << account->getBalance() << endl;
                        } else if (operation == 'W' || operation == 'w') {
                            unsigned long amount;
                            cout << "Enter amount to withdraw: ";
                            cin >> amount;
                            if (account->withdraw(amount)) {
                                cout << "Withdrawal successful. New balance: " << account->getBalance() << endl;
                            }
                        }

                        cout << "Do you want to perform another operation on this account? (Y/N): ";
                        cin >> operation;

                    } while (operation == 'Y' || operation == 'y');
                } else {
                    cout << "Account not found or incorrect password." << endl;
                }
            }

            cout << "Do you want to perform another operation? (Y/N): ";
            cin >> choice;

        } while (choice == 'Y' || choice == 'y');
    }

    return 0;
}
