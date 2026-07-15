# MetroSim — MBTA Green Line Extension Simulator

A command-driven simulation of a train running a simplified loop of the MBTA
Green Line Extension. Passengers wait at stations, board the train, ride to
their destination, and disembark. The program tracks the full state of every
station and the train after each command.

Written in C++ as an exercise in object-oriented design and building an
interactive front end on top of a queue-based back end.

## Build

```bash
make MetroSim
```

The Makefile uses `clang++` by default. To build with `g++` instead:

```bash
make MetroSim CXX=g++
```

## Run

```bash
./MetroSim stationsFile outputFile [commandsFile]
```

- `stationsFile` — input file listing the stations on the line (one per line).
- `outputFile` — file the simulator writes to whenever a passenger leaves the
  train (e.g. `Passenger 1 left train at station Gilman Square`).
- `commandsFile` — *optional*. If given, commands are read from this file
  (batch mode). If omitted, commands are read interactively from standard input.

Sample data files are included, so you can try it immediately:

```bash
# Batch mode — runs the bundled command script
./MetroSim stations.txt out.txt test_commands.txt

# Interactive mode — type commands yourself
./MetroSim stations.txt out.txt
```

## Commands

| Command      | Meaning                                                        |
|--------------|----------------------------------------------------------------|
| `p <from> <to>` | Add a passenger boarding at station `<from>`, bound for `<to>` (station indices). |
| `m m`        | Move the train forward one station (loops back to the start at the end of the line). |
| `m f`        | End the simulation.                                            |

After every command the simulator prints the passengers currently on the train
and the full list of stations, marking the train's current location with
`TRAIN:`.

### Example

Given `stations.txt`:

```
Lechmere
Union Square
Gilman Square
Magoun Square
Ball Square
Medford/Tufts
```

the command `p 0 2` adds passenger 1 at Lechmere (station 0) bound for Gilman
Square (station 2). After two `m m` commands the train reaches Gilman Square,
passenger 1 disembarks, and `out.txt` records:

```
Passenger 1 left train at station Gilman Square
```

## Design

The simulation is split into a small driver, a back-end data model, and the
`MetroSim` class that ties them together.

- **`Passenger`** — a struct holding the passenger's `id`, departure station
  (`from`), and arrival station (`to`).
- **`PassengerQueue`** — a FIFO queue of `Passenger`s, backed by a `vector`.
  Used both for the line waiting at each station and for the train's cars.
- **`Station`** — a struct pairing a station name and number with the
  `PassengerQueue` of people waiting there.
- **`MetroSim`** — owns a `vector<Station>` for the line and a
  `vector<PassengerQueue>` for the train. The train vector is indexed by
  *destination station number*: a passenger riding to station `k` is held in
  train car `k`. When the train arrives at station `k`, everyone in car `k`
  disembarks — no scanning required.

When a passenger is added they enqueue at their departure station. On `m m`,
everyone waiting at the current station boards the train (moving into the car
for their destination), the train advances one stop (wrapping around at the
end), and anyone whose destination matches the new stop leaves the train and is
logged to the output file.

## Files

| File | Purpose |
|------|---------|
| `main.cpp` | Driver: parses arguments, opens files, starts the simulation loop. |
| `MetroSim.h` / `MetroSim.cpp` | The `MetroSim` class — simulation state, command handling, and printing. |
| `Passenger.h` / `Passenger.cpp` | The `Passenger` struct and its print routine. |
| `PassengerQueue.h` / `PassengerQueue.cpp` | FIFO queue of passengers used for stations and train cars. |
| `unit_tests.h` | Unit tests for `Passenger` and `PassengerQueue`. |
| `stations.txt` | Sample stations file (the six GLX stations above). |
| `test_commands.txt` | Sample command script for batch mode. |
| `Makefile` | Build rules. |

## Testing

`Passenger` and `PassengerQueue` are covered by unit tests in `unit_tests.h`
(queue sizes of 0, 1, and 3; repeated `enqueue`/`dequeue`/`front` calls; print
formatting). The end-to-end simulation was validated with diff testing against
a reference implementation across a range of cases: command files ending on
EOF rather than `m f`, arrival stations before/equal to/after departure,
ending the run with passengers still on the train or waiting, and the train
looping the line more than once.
