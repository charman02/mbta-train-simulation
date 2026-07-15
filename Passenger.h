/*
 *  Passenger.h
 *  Charles Man
 *  2/12/23
 *
 *  MetroSim
 *
 *  Purpose: This is the interface for the Passenger struct. It contains
 *           three variables: ID, departure station, and arrival station.
 *           It also contains a default constructor, a constructor that
 *           takes in a given ID and departure/arrival stations as arguments,
 *           and a print function.
 *
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

using namespace std;

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);

};

#endif
