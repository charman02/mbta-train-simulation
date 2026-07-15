/*
 *  main.cpp
 *  Charles Man
 *  2/12/23
 *
 *  MetroSim
 *
 *  Purpose: This is the Main file that handles simple driver functions such
 *           as opening and reading in given input files.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MetroSim.h"
#include "Passenger.h"

using namespace std;

int main(int argc, char *argv[])
{
        MetroSim ride;
        if (not ((argc == 3) or (argc == 4))) {
                ride.abort("Usage: ./MetroSim stationsFile outputFile "
                "[commandsFile]", "");
        }

        // argc == 3 or 4
        else {
                ifstream station_file;
                ofstream outFile;

                ride.open_file(station_file, argv[1]);
                ride.open_file(outFile, argv[2]);

                if (argc == 3) {
                        ride.run_command_line(station_file, outFile);
                }

                // argc == 4
                else {
                        ifstream command_file;
                        ride.open_file(command_file, argv[3]);
                        ride.run_command_file(station_file, outFile,
                                command_file);
                        command_file.close();
                }

                station_file.close();
                outFile.close();

        }
};