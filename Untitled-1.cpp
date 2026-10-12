#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // 1. Declare input stream and variables
    ifstream fin;
    string food1, food2;
    double food1Sm, food1Med, food1Lg;
    double food2Sm, food2Med, food2Lg;

    // 2. Open the menu text file (replace "menu.txt" with your exact file name if different)
    fin.open("menu.txt");

    // Check if file opened successfully
    if (!fin) {
        cout << "Error: Could not open menu file!" << endl;
        return 1;
    }

    // 3. Read Item 1
    getline(fin, food1);
    fin >> food1Sm >> food1Med >> food1Lg;
    fin.ignore(); // Clears the newline character after reading the last price

    // 4. Read Item 2
    getline(fin, food2);
    fin >> food2Sm >> food2Med >> food2Lg;

    // Close the file stream
    fin.close();

    // Quick test print to verify it loaded correctly
    cout << "Loaded from file successfully:\n";
    cout << food1 << " -> $" << food1Sm << " / $" << food1Med << " / $" << food1Lg << endl;
    cout << food2 << " -> $" << food2Sm << " / $" << food2Med << " / $" << food2Lg << endl;

    return 0;
}
