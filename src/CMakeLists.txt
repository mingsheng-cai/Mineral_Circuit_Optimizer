# add the genetic algorithm library

file(GLOB OPERATORS_SOURCES "operators/Selection/*.cpp" "operators/Crossover/*.cpp" "operators/Mutation/*.cpp")
add_library(geneticAlgorithm Genetic_Algorithm.cpp ${OPERATORS_SOURCES})
set_target_properties(geneticAlgorithm
        PROPERTIES
        CXX_STANDARD 17
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(geneticAlgorithm PUBLIC OpenMP::OpenMP_CXX)
endif()

# build the circuit simulator as a testable library

file(GLOB CIRCUIT_SOURCES "circuit/*.cpp")
add_library(circuitSimulator CSimulator.cpp ${CIRCUIT_SOURCES})
set_target_properties( circuitSimulator
    PROPERTIES
    CXX_STANDARD 17
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# build the executable

file(GLOB UTIL_SOURCES "utils/*.cpp")
add_executable(Circuit_Optimizer main.cpp ${UTIL_SOURCES})
target_link_libraries(Circuit_Optimizer PUBLIC geneticAlgorithm circuitSimulator)

set_target_properties(Circuit_Optimizer
        PROPERTIES
        CXX_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
