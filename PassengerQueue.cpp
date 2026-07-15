/*
 *  PassengerQueue.cpp
 *  Charles Man
 *  2/12/23
 *
 *  MetroSim
 *
 *  Purpose: This is the class implemenetation for PassengerQueue. It contains
 *           all definitions for both public and private member functions of
 *           the class.
 *
 */

#include "PassengerQueue.h"

using namespace std;

/* 
 * front
 * purpose: return element at front of queue
 * parameters: none
 * returns: element at front of queue
 */
Passenger PassengerQueue::front() {
    
    return queue[0];

}

/* 
 * dequeue
 * purpose: removes element at front of queue
 * parameters: none
 * returns: none
 */
void PassengerQueue::dequeue() {
    
    queue.erase(queue.begin());

}

/* 
 * enqueue
 * purpose: inserts new element at end of queue
 * parameters: a const reference to a Passenger
 * returns: none
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    
    queue.push_back(passenger);

}

/* 
 * size
 * purpose: determine number of elements in queue
 * parameters: none
 * returns: number of elements currently in queue
 */
int PassengerQueue::size() {
    
    return queue.size();

}

/* 
 * print
 * purpose: prints each Passenger in the PassengerQueue to given output
 *          stream
 * parameters: an ostream reference to the queue output
 * returns: none
 */
void PassengerQueue::print(ostream &output) {
    
    int size = queue.size();

    for (int i = 0; i < size; i++) {
        queue[i].print(output);
    }

}