#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // ==========================================
    // PHASE 2: Read the menu from "lol.txt"
    // ==========================================
    ifstream fin;
    fin.open("lol.txt");
    
    // Check if the menu file opened successfully
    if (!fin) {
        cout << "Error: Could not open menu file! Make sure lol.txt is in your project directory." << endl;
        return 1;
    }

    string food1, food2;
    double food1Sm, food1Med, food1Lg;
    double food2Sm, food2Med, food2Lg;

    // Read Item 1 name and its three prices
    getline(fin, food1);
    fin >> food1Sm >> food1Med >> food1Lg;
    fin.ignore(); // Clears the newline character left in the stream

    // Read Item 2 name and its three prices
    getline(fin, food2);
    fin >> food2Sm >> food2Med >> food2Lg;

    // Close the input file stream
    fin.close();

    // ==========================================
    // PHASE 3: Ordering & Receipt / Inventory Log
    // ==========================================
    string customerName;
    cout << "Enter customer name: ";
    cin >> customerName;

    // Initial inventory tracking variables
    int food1Start = 50;
    int food2Start = 50;
    int food1Sold = 0;
    int food2Sold = 0;

    int choice, sizeChoice, qty;
    char more;
    double total = 0.0;

    // Open receipt output stream (append mode so multiple customer receipts stack nicely)
    ofstream receipt_fout;
    receipt_fout.open("receipt.txt", ios::app);

    // Print receipt header to both console and receipt file simultaneously
    cout << "\n************* Receipt for " << customerName << " *************\n";
    if (receipt_fout.is_open()) {
        receipt_fout << "************* Receipt for " << customerName << " *************\n";
    }

    do {
        // Display interactive menu pulled from the text file
        cout << "\n--- MENU ---\n";
        cout << "1. " << food1 << " (Sm: $" << food1Sm << ", Med: $" << food1Med << ", Lg: $" << food1Lg << ")\n";
        cout << "2. " << food2 << " (Sm: $" << food2Sm << ", Med: $" << food2Med << ", Lg: $" << food2Lg << ")\n";
        cout << "Select item (1 or 2): ";
        cin >> choice;

        cout << "Select size (1 = Small, 2 = Medium, 3 = Large): ";
        cin >> sizeChoice;

        cout << "Enter quantity: ";
        cin >> qty;

        double itemPrice = 0.0;
        string itemName = "";
        string sizeName = "";

        // Process item selection and update quantities sold
        if (choice == 1) {
            itemName = food1;
            food1Sold += qty;
            if (sizeChoice == 1) { itemPrice = food1Sm; sizeName = "Small"; }
            else if (sizeChoice == 2) { itemPrice = food1Med; sizeName = "Medium"; }
            else { itemPrice = food1Lg; sizeName = "Large"; }
        } else if (choice == 2) {
            itemName = food2;
            food2Sold += qty;
            if (sizeChoice == 1) { itemPrice = food2Sm; sizeName = "Small"; }
            else if (sizeChoice == 2) { itemPrice = food2Med; sizeName = "Medium"; }
            else { itemPrice = food2Lg; sizeName = "Large"; }
        }

        double subtotal = itemPrice * qty;
        total += subtotal;

        // Print item line to console and receipt file
        cout << qty << "x " << sizeName << " " << itemName << " @ $" << itemPrice << " = $" << subtotal << endl;
        if (receipt_fout.is_open()) {
            receipt_fout << qty << "x " << sizeName << " " << itemName << " @ $" << itemPrice << " = $" << subtotal << endl;
        }

        cout << "Would you like to order another item? (y/n): ";
        cin >> more;

    } while (more == 'y' || more == 'Y');

    // Finalize receipt total
    cout << "Total: $" << total << "\n";
    cout << "****************************************************\n\n";
    if (receipt_fout.is_open()) {
        receipt_fout << "Total: $" << total << "\n";
        receipt_fout << "****************************************************\n\n";
        receipt_fout.close(); // Close receipt file
    }

    // ==========================================
    // PHASE 3 Part 2: Daily Inventory Log
    // ==========================================
    int food1End = food1Start - food1Sold;
    int food2End = food2Start - food2Sold;

    // Open daily log file in append mode (`ios::app`) to save records safely
    ofstream daily_log_fout;
    daily_log_fout.open("daily_log.txt", ios::app);
    
    if (daily_log_fout.is_open()) {
        daily_log_fout << "Daily Inventory\n";
        daily_log_fout << "Item | Start | Change | End\n";
        daily_log_fout << food1 << " | " << food1Start << " | -" << food1Sold << " | " << food1End << "\n";
        daily_log_fout << food2 << " | " << food2Start << " | -" << food2Sold << " | " << food2End << "\n";
        daily_log_fout << "----------------------------------------\n";
        daily_log_fout.close();
    }

    cout << "Transaction complete! Receipt saved to receipt.txt and inventory logged to daily_log.txt.\n";

    return 0;
}
