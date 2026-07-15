/*
 *  MetroSim.cpp
 *  Charles Man
 *  2/12/23
 *
 *  MetroSim
 *
 *  Purpose: This is the class implemenetation for MetroSim. It contains the
 *           main functionality of running MetroSim, moving trains and
 *           dealing with passengers going on and off the train.
 */

#include "MetroSim.h"
#include <sstream>

using namespace std;

/* 
 * open_file
 * purpose: calls open on given file and calls abort if it fails
 * parameters: stream of some type and file name
 * returns: none
 */
template<typename streamtype>
void MetroSim::open_file(streamtype &stream, string file_name) {
    
    stream.open(file_name);
    
    if (not stream.is_open()) {
        abort("Error: could not open file ", file_name);
    }

}

/* 
 * abort
 * purpose: sends error message to cerr and calls exit
 * parameters: error message and file name
 * returns: none
 */
void MetroSim::abort(string error_message, string file_name) {
        
    cerr << error_message << file_name << endl;
    exit(EXIT_FAILURE);

}

/* 
 * run_command_line
 * purpose: run MetroSim loop for commands given through command line
 * parameters: references to input (station) and output files
 * returns: none
 */
void MetroSim::run_command_line(ifstream &stationFile, ofstream &outFile) {
    
    init_metrosim(stationFile);
    print_metrosim();

    string line;

    while (line != "m f") {
        getline(cin, line);
        run_command_helper(line, outFile);
    }

    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;

}

/* 
 * run_command_file
 * purpose: run MetroSim for commands given through command file by calling
 *          init_metrosim, print_metrosim, and run_command_helper
 * parameters: reference to input (stations and commands) and output files
 * returns: none
 */
void MetroSim::run_command_file(ifstream &stationFile, ofstream &outFile,
ifstream &commandFile) {
    
    init_metrosim(stationFile);
    print_metrosim();

    string line;
    
    while (not getline(commandFile, line).fail() and line != "m f") {
        run_command_helper(line, outFile);
    }

    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/* 
 * run_command_helper
 * purpose: run MetroSim for given command by calling add_passenger or
 *          metro_move
 * parameters: a line of type string representing given command, and
 *             reference to an output file
 * returns: none
 */
void MetroSim::run_command_helper(string line, ofstream &outFile) {
    char first_command;
    stringstream input_ss(line);
    input_ss >> first_command;

    if (first_command == 'p') {
        int departure, arrival;
        input_ss >> departure >> arrival;
        add_passenger(Passenger(numPassengers + 1, departure, arrival));
        print_metrosim();
    }

    // first_command == 'm'
    else {
        char second_command;
        input_ss >> second_command;
        if (second_command == 'm') {
            metro_move(outFile);
            print_metrosim();
        }
    }
}

/* 
 * print_metrosim
 * purpose: print state of simulation
 * parameters: none
 * returns: none
 */
void MetroSim::print_metrosim() {

    print_train_passengers();
    print_stations();

    cout << "Command? ";
    
}

/* 
 * init_metrosim
 * purpose: initialize stations vector, train vector, current station, and
 *          total number of passengers
 * parameters: reference to input (station) file
 * returns: none
 */
void MetroSim::init_metrosim(ifstream &stationFile) {

    string line;

    // initialize station and train vectors
    for (int i = 0; not getline(stationFile, line).fail(); i++) {
        PassengerQueue empty_queue;
        stationVector.push_back(newStation(line, i, empty_queue));
        train.push_back(empty_queue);
    }

    // initalize current station and total number of passengers
    currStation = &stationVector[0];
    numPassengers = 0;

}

/* 
 * newStation
 * purpose: create a new Station struct
 * parameters: station name, number, and PassengerQueue
 * returns: new Station struct
 */
Station MetroSim::newStation(string newName, int newNum,
PassengerQueue newQueue) {

    Station new_station;
    new_station.stationName = newName;
    new_station.stationNum = newNum;
    new_station.stationQueue = newQueue;
    return new_station;

}

/* 
 * print_train_passengers
 * purpose: print passengers on train to cout
 * parameters: none
 * returns: none
 */
void MetroSim::print_train_passengers() {

    int train_size = train.size();
    cout << "Passengers on the train: {";

    for (int i = 0; i < train_size; i++) {
        train[i].print(cout);
    }

    cout << "}" << endl;
    
}

/* 
 * print_stations
 * purpose: print all stations, passengers at each station, and current
 *          location of train
 * parameters: none
 * returns: none
 */
void MetroSim::print_stations() {
    
    string line;
    int station_size = stationVector.size();

    // loop through and print stations in file
    for (int i = 0; i < station_size; i++) {
        
        // print current location of train
        if (i == currStation->stationNum) {
            cout << "TRAIN: ";
        } else {
            cout << "       ";
        }

        cout << "[" << i << "] " << stationVector[i].stationName << " {";
        stationVector[i].stationQueue.print(cout);
        cout << "}" << endl;
    }
}

/* 
 * passenger_command
 * purpose: implements command to add given passenger to simulation by
 *          calling add_passenger
 * parameters: reference to input stringstream and passenger's departure
 *             station
 * returns: none
 */
void MetroSim::passenger_command(stringstream &input_ss, int departure) {
    
    int arrival;
    input_ss >> arrival;
    add_passenger(Passenger(numPassengers + 1, departure, arrival));

}

/* 
 * add_passenger
 * purpose: add passenger to simulation and update number of passengers
 * parameters: const reference to a Passenger
 * returns: none
 */
void MetroSim::add_passenger(const Passenger &passenger) {
    
    stationVector[passenger.from].stationQueue.enqueue(passenger);
    numPassengers++;
    
}

/* 
 * metro_move
 * purpose: moves train to next station
 * parameters: reference to an output file
 * returns: none
 */
void MetroSim::metro_move(ofstream &outFile) {

    int station_queue_size = currStation->stationQueue.size();
    int currNum = currStation->stationNum;
    int numStations = stationVector.size();

    // add PassengerQueue at current station to train
    for (int i = 0; i < station_queue_size; i++) {
        Passenger front_p = currStation->stationQueue.front();
        train[front_p.to].enqueue(front_p);
        currStation->stationQueue.dequeue();
    }
    
    // update currStation to next Station
    if (currStation->stationNum == numStations - 1) {
        currStation = &stationVector[0];
    } else {
        currStation = &stationVector[currNum + 1];
    }

    remove_passengers(outFile);

}

/* 
 * remove_passengers
 * purpose: removes passengers from train if current station is their arrival
 *          station
 * parameters: reference to an output file
 * returns: none
 */
void MetroSim::remove_passengers(ofstream &outFile) {

    int currSize = train[currStation->stationNum].size();

    // dequeue passengers from train vector
    for (int i = 0; i < currSize; i++) {
        print_remove_passengers(outFile,
        train[currStation->stationNum].front().id, currStation->stationName);
        train[currStation->stationNum].dequeue();
    }

}

/* 
 * print_remove_passengers
 * purpose: print every passenger that leaves train to given output file
 * parameters: reference to an output file, passenger ID and arrival station
 * returns: none
 */
void MetroSim::print_remove_passengers(ofstream &outFile, int id,
string station) {

    outFile << "Passenger " << id << " left train at station " << station;
    outFile << endl;

}

// explicit template declaration to solve linker errors
template void MetroSim::open_file<ifstream>(ifstream &stream, string
    file_name);
template void MetroSim::open_file<ofstream>(ofstream &stream, string
    file_name);