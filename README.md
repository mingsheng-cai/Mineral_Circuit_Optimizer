

<p align="center"> <img src="https://raw.githubusercontent.com/acse-sc4623/img/main/GerardiumRush.png" style="zoom:50%;" /> </p>

[![GerardiumRush](https://img.shields.io/badge/Gerardium%20Rush-Pentlandite-f39f37)](https://github.com/ese-msc-2023/acs-gerardium-rush-pentlandite) [![CMake](https://img.shields.io/badge/CMake-3.10%2B-blue)](https://cmake.org/) [![GCC](https://img.shields.io/badge/GCC-13.0%2B-blue)](https://gcc.gnu.org/) [![G++](https://img.shields.io/badge/G++-13.0%2B-blue)](https://gcc.gnu.org/projects/cxx-status.html) [![OpenMP](https://img.shields.io/badge/OpenMP-4.5%2B-blue)](https://www.openmp.org/) [![Python](https://img.shields.io/badge/Python-3.10%2B-blue)](https://www.python.org/) [![Graphviz](https://img.shields.io/badge/Graphviz-2.50.0%2B-blue)](https://graphviz.org/) [![Matplotlib](https://img.shields.io/badge/Matplotlib-3.8.2%2B-blue)](https://matplotlib.org/) [![Pandas](https://img.shields.io/badge/Pandas-2.1.3%2B-blue)](https://pandas.pydata.org/)

------

This is an implementation for the **ACS - Gerardium Rush** project delivered by group **Pentlandite**. 

This project is designed to optimize circuit configurations using genetic algorithms to enhance the recovery of valuable materials in separation technologies. The goal is to create an efficient and effective tool for optimizing circuits in minerals processing, particularly for the recovery of "gerardium". This project combines the power of genetic algorithms with mass balance simulations to find the optimal circuit configuration.

## 📣 News

[![new](https://github.com/RUCAIBox/RecBole/raw/master/asset/new.gif)](https://github.com/RUCAIBox/RecBole/blob/master/asset/new.gif)**24/05/2024**: Our answer for released challenges is available here: [Challenge Answer - Pentlandite](https://github.com/ese-msc-2023/acs-gerardium-rush-pentlandite/blob/main/docs/Challenge_Answer.ipynb)

[![new](https://github.com/RUCAIBox/RecBole/raw/master/asset/new.gif)](https://github.com/RUCAIBox/RecBole/blob/master/asset/new.gif)**23/05/2024**: Our online API document is available here: [API Document - Pentlandite](https://acse-sc4623.github.io/pentlandite/)

[![new](https://github.com/RUCAIBox/RecBole/raw/master/asset/new.gif)](https://github.com/RUCAIBox/RecBole/blob/master/asset/new.gif)**22/05/2024**: Our exploratory code is available here: [Investigation - Pentlandite](https://github.com/ese-msc-2023/acs-gerardium-rush-pentlandite/tree/main/investigate)

## 🔭 Overview

The project is organized into several key components, each with specific responsibilities:

1. **Circuit Simulation (CSimulator.cpp)**:

   ![CSimulator](https://raw.githubusercontent.com/acse-sc4623/img/main/CSimulator.png)

   - Core simulation logic for evaluating circuit performance
   - Simulates the mass balance for given circuit configurations.
   - Utilizes classes like `CCircuit` and `CUnit` to represent and manage circuit units and their interactions.

2. **Genetic Algorithm (Genetic_Algorithm.cpp)**:

   <img src="https://raw.githubusercontent.com/acse-sc4623/img/main/Operator.png" alt="Operator" style="zoom:80%;" />

   - Implements the genetic algorithm for optimizing circuit configurations.

   - Includes various operators for selection, crossover, and mutation.

   - Parallel processing enabled using OpenMP for efficient computation.

## ✨ Features

- **Genetic Algorithm Optimization**: Efficiently explore numerous circuit configurations using genetic algorithms to find the most effective setups.
- **Mass Balance Simulation**: Simulate the mass balance for each circuit to ensure accurate recovery and grade calculations, ensuring the reliability of the proposed solutions.
- **Parallel Processing**: Leverage OpenMP for faster computations and simulations, enhancing performance and reducing computation time.
- **Comprehensive Unit Tests**: Ensure the correctness of the circuit simulator and genetic algorithm through extensive unit tests, providing a robust and reliable tool.
- **Visualization Tools**: Utilize Python scripts and Jupyter notebooks for post-processing and visualizing the results, helping to analyze and interpret the outcomes effectively.
- **Documentation**: Detailed API documentation and project reports to facilitate understanding and usage, making it easier for users to get started and for developers to extend the project.

## 📋 Requirements

The project uses CMake for building and requires several tools and libraries. Below are the required tools and libraries:

| Tool/Library    | Purpose                               | Version          |
| --------------- | ------------------------------------- | ---------------- |
| **CMake**       | For managing the build process        | 3.10 or higher   |
| **GCC and G++** | For compiling the code                | 13.0 or higher   |
| **OpenMP**      | For parallel processing               | 4.5 or higher    |
| **Python**      | For post-processing and visualization | 3.10 or higher   |
| **Graphviz**    | For generating diagrams               | 2.50.0 or higher |
| **Matplotlib**  | For plotting and visualizing data     | 3.8.2 or higher  |
| **Pandas**      | For data manipulation and analysis    | 2.1.3 or higher  |

To install these requirements on a Debian-based system, you can use the following commands:

```shell
$ sudo apt update
$ sudo apt install cmake gcc g++ libomp-dev python3 python3-pip graphviz
$ pip3 install matplotlib pandas
```

## 🛠️ Installation

To build the project, you need to have CMake and GCC installed on your system.

1. Clone the repository:

   ```shell
   $ git clone https://github.com/yourusername/circuit-optimizer.git
   ```

2. Create a build directory and navigate to it:

   ```shell
   $ mkdir build
   $ cd build
   ```

3. Configure the project using CMake:

   ```shell
   $ cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
   ```

4. Build the project:

   ```shell
   $ cmake --build .
   ```

## 🚀 Usage

**Run Executable**

To run the Circuit Optimizer, execute the following commands from the `build` directory:

```shell
$ export OMP_NUM_THREADS=10
$ ./bin/Circuit_Optimizer
```

**Run Tests**

The project includes a set of unit tests to verify the functionality of the circuit simulator and the genetic algorithm. The tests are located in the `tests` directory.

To run the tests, use the following command:

```shell
$ ctest --output-on-failure
```

**Run Visualization**

To run the visualization tool, use the following command:

```python
$ python3 ../post_process/visualize.py <vector> <performance> <recovery> <grade>
```

**Run Scripts (Recommended)**

Alternatively, you can use the provided shell scripts:

- To run the optimizer, go to the root directory and run the following command:

  ```shell
  $ ./scripts/run.sh
  ```

- To run the tests, go to the root directory and run the following command:

  ```shell
  $ ./scripts/run_test.sh
  ```

You can modify the `OMP_NUM_THREADS` in corresponding shell scripts.

## 🕹️ Parameter Setting

In `src/main.cpp`, you can set the Genetic Algorithm parameters and Circuit Simulator parameters. Here is an example:

```cpp
/** 
 * Genetic algorithm parameters
	*/
int generations = 1000;
int populationSize = 100;
std::string selection = "NaryTournamentSelection";
// std::string selection = "RankSelection";
// std::string selection = "RouletteWheelSelection";
int tournamentSize = 5;
std::string crossover = "TwoPointCrossover";
// std::string crossover = "UniformCrossover";
// std::string crossover = "PureSinglePointCrossover";
double crossRate = 0.8;
std::string mutation = "GuidedMutation";
// std::string mutation = "GenProgMutation";
double mutationRate = 0.1;
double eliteRate = 0.2;
double initialTemp = 1000.0;
double deltT = 0.85;
unsigned int randomSeed = 0;

/** 
 * Circuit simulator parameters
 */
double tolerance = 1e-6;
int maxIteration = 1000;

/**
 * Set up parameters
 */
Algorithm_Parameters ga_params(generations, populationSize, selection, tournamentSize, crossover, crossRate, mutation, mutationRate, eliteRate, initialTemp, deltT, randomSeed);

CircuitParameters c_params(tolerance, maxIteration);
```

**Genetic Algorithm Operators**

- **Selection**:
  - `NaryTournamentSelection`: Selects the best individuals based on tournament competition.
  - `RankSelection`: Selects individuals based on their rank within the population.
  - `RouletteWheelSelection`: Selects individuals based on their fitness proportionally.
- **Crossover**:
  - `TwoPointCrossover`: Combines genes from two parents at two crossover points.
  - `UniformCrossover`: Combines genes from two parents based on a uniform distribution.
  - `PureSinglePointCrossover`: Combines genes from two parents at a single crossover point.
- **Mutation**:
  - `GuidedMutation`: Performs guided mutation based on specific rules or heuristics.
  - `GenProgMutation`: Performs genetic programming mutation by changing operations and parameters.

## 📁 Project Structure

```shell
.
├── CMakeLists.txt                             # Main CMake configuration file for the entire project
├── Doxygen.config                             # Configuration file for generating documentation with Doxygen
├── LICENSE.txt                                # License information for the project
├── README.md                                  # Project's readme file with instructions and documentation
├── build                                      # Build directory containing compiled binaries and test executables
│   ├── bin                                    # Directory for main binary executables
│   │   └── Circuit_Optimizer                  # Main executable for the Circuit Optimizer project
│   └── tests                                  # Directory for test executables and related files
│       ├── bin                                # Binaries for the tests
│       │   ├── test_circuit_simulator         # Test executable for circuit simulator
│       │   ├── test_genetic_algorithm         # Test executable for genetic algorithm
│       │   └── test_validity_checker          # Test executable for validity checker
│       └── ...                                # Other test-related files
├── circuit_diagrams                           # Directory for circuit diagrams
│   └── circuit.png                            # Example circuit diagram image
├── docs                                       # Documentation files
│   ├── API_Document.pdf                       # API documentation in PDF format
│   ├── CCircuit_Document_Analysis.md          # Markdown document with circuit design analysis
│   ├── CCircuit_Document_Analysis.pdf         # PDF document with circuit design analysis
│   ├── Challenge_Answer.ipynb                 # Python notebook with released challenge answer
│   ├── CSimulator_Document_and_Analysis.md    # Markdown document with simulator performance analysis
│   ├── CSimulator_Document_and_Analysis.pdf   # PDF document with simulator performance analysis
│   ├── GeneticAlgorithm_Design_Document.md    # Markdown document with algorithm design illstration
│   ├── GeneticAlgorithm_Design_Document.pdf   # PDF document with algorithm design illstration
│   ├── GeneticAlgorithm_Params_Analysis.md    # Markdown document with algorithm & circuit params analysis
│   ├── GeneticAlgorithm_Params_Analysis.pdf   # Markdown document with algorithm & circuit params analysis
│   ├── Problem_Statement.pdf                  # Project problem statement
│   └── doxygen                                # Directory for Doxygen-generated documentation files
├── include                                    # Header files for the project
│   ├── CSimulator.h                           # Header for the circuit simulator
│   ├── Genetic_Algorithm.h                    # Header for the genetic algorithm
│   ├── circuit                                # Directory for circuit-related headers
│   │   ├── CCircuit.h                         # Header for the circuit class
│   │   └── CUnit.h                            # Header for the unit class
│   ├── operators                              # Directory for operator-related headers
│   │   ├── Crossover                          # Crossover operator headers
│   │   │   ├── PureSinglePointCrossover.h     # Header for pure single point crossover
│   │   │   ├── TwoPointCrossover.h            # Header for two-point crossover
│   │   │   └── UniformCrossover.h             # Header for uniform crossover
│   │   ├── Mutation                           # Mutation operator headers
│   │   │   ├── GenProgMutation.h              # Header for genetic programming mutation
│   │   │   └── GuidedMutation.h               # Header for guided mutation
│   │   └── Selection                          # Selection operator headers
│   │       ├── NaryTournamentSelection.h      # Header for N-ary tournament selection
│   │       ├── RankSelection.h                # Header for rank selection
│   │       └── RouletteWheelSelection.h       # Header for roulette wheel selection
│   └── utils                                  # Utility headers
│       ├── Helper.h                           # Header for helper functions
│       ├── Individual.h                       # Header for individual class
│       ├── Parameter.h                        # Header for parameter handling
│       └── tqdm.hpp                           # Header for progress bar utility
├── investigate                                # Directory for investigation scripts and logs
│   ├── CCircuit.cpp                           # Circuit source file for investigation
│   ├── evaluate_circuit.ipynb                 # Jupyter notebook for evaluating circuits
│   ├── evaluate_circuit_time.ipynb            # Jupyter notebook for evaluating circuit times
│   ├── execution_times.txt                    # Log file for execution times
│   └── timings_thread.log                     # Log file for thread timings
├── log                                        # Directory for log files
│   └── 2024-05-23_21-28-04                    # Log directory with timestamp
│       └── circuit_info.log                   # Log file for circuit information
├── post_process                               # Directory for post-processing scripts
│   ├── visualize.ipynb                        # Jupyter notebook for visualization
│   └── visualize.py                           # Python script for visualization
├── scripts                                    # Shell scripts for running the project
│   ├── run.sh                                 # Script to run the main optimizer
│   └── run_test.sh                            # Script to run the tests
├── src                                        # Source code for the project
│   ├── CMakeLists.txt                         # CMake configuration file for source code
│   ├── CSimulator.cpp                         # Source file for the circuit simulator
│   ├── Genetic_Algorithm.cpp                  # Source file for the genetic algorithm
│   ├── circuit                                # Directory for circuit-related source files
│   │   ├── CCircuit.cpp                       # Source file for the circuit class
│   │   └── CUnit.cpp                          # Source file for the unit class
│   ├── main.cpp                               # Main source file for the project
│   ├── operators                              # Directory for operator-related source files
│   │   ├── Crossover                          # Crossover operator source files
│   │   │   ├── PureSinglePointCrossover.cpp   # Source file for pure single point crossover
│   │   │   ├── TwoPointCrossover.cpp          # Source file for two-point crossover
│   │   │   └── UniformCrossover.cpp           # Source file for uniform crossover
│   │   ├── Mutation                           # Mutation operator source files
│   │   │   ├── GenProgMutation.cpp            # Source file for genetic programming mutation
│   │   │   └── GuidedMutation.cpp             # Source file for guided mutation
│   │   └── Selection                          # Selection operator source files
│   │       ├── NaryTournamentSelection.cpp    # Source file for N-ary tournament selection
│   │       ├── RankSelection.cpp              # Source file for rank selection
│   │       └── RouletteWheelSelection.cpp     # Source file for roulette wheel selection
│   └── utils                                  # Utility source files
│       └── Helper.cpp                         # Source file for helper functions
└── tests                                      # Test files
    ├── CMakeLists.txt                         # CMake configuration file for tests
    ├── test_circuit_simulator.cpp             # Test file for circuit simulator
    ├── test_circuit_time.cpp                  # Test file for circuit timing
    ├── test_genetic_algorithm.cpp             # Test file for genetic algorithm
    └── test_validity_checker.cpp              # Test file for validity checker

```

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add new feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Create a new Pull Request.

## 📜 License

This project is licensed under the MIT License. See the [LICENSE.txt](https://github.com/ese-msc-2023/acs-gerardium-rush-pentlandite/blob/main/LICENSE.txt) file for more details.
