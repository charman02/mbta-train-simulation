/*
 *  MetroSim.h
 *  Charles Man
 *  2/12/23
 *
 *  MetroSim
 *
 *  Purpose: This is the class interface for MetroSim. It contains all
 *           of the public and private member functions and variables for the
 *           class. The public members can be accessed by the user, while the
 *           private members can only be accessed by other members of the
 *           class.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "PassengerQueue.h"

using namespace std;

struct Station {
    string stationName;
    int stationNum;
    PassengerQueue stationQueue;
};

class MetroSim {
public:
    template<typename streamtype>
    void open_file(streamtype &stream, string file_name);
    void abort(string error_message, string file_name);
    void run_command_line(ifstream &stationFile, ofstream &outFile);
    void run_command_file(ifstream &stationFile, ofstream &outFile,
        ifstream &commandFile);

private:
    // vector of all stations in simulation
    vector<Station> stationVector;
    // vector of PassengerQueues for each station, representing train
    vector<PassengerQueue> train;
    // vector of Passengers on train representing train queue
    // vector<Passenger> trainQueue;
    // Station pointer representing current station that train is at
    Station *currStation;
    // total number of passengers in simulation
    int numPassengers;
    Station newStation(string newName, int newNum, PassengerQueue newQueue);

    void run_command_helper(string line, ofstream &outFile);
    void print_metrosim();
    void init_metrosim(ifstream &stationFile);
    void print_train_passengers();
    void print_stations();
    void passenger_command(stringstream &input_ss, int departure);
    void add_passenger(const Passenger &passenger);
    void metro_move(ofstream &outFile);
    void remove_passengers(ofstream &outFile);
    void print_remove_passengers(ofstream &outFile, int id, string station);
};

#endif