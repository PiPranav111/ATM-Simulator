#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class ATM {
private:
    long accountNo;
    string name;
    int pin;
    double balance;
    string mobileNo;

public:
    ATM(long acc, string nm, int p, double bal, string mob)
        : accountNo(acc), name(nm), pin(p), balance(bal), mobileNo(mob) {}

    bool authenticate(long acc, int inputPin) {
        return (acc == accountNo && inputPin == pin);
    }

    string getName() const {
        return name;
    }

    void showMenu() {
        int choice;
        while (true) {
            cout << "\n========== ATM MENU ==========";
            cout << "\n1. Check Balance";
            cout << "\n2. Withdraw Cash";
            cout << "\n3. Show User Details";
            cout << "\n4. Update Mobile Number";
            cout << "\n5. Logout";
            cout << "\nEnter choice: ";
            cin >> choice;

            if (cin.fail()) {
                handleInvalidInput();
                continue;
            }

            switch (choice) {
                case 1: showBalance(); break;
                case 2: withdrawCash(); break;
                case 3: showDetails(); break;
                case 4: updateMobile(); break;
                case 5:
                    cout << "Logging out...\n";
                    return;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
    }

private:
    void showBalance() {
        cout << "Available Balance: ₹" << balance << endl;
    }

    void withdrawCash() {
        int amount;
        cout << "Enter amount to withdraw: ₹";
        cin >> amount;

        if (cin.fail() || amount <= 0) {
            handleInvalidInput();
            return;
        }

        if (amount <= balance) {
            balance -= amount;
            cout << "Please collect your cash.\n";
            cout << "Remaining Balance: ₹" << balance << endl;
        } else {
            cout << "Insufficient Balance.\n";
        }
    }

    void showDetails() {
        cout << "\n--- User Details ---";
        cout << "\nAccount No: " << accountNo;
        cout << "\nName: " << name;
        cout << "\nBalance: ₹" << balance;
        cout << "\nMobile No: " << mobileNo << endl;
    }

    void updateMobile() {
        string oldMob, newMob;
        cout << "Enter old mobile number: ";
        cin >> oldMob;
        cout << "Enter new mobile number: ";
        cin >> newMob;

        if (oldMob == mobileNo) {
            mobileNo = newMob;
            cout << "Mobile number updated successfully.\n";
        } else {
            cout << "Incorrect old mobile number.\n";
        }
    }

    void handleInvalidInput() {
        cout << "Invalid input! Please enter valid data.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

int main() {
    vector<ATM> users;
    users.push_back(ATM(1234567, "Tim", 1111, 45000.90, "9087654321"));
    users.push_back(ATM(7654321, "Anya", 2222, 55000.50, "9876543210"));
    users.push_back(ATM(3456789, "Pranav", 2025, 99999.00, "9999999999"));

    while (true) {
        long acc;
        int pin;
        cout << "\n====== Welcome to ATM ======\n";
        cout << "Enter Account Number (or 0 to Exit): ";
        cin >> acc;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid account input. Try again.\n";
            continue;
        }

        if (acc == 0) {
            cout << "Exiting ATM. Thank you!\n";
            break;
        }

        cout << "Enter PIN: ";
        cin >> pin;

        bool authenticated = false;

        for (ATM& user : users) {
            if (user.authenticate(acc, pin)) {
                cout << "\n✅ Login successful. Welcome, " << user.getName() << "!\n";
                user.showMenu();  // session starts
                authenticated = true;
                break;
            }
        }

        if (!authenticated) {
            cout << "❌ Authentication failed. Please try again.\n";
        }
    }

    return 0;
}
