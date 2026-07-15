/*
 *  Passenger.cpp
 *  Charles Man
 *  2/12/23
 *
 *  MetroSim
 *
 *  Purpose: This is the implementation for the print function of the
 *           Passenger struct.
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

using namespace std;

/* 
 * print
 * purpose: print ID, arrival station, and departure station of passenger
 * parameters: an ostream reference to a passenger
 * returns: none
 */
void Passenger::print(ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
