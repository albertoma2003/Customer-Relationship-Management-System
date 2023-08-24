// CRM in C++
// Alberto Martinez

#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) {
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // constructor
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) {
    return this->length;
}

CustomerDB::~CustomerDB(void) { // destructor
    delete[] this->data;
}



void CustomerDB::clear(void) {
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) {
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) {
    // if a customer in the customer database has a name that matches the argument operator [], then
    // return a reference to that customer
    // if there is no customer in the database with that name, then add new customer to database and return reference to
    // new customer
    //if you add new customer to database, increase capacity for customer and use amortized doubling to resize the array
    
    for (int i = 0; i < this->length; i++) {

        if (name == this->data[i].name){
            return this->data[i];
        }
    }

    // if customer is not in the database
    if (this->length == this->capacity) {

        int new_len = this->length;
        int new_cap = this->capacity * 2; // amortized doubling
        Customer *new_database = new Customer[new_cap]; // creating new customer object array for database


        // copying contents from old database to new database
        for (int i = 0; i < this->length; i++) {
            new_database[i] = this->data[i];
        }

        delete[] data; // deleting old pointer to avoid memory leaks
        this->data = new_database; // set customer database to new database with updated capacity and length
        this->capacity = new_cap;
        this->length = new_len;
    }

    // initialize new customer data
    this->data[this->length].name = name;
    this->data[this->length].bottles = 0;
    this->data[this->length].diapers = 0;
    this->data[this->length].rattles = 0;
    this->length++;

    return this->data[this->length-1]; // return reference to new customer in database array
}


bool CustomerDB::isMember(UTString name) {
    // return true if it finds a customer with the matching name
    // return false otherwise

    for (int i = 0; i < this->length; i++) {

        if (this->data[i].name == name){
            return true;
        }
    }
     return false; // return false if customer was not found in database

}