/*
 *  unit_tests.h
 *  Charles Man
 *  2/2/23
 *
 *  MetroSim
 *
 *  Purpose: This file contains all unit tests for testing the member
 *           functions of the Passenger struct and PassengerQueue class.
 *
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

// Tests print for Passenger using default constructor
void passenger_print_default() {
    Passenger p;
    std::ostringstream os;

    p.print(os);

    assert(os.str() == "[-1, -1->-1]");
}

// Tests print for Passenger using given ID and stations
void passenger_print_arguments() {
    Passenger p(1, 2, 3);
    std::ostringstream os;

    p.print(os);

    assert(os.str() == "[1, 2->3]");

}

// Tests enqueue and front for 1-element queue
void front_enqueue_single() {
    Passenger p(1, 2, 3);
    PassengerQueue pq;
    pq.enqueue(p);
    assert(pq.front().id == 1);
    assert(pq.front().from == 2);
    assert(pq.front().to == 3);
}

// Tests front for 1-element queue using default constructor
void front_single_default() {
    Passenger p;
    PassengerQueue pq;
    pq.enqueue(p);
    assert(pq.front().id == -1);
    assert(pq.front().from == -1);
    assert(pq.front().to == -1);
}

// Tests front for 3-element queue
void front_three_elements() {
    Passenger p1(1, 2, 3);
    Passenger p2(2, 2, 8);
    Passenger p3(3, 5, 6);
    PassengerQueue pq;
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    assert(pq.front().id == 1);
    assert(pq.front().from == 2);
    assert(pq.front().to == 3);
}

// Tests dequeue for 3-element queue
void dequeue_three_elements() {
    Passenger p1(1, 2, 3);
    Passenger p2(2, 2, 8);
    Passenger p3(3, 5, 6);
    PassengerQueue pq;
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    pq.dequeue();
    assert(pq.front().id == 2);
    assert(pq.front().from == 2);
    assert(pq.front().to == 8);
}

// Tests dequeue twice for 3-element queue
void dequeue_twice() {
    Passenger p1(1, 2, 3);
    Passenger p2(2, 2, 8);
    Passenger p3(3, 5, 6);
    PassengerQueue pq;
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    pq.dequeue();
    pq.dequeue();
    assert(pq.front().id == 3);
    assert(pq.front().from == 5);
    assert(pq.front().to == 6);
}

// Tests size for empty queue
void size_empty() {
    PassengerQueue pq;
    assert(pq.size() == 0);
}

// Tests size for 1-element queue
void size_single() {
    Passenger p(1, 2, 3);
    PassengerQueue pq;
    pq.enqueue(p);
    assert(pq.size() == 1);
}

// Tests size for 3-element queue
void size_three_elements() {
    Passenger p1(1, 2, 3);
    Passenger p2(2, 2, 8);
    Passenger p3(3, 5, 6);
    PassengerQueue pq;
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    assert(pq.size() == 3);
}

// Tests print for PassengerQueue 1-element queue
void passengerqueue_print_single() {
    Passenger p(1, 2, 3);
    PassengerQueue pq;
    pq.enqueue(p);
    std::ostringstream os;
    pq.print(os);
    assert(os.str() == "[1, 2->3]");
}

// Tests enqueue and print for PassengerQueue for 3-element queue
void print_enqueue_three_elements() {
    Passenger p1(1, 2, 3);
    Passenger p2(2, 2, 8);
    Passenger p3(3, 5, 6);
    PassengerQueue pq;
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    std::ostringstream os;
    pq.print(os);
    assert(os.str() == "[1, 2->3][2, 2->8][3, 5->6]");
}