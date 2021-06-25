// Libraries included
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Function declarations
void menu();
void print();
void readFile();
void updateFile();
void calFilament_left(string color, float mm);
void calPrint_cost(string color, float mm, float hour);


// Variables defined.
vector<string> roll = {};
vector<float> cost = {};
vector<float> length = {};

constexpr auto spool_length = 330000;

int option;
float price, mm, hour;
string color;



int main()
{
    
    cout << "Welcome to the filament calculator program!" << endl << endl;

    // Loads vectors with the inventory elements.
    readFile();

    do {

        menu();

        cout << endl << endl;

        cout << "Select an option: ";
        cin >> option;
        cout << endl;
        cout << "<----------------------------------->" << endl << endl;

        switch (option) {

            // Calculate cost of print.
        case 1:

            cout << "Calculate cost of print selected." << endl << endl;

            print();

            cout << endl;

            cout << "Enter the color of filament: ";
            cin >> color;
            cout << endl;

            cout << "Enter the length of filament for the print in m: ";
            cin >> mm;
            mm = mm * 1000;
            cout << endl;

            cout << "Enter the hours of the print: ";
            cin >> hour;
            cout << endl;

            calPrint_cost(color, mm, hour);


            cout << "<----------------------------------->" << endl << endl;


            break;

            // Calculate filament left.
        case 2:

            cout << "Calculate filament length left selected." << endl << endl;

            print();

            cout << endl << endl;

            cout << "Enter the color of the roll: ";
            cin >> color;
            cout << endl;

            cout << "Enter amount of filament for print in m: ";
            cin >> mm;
            mm = mm * 1000;
            cout << endl;

            calFilament_left(color, mm);

            cout << endl;

            cout << "<----------------------------------->" << endl << endl;

            break;

            // Add filament roll.
        case 3:

            cout << "Add filament roll selected." << endl << endl;

            cout << "Enter the color of the roll: ";
            cin >> color;
            cout << endl;

            roll.push_back(color);

            cout << "Enter the cost of the roll ($00.00): ";
            cin >> price;
            cout << endl;

            cost.push_back(price);

            cout << "Enter the length of the roll in m (1kg = 330m): ";
            cin >> mm;
            mm = mm * 1000;
            cout << endl;

            length.push_back(mm);

            cout << color <<" roll added." << endl << endl;
            cout << "<----------------------------------->" << endl << endl;


            break;

            // Remove filament roll.
        case 4:

            cout << "Remove filament roll selected." << endl << endl;

            cout << "Rolls currently stocked." << endl << endl;

            print();

            cout << endl;

            cout << "Enter color of roll to remove: ";
            cin >> color;
            cout << endl;

            // Removes roll from vector.
            for (int i = 0; i < roll.size(); i++) {
                if (roll[i] == color) {

                    roll.erase(roll.begin() + i);
                    cost.erase(cost.begin() + i);
                    length.erase(length.begin() + i);
                }
                    
            }

            cout << color << " roll removed." << endl << endl;
            cout << "<----------------------------------->" << endl << endl;


            break;

            // Print availble rolls.
        case 5:

            cout << "Print availble rolls selected." << endl << endl;

            print();

            cout << endl;
            cout << "<----------------------------------->" << endl << endl;

            break;

            // Exit program
        case 6:

            updateFile();

            cout << "Thank you for using the filament calculator!" << endl;
            cout << "Goodbye!" << endl;
            exit(1);

        default:

            break;
        }
    } while (option != 6);
    
}


void menu() {

    cout << "1 --> Calculate cost of print." << endl;
    cout << "2 --> Calculate filament left." << endl;
    cout << "3 --> Add filament roll." << endl;
    cout << "4 --> Remove filament roll." << endl;
    cout << "5 --> Print availble rolls." << endl;
    cout << "6 --> Exit program." << endl;
}

void print() {

    cout << "Color\tCost\tLength" << endl << endl;

    // Prints all items in inventory.
    for (int i = 0; i < roll.size(); i++) {
        cout << roll[i] << "\t$" << cost[i]  << "\t" << length[i] << " mm" << endl;
        if (i < roll.size() - 1) {
            cout << "_______________________________________" << endl << endl;
        }
    }
}

void readFile() {

    ifstream inFile;
    inFile.open("inventory.txt");

    // Fills vectors from inventory file.
    if (inFile.is_open()) {
        while (inFile >> color >> price >> mm) {

            roll.push_back(color);
            cost.push_back(price);
            length.push_back(mm);
        }
    }

    inFile.close();
}

void updateFile() {

    ofstream outFile;
    outFile.open("inventory.txt");

    // Prints inventory to .txt file.
    for (int i = 0; i < roll.size(); i++) {

        outFile << roll.at(i) << " ";
        outFile << cost.at(i) << " ";
        outFile << length.at(i) << endl;
    }

    outFile.close();
}

void calFilament_left(string color, float mm) {

    float temp = 0.0;
    bool check = true;

    for (int i = 0; i < roll.size(); i++) {

        // Finds color of roll.
        if (roll[i] == color) {

            temp = length[i] - mm;

            // Checks if the print can be made.
            if (temp < length[i] && temp >= 0.0) {
                length[i] = temp;

                cout << "The print can be made." << endl;
                cout << roll[i] << " has " << length[i] << " mm left." << endl;

                check = false;

                break;
            }
            
        }
    }  

    // Print cannot be made with current roll.
    if (check) {
        cout << "The print exceeds the current amount of filament!" << endl;
    }
}

void calPrint_cost(string color, float mm, float hour) {

    float cph = 1.50 * hour;

    for (int i = 0; i < roll.size(); i++) {

        // Finds color of roll.
        if (roll[i] == color) {

            // Calculates print cost.
            float total = cph + (cost[i] / spool_length) * mm;
            float printCost = (cost[i] / spool_length) * mm;

            cout << "The print would cost $" << printCost << " per mm."<< endl;
            cout << "Cost per hour is $" << cph << "." << endl;
            cout << "The total cost of the print would be $ " << total << "." << endl;

            total = 0.0;

            break;
        }
    }
}