// CRM in C++
// Alberto Martinez

#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

using namespace std;

void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

UTString bottles = "Bottles";
UTString diapers = "Diapers";
UTString rattles = "Rattles";


/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    UTString str_name;
    UTString item_type;
    int amount;
    int index;

    readString(str_name);
    readString(item_type);
    readNum(amount);

    // before anything make sure possible customer is making a purchase > 0, if not do not add to DB
    if (amount > 0) {
        // now customer is making a real purchase, check if already in database or not

        if (item_type == bottles){
            if (num_bottles < amount){ // check if there's enough inventory for purchase
                cout << "Sorry " << str_name.c_str() << ", we only have " << num_bottles << " Bottles" << endl;
            }
            else {
                database[str_name]; // using function I wrote, customer is now in database and can purchase

                // this gets index of customer, used to add purchase amount of item to customers profile index
                for (int i = 0; database[i].name != "__invalid__"; i++) {
                    if (database[i].name == str_name){
                        index = i;
                        break;
                    }
                }
                database[index].bottles += amount; // updating database
                num_bottles -= amount; // updating inventory
            }
        }

        else if (item_type == diapers){
            if (num_diapers < amount){ // check if enough inventory for purchase
                cout << "Sorry " << str_name.c_str() << ", we only have " << num_diapers << " Diapers" << endl;
            }
            else {
                database[str_name]; // using function I wrote, customer is now in database and can purchase

                // this gets index of customer, used to add purchase amount of item to customers profile index
                for (int i = 0; database[i].name != "__invalid__"; i++) {
                    if (database[i].name == str_name){
                        index = i;
                        break;
                    }
                }
                database[index].diapers += amount; // updating database purchase
                num_diapers -= amount; //updating inventory

            }
        }

        else if (item_type == rattles){
            if (num_rattles < amount){
                cout << "Sorry " << str_name.c_str() << ", we only have " << num_rattles << " Rattles" << endl;
            }
            else {
                database[str_name]; // using function I wrote, customer is now in database and can purchase

                // this gets index of customer, used to add purchase amount of item to customers profile index
                for (int i = 0; database[i].name != "__invalid__"; i++) {
                    if (database[i].name == str_name){
                        index = i;
                        break;
                    }
                }
                database[index].rattles += amount; // updating database
                num_rattles -= amount; // updating inventory
            }
        }

    }
}

void processSummarize() {

    int bottle_flag = 0;
    int diaper_flag = 0;
    int rattle_flag = 0;

    for( int i = 0; i < database.size(); i++){
        if (database[i].bottles > 0){
            bottle_flag = 1;
        }
        if (database[i].diapers > 0){
            diaper_flag = 1;
        }
        if (database[i].rattles > 0){
            rattle_flag = 1;
        }
    }

    Customer c1;

    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and "
    << num_rattles << " Rattles in inventory" << endl;

    cout << "we have had a total of " << database.size() << " different customers" << endl;


    if (bottle_flag == 1) {
        c1 = *findMax(bottles);
        cout << c1.name.c_str() << " has purchased the most Bottles (" << c1.bottles << ")" << endl;
    }
    else {
        cout << "no one has purchased any Bottles" << endl;
    }

    if (diaper_flag == 1) {
        c1 = *findMax(diapers);
        cout << c1.name.c_str() << " has purchased the most Diapers (" << c1.diapers << ")" << endl;
    }
    else{
        cout << "no one has purchased any Diapers" << endl;
    }

    if (rattle_flag == 1) {
        c1 = *findMax(rattles);
        cout << c1.name.c_str() << " has purchased the most Rattles (" << c1.rattles << ")" << endl;
    }
    else{
        cout << "no one has purchased any Rattles" << endl;
    }


}

void processInventory() {

    UTString item_received;
    int total;

    readString(item_received);
    readNum(total);

    if(item_received == bottles){
        num_bottles += total;
    }

    else if (item_received == diapers){
        num_diapers += total;
    }

    else if (item_received == rattles){
        num_rattles += total;
    }
}
