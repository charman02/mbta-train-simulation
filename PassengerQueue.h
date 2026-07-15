/*
 *  PassengerQueue.h
 *  Charles Man
 *  2/12/23
 *
 *  MetroSim
 *
 *  Purpose: This is the class interface for PassengerQueue. It contains all
 *           of the public and private member functions and variables for the
 *           class. The public members can be accessed by the user, while the
 *           private members can only be accessed by other members of the
 *           class.
 *
 */
#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include "Passenger.h"
#include <vector>
#include <iostream>

using namespace std;

class PassengerQueue {
public:
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(ostream &output);
    
private:
    vector<Passenger> queue;

};

#endif
