#!/bin/bash

clear

rm -rf build/

mkdir -p build

cd build

cmake .. -DCMAKE_C_COMPILER=/opt/homebrew/bin/gcc-13 -DCMAKE_CXX_COMPILER=/opt/homebrew/bin/g++-13

cmake --build .

export OMP_NUM_THREADS=10

echo ">>> Running Circuit Optimizer..."

./bin/Circuit_Optimizer

latest_log_dir=$(ls -td ../log/*/ | head -1)

if [ -z "$latest_log_dir" ]; then
    echo "No log directory found."
    exit 1
fi

log_file=$(find "$latest_log_dir" -type f -name "circuit_info.log")
if [ ! -f "$log_file" ]; then
    echo "Log file not found."
    exit 1
fi

elapsed_time=$(grep "Elapsed time" "$log_file" | awk '{print $3}')
performance=$(grep "Performance" "$log_file" | awk '{print $2}')
recovery=$(grep "Recovery" "$log_file" | awk '{print $2}')
grade=$(grep "Grade" "$log_file" | awk '{print $2}')
configuration=$(grep "Final Circuit Configuration" "$log_file" | awk '{for (i=4; i<=NF; i++) printf "%s ", $i; print ""}')

vector=$(echo "$configuration" | sed 's/[[:space:]]*$//' | sed 's/ /,/g')

#echo "Elapsed time: $elapsed_time"
#echo "Performance: $performance"
#echo "Recovery: $recovery"
#echo "Grade: $grade"
#echo "Configuration: [$vector]"

cd ..

cd post_process

#echo "python3 ./post_process/visualize.py "$latest_log_dir" "\"[$vector]\"" "$performance" "$recovery" "$grade""

echo ">>> Generating circuit diagram..."

#python3 ./post_process/visualize.py "$latest_log_dir" "[$vector]" "$performance" "$recovery" "$grade"
python3 ./visualize.py "[$vector]" "$performance" "$recovery" "$grade"

echo ">>> Circuit diagram saved in './circuit_diagrams' directory."

echo ">>> All done."
