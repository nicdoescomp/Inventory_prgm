#include <iostream>
#include <fstream> // Needed to access files
#include <string>
#include <iomanip>
#include <limits> // used for the ClearInput function below
#include <vector>

using namespace std;

void ClearInput();
void changeRecords(std::fstream &MyWriteFile, const string &filename);

const int NAME_SIZE = 21, DATE_SIZE = 11;

struct items {
    char name[NAME_SIZE];
    char date[DATE_SIZE];
    int quant;
    double whole, retail;
};

int main() {
    items invent;
    
    fstream MyWriteFile; // declare this first before opening up files
    
    int ans;
    int count;
    string filename = "/Users/nic/Documents/A4/A4/inventory_1.txt";

    
    cout << "Opening file...\n";
    MyWriteFile.open("/Users/nic/Documents/A4/A4/inventory_1.txt", ios::out);
    
    if (!MyWriteFile) {
        cerr << "Error opening file!\n";
        return 1;
    }
    
    for (count = 0; count < 4; count++) {
        cout << "Please input the item's name:\n";
        cin.getline(invent.name, NAME_SIZE);
        
        cout << "Please input the date received (YYYY-MM-DD format):\n";
        cin.getline(invent.date, DATE_SIZE);
        
        cout << "Please input quantity:\n";
        cin >> invent.quant;
        
        cout << "Please input the wholesale cost:\n";
        cin >> invent.whole;
        
        cout << "Please input the retail cost:\n";
        cin >> invent.retail;
        
        // Now writing data to the file in text mode
        MyWriteFile << invent.name << " " << setw(10)<< invent.date
        << setw(10) << invent.quant  << setw(10) << fixed << setprecision(2)
        << invent.whole  << setw(10) << invent.retail << endl;
        
        cout << "Done writing item " << count + 1 << "/4 to the inventory file.\n";
        ClearInput(); // Clears input buffer
    }
    
    
    cout << "You have filled out the required inventory.\n";
    cout << "Now closing the file.\n";
    
    MyWriteFile.close();
    
    cout << "Here is your inventory:\n";

    string myText;
    
    ifstream MyReadFile("/Users/nic/Documents/A4/A4/inventory_1.txt");
    
    while (getline (MyReadFile, myText)) {
        cout << myText << endl;
    }
    
    MyReadFile.close();
    
    
    cout << "Do you want to change records or quit program? [1] for 'Yes' or [0] for 'No' :\n";
    cin >> ans;
    if (ans == 1) {
        changeRecords(MyWriteFile, filename);

    }else{
        cout << "Goodbye!" << endl;
        cout << "Terminating program...." << endl;

    }

}

void changeRecords(fstream &MyWriteFile, const string &filename) {
    vector<items> inventory; // inventory is now a dynamic array of items objects
    items temp; // create the object
    
    ifstream inFile(filename); // Reopen the file cause we closed it two seperate times before
    if (!inFile) {
        cerr << "Error opening file for reading!\n"; // output an error if not able to access
        return;
    }
    
    while (inFile >> temp.name >> temp.date >> temp.quant >> temp.whole >> temp.retail) {
        inventory.push_back(temp);  //Loops as long as there is valid data to read and pushes the temp items into the inventory vector
    }
    inFile.close();
    
    cout << "Select an item number to modify (0 to " << inventory.size() - 1 << "):\n";
    int index;
    cin >> index;
    
    if (index < 0 || index >= inventory.size()) { //Error handling if index given is not in scope
        cout << "Invalid index. Exiting...\n";
        return;
    }
    
    cout << "Editing item: " << inventory[index].name << endl;
    cout << "Enter new quantity: ";
    cin >> inventory[index].quant;
    
    cout << "Enter new wholesale cost: ";
    cin >> inventory[index].whole;
    
    cout << "Enter new retail cost: ";
    cin >> inventory[index].retail;
    
    MyWriteFile.open(filename, ios::out | ios::trunc); //Reopens the file but now uses it to write on it
    if (!MyWriteFile) {
        cerr << "Error opening file for writing!\n";
        return;
    }
    
    //now that we have the contents inside of the inventory vector we can then itterate over them and store them inside of the file itself
    for (const auto &item : inventory) {
        MyWriteFile << item.name << " " << setw(10) << item.date  << setw(10) << item.quant  << setw(10)
        << fixed << setprecision(2) << item.whole << setw(10) << item.retail << endl;
    }
    
    MyWriteFile.close();
    cout << "Record updated successfully!\n";
}
// Clear input buffer
void ClearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

