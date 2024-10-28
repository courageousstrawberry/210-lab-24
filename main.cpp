#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <limits>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;
    int user = 0;
    list<Goat> goats;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // Get user choice and run associated function.
    user = main_menu();
    while (user!=4) {
        if (user == 1) {
            add_goat(goats, names, colors);
        }
        else if (user == 2) {
            delete_goat(goats);
        }
        else if (user == 3) {
            display_trip(goats);
        }
        else {
            cout << "Error, enter a valid number 1-4." << endl;
        }
        user = main_menu();
    }
    // Exit if choice is 4.
    if (user == 4) {
        cout << "Exiting program..." << endl;
    }

    return 0;
}

int main_menu() {
    int choice = 0;
    // Print out all possible menu options.
    cout << "\n*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";
    // Loop until user enters valid input.
    while(!(cin >> choice) || (choice != 1 && choice !=2 && choice !=3 && choice !=4)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice, please enter an integer from 1 to 4: ";
    }
    return choice;
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    // Randomly select name, color, and age of the goat.
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE +1);

    // Create a new goat and add it to the list.
    Goat new_goat(name, age, color);
    trip.push_back(new_goat);
}

void display_trip(list<Goat> trip){
    int count = 1;
    // Loop through all the goats in the list and display them.
    for (auto i = trip.begin(); i != trip.end(); i++){
        cout << "\t[" << count << "] " << i->get_name() << " (" << i->get_age() << ", " << i->get_color() << ")" << endl;
        count++;
    }
}

int select_goat(list<Goat> trip) {
    int choice = 0;
    display_trip(trip);
    cout << "Select Goat -> ";
    // Loop until user selects a valid goat.
    while (!(cin >> choice) || choice > trip.size() || choice <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nError invalid input, please enter an integer that corresponds to an existing goat: ";
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    int choice = 0;
    cout << "Select a goat to delete..." << endl;
    // User selects a goat to delete.
    choice = select_goat(trip);
    // Create an iterator.
    auto it = trip.begin();
    // Iterate through the list until the user's choice is reached.
    advance(it, choice-1);
    // Remove that goat from the list.
    trip.erase(it);
}