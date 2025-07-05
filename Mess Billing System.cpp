#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to print ASCII Art
void printASCIIArt() {
    cout << R"(
███╗   ███╗███████╗███████╗███████╗    ██████╗ ██╗██╗     ██╗     ██╗███╗   ██╗ ██████╗     ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗
████╗ ████║██╔════╝██╔════╝██╔════╝    ██╔══██╗██║██║     ██║     ██║████╗  ██║██╔════╝     ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║
██╔████╔██║█████╗  ███████╗███████╗    ██████╔╝██║██║     ██║     ██║██╔██╗ ██║██║  ███╗    ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║
██║╚██╔╝██║██╔══╝  ╚════██║╚════██║    ██╔══██╗██║██║     ██║     ██║██║╚██╗██║██║   ██║    ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║
██║ ╚═╝ ██║███████╗███████║███████║    ██████╔╝██║███████╗███████╗██║██║ ╚████║╚██████╔╝    ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║
╚═╝     ╚═╝╚══════╝╚══════╝╚══════╝    ╚═════╝ ╚═╝╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝
    )" << endl;
}


// Global variables for student data, menu, and mess operations
string name[100];
int reg_no[100];
unsigned int password[100];
int bill[100];
bool check_io[100];  // Mess access (True for granted, False for denied)
int n = 0;  // Number of students
string menuItems[21];  // Menu items
int priceItems[21];  // Prices for menu items
int m = 0; // Menu count

// Function to save students to a file
void saveStudents() {
    ofstream outFile("students.txt");
    for (int i = 0; i < n; i++) {
        outFile << reg_no[i] << " " << name[i] << " " << password[i] << " " << bill[i] << " " << check_io[i] << endl;
    }
    outFile.close();
}

// Function to load students from a file
void loadStudents() {
    ifstream inFile("students.txt");
    while (inFile >> reg_no[n]) {
        inFile >> name[n] >> password[n] >> bill[n] >> check_io[n];
        n++;  // Increment the number of students
    }
    inFile.close();
}

// Function to save the menu to a file
void saveMenu() {
    ofstream outFile("menu.txt");
    for (int i = 0; i < m; i++) {
        outFile << menuItems[i] << " " << priceItems[i] << endl;
    }
    outFile.close();
}

// Function to load the menu from a file
void loadMenu() {
    ifstream inFile("menu.txt");
    while (inFile >> menuItems[m]) {
        inFile >> priceItems[m];
        m++;  // Increment the menu count
    }
    inFile.close();
}

// Function to save bills to a file
void saveBills() {
    ofstream outFile("bills.txt");
    for (int i = 0; i < n; i++) {
        outFile << reg_no[i] << " " << bill[i] << endl;
    }
    outFile.close();
}

// Function to load bills from a file
void loadBills() {
    ifstream inFile("bills.txt");
    int reg;
    while (inFile >> reg) {
        for (int i = 0; i < n; i++) {
            if (reg_no[i] == reg) {
                inFile >> bill[i];  // Load the bill amount
                break;
            }
        }
    }
    inFile.close();
}



// Function to get the number of days in a month (simplified)
int getDaysInMonth(int month) {
    if (month == 2) {
        return 28;  // February, assuming 28 days
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;  // April, June, September, November
    } else {
        return 31;  // January, March, May, July, August, October, December
    }
}
// Function to set the menu for a week
void menuFunction(string day[], int &v, string menu[], int price[], int &m, int &dayNum, int &month, int &year) {
    m = 0;  // Reset menu count for the new week
    // Loop through the 7 days of the week
    for (int i = 0; i < 7; i++) {
        cout << "Enter the name of the day : ";
        cin >> day[i];  // Store the day name
        for (int j = 0; j < 3; j++) {  // 3 dishes per day
            cout << "Enter the name of dish " << j + 1 << ": ";
            cin >> menu[m];  // Store the name of the menu item
            cout << "Enter the price for " << menu[m] << ": ";
            cin >> price[m];  // Store the price of the dish
            m++;  // Increase the menu count
        }
        // Display the current date
        cout << "Menu for " << day[i] << " (" << dayNum << "/" << month << "/" << year << ")" << endl;
        dayNum++;  // Increment the day number
        // Adjust the day and month if necessary
        if (dayNum > getDaysInMonth(month)) {
            dayNum = 1;  // Reset day to 1 when moving to the next month
            month++;  // Increment the month
            if (month > 12) {  // If the month goes beyond December, reset to January and increment the year
                month = 1;
                year++;
            }
        }
    }
    cout << "Menu for the week has been set successfully!" << endl;
}
// Function to add a student
void addStudent() {
    cout << "Enter student name: ";
    cin >> name[n];
    cout << "Enter registration number: ";
    cin >> reg_no[n];
    cout << "Enter password: ";
    cin >> password[n];
    bill[n] = 0;  // Initializing the bill to 0
    check_io[n] = true; // Grant mess access initially
    n++;
    cout << "Student added successfully!" << endl;
}
// Function to remove a student
void removeStudent() {
    int check_r;
    cout << "Enter registration number of student to remove: ";
    cin >> check_r;
    for (int i = 0; i < n; i++) {
        if (reg_no[i] == check_r) {
            // Shift the elements after the student
            for (int j = i; j < n - 1; j++) {
                reg_no[j] = reg_no[j + 1];
                name[j] = name[j + 1];
                password[j] = password[j + 1];
                bill[j] = bill[j + 1];
                check_io[j] = check_io[j + 1];
            }
            n--;
            cout << "Student removed successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}
// Function to print bills (Single/All)
void printBill() {
    char choice;
    cout << "Enter 'S' to print a single bill or 'A' to print all bills: ";
    cin >> choice;
    if (choice == 'S') {
        int check_r;
        cout << "Enter registration number: ";
        cin >> check_r;
        for (int i = 0; i < n; i++) {
            if (reg_no[i] == check_r) {
                cout << "Bill for " << name[i] << ": " << bill[i] << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    } else if (choice == 'A') {
        for (int i = 0; i < n; i++) {
            cout << "Bill for " << name[i] << " (" << reg_no[i] << "): " << bill[i] << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }
}
// Function to change the menu (Display, Add, Remove food items)
void changeMenu() {
    char action;
    cout << "Menu Management:" << endl;
    cout << "1. Display Menu" << endl;
    cout << "2. Add Food Item" << endl;
    cout << "3. Remove Food Item" << endl;
    cout << "4. Set Daily Menu" << endl;  // Option for new functionality
    cout << "Enter your choice: ";
    cin >> action;
    if (action == '1') {
        // Display the menu
        cout << "Current Menu: " << endl;
        if (m == 0) {
            cout << "No items available in the menu." << endl;
        } else {
            int index = 0;
            for (int i = 0; i < 7; i++) {  // Loop through 7 days
                cout << "Day " << i + 1 << ": " << endl;
                cout << "Menu for " << menuItems[index] << ": " << endl;
                for (int j = 0; j < 3; j++) {  // 3 items per day
                    cout << menuItems[index] << " - Price: " << priceItems[index] << endl;
                    index++;  // Move to next item
                }
                cout << endl;
            }
        }
    } else if (action == '2') {
        // Add food item
        if (m < 21) {  // Ensure that the menu doesn't exceed 21 items
            cout << "Enter the name of the new food item: ";
            cin >> menuItems[m];
            cout << "Enter the price of the new food item: ";
            cin >> priceItems[m];
            m++;  // Increase the menu count
            cout << "Food item added successfully!" << endl;
        } else {
            cout << "Menu is full, can't add more items." << endl;
        }
    } else if (action == '3') {
        // Remove food item
        int itemToRemove;
        cout << "Enter the number of the food item to remove: ";
        cin >> itemToRemove;
        if (itemToRemove < 1 || itemToRemove > m) {
            cout << "Invalid item number!" << endl;
        } else {
            // Remove the food item by shifting subsequent items
            for (int i = itemToRemove - 1; i < m - 1; i++) {
                menuItems[i] = menuItems[i + 1];
                priceItems[i] = priceItems[i + 1];
            }
            m--;  // Decrease the menu count
            cout << "Food item removed successfully!" << endl;
        }
    } else if (action == '4') {
        string day[7];  // Array to store days of the week
        string menu[3]; // Array to store 3 dishes per day
        int price[3];   // Array to store prices of the dishes
        int v = 0;      // Day index
        int dayNum = 1, month = 1, year = 2024;  // Initialize date
        
        // Call the menu function to set the menu for the week
        menuFunction(day, v, menu, price, m, dayNum, month, year);
    } else {
        cout << "Invalid choice!" << endl;
    }
}
// Function to open the mess
void openMess() {
    cout << "Mess is now OPEN!" << endl;
}
// Function to close the mess
void closeMess() {
    cout << "Mess is now CLOSED!" << endl;
}
// Function to check student profile
void checkStudentProfile() {
    int check_r;
    cout << "Enter student registration number: ";
    cin >> check_r;
    for (int i = 0; i < n; i++) {
        if (reg_no[i] == check_r) {
            cout << "Name: " << name[i] << endl;
            cout << "Registration Number: " << reg_no[i] << endl;
            cout << "Bill: " << bill[i] << endl;
           // cout << "Mess Access: " << (check_io[i] ? "Granted" : "Denied") << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}
// Function to confirm bill payment
void confirmBillPayment() {
    int check_r;
    cout << "Enter registration number to confirm payment: ";
    cin >> check_r;
    for (int i = 0; i < n; i++) {
        if (reg_no[i] == check_r) {
            bill[i] = 0;  // Resetting the bill to 0 after payment
            cout << "Payment confirmed for " << name[i] << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}
// Function to toggle mess access for a student (IN/OUT options)
void toggleMessAccess() {
    int check_r;
    string action;
    cout << "Enter registration number to toggle access: ";
    cin >> check_r;
    for (int i = 0; i < n; i++) {
        if (reg_no[i] == check_r) {
            cout << "Enter 'IN' to grant access or 'OUT' to deny: ";
            cin >> action;
            if (action == "IN") {
                check_io[i] = true;
                cout << "Access granted!" << endl;
            } else if (action == "OUT") {
                check_io[i] = false;
                cout << "Access denied!" << endl;
            } else {
                cout << "Invalid option!" << endl;
            }
            return;
        }
    }
    cout << "Student not found!" << endl;
}
   int main() {
       printASCIIArt();
    char userType;
    int check_p;
    
    cout << "Welcome to the Mess Billing System!" << endl;
    cout << "------------------------------------" << endl;
    // Manager login
    cout << "Enter the password to start: ";
    cin >> check_p;
    if (check_p == 12345) {  // System-level password
        do {
            cout << "Enter 'S' if you are a student and 'M' if you are a manager: ";
            cin >> userType;
            if (userType == 'S') {
                // Student functionality
                int studentReg;
                cout << "Enter your registration number: ";
                cin >> studentReg;
                bool studentFound = false;
                for (int i = 0; i < n; i++) {
                    if (reg_no[i] == studentReg) {
                        cout << "Today's menu: " << endl;
                        for (int i = 0; i < m; i++) {
                            cout << menuItems[i] << " - Price: " << priceItems[i] << endl;
                        }
                        studentFound = true;
                        break;
                    }
                }
                if (!studentFound) {
                    cout << "Student not found!" << endl;
                }
            } else if (userType == 'M') {
                // Manager functionality
                cout << "Enter the manager password: ";
                cin >> check_p;
                if (check_p == 54321) {  // Manager password
                    char choice;
                    cout << "Manager Menu:\n";
                    cout << "1. Add Student\n";
                    cout << "2. Remove Student\n";
                    cout << "3. Print Bill (Single/All)\n";
                    cout << "4. Change Menu\n";
                    cout << "5. Open Mess\n";
                    cout << "6. Close Mess\n";
                    cout << "7. Check Student Profile\n";
                    cout << "8. Confirm Bill Payment\n";
                    cout << "9. Toggle Mess Access for a Student\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case '1': addStudent(); break;
                        case '2': removeStudent(); break;
                        case '3': printBill(); break;
                        case '4': changeMenu(); break;
                        case '5': openMess(); break;
                        case '6': closeMess(); break;
                        case '7': checkStudentProfile(); break;
                        case '8': confirmBillPayment(); break;
                        case '9': toggleMessAccess(); break;
                        default: cout << "Invalid choice!" << endl; break;
                    }
                    // Save student, menu, and bill data to files after each change
                    saveStudents();
                    saveMenu();
                    saveBills();
                    
                } else {
                    cout << "Invalid password." << endl;
                }
            } else {
                cout << "Invalid input!" << endl;
            }
        } while (true);  // Loop indefinitely as no exit option is provided
    } else {
        cout << "Invalid system password!" << endl;
    }
    return 0;
}