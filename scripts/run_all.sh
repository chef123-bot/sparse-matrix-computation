#!/bin/bash

echo "=== Building all versions ==="
make clean
make all

echo -e "\n=== Running Serial Version ==="
./build/serial_compute 500

echo -e "\n=== Running OpenMP Version ==="
export OMP_NUM_THREADS=4
./build/openmp_compute 500 4

echo -e "\n=== Running MPI Version ==="
mpirun -np 4 ./build/mpi_compute 500

echo -e "\n=== Scalability Tests ==="
echo "OpenMP with different thread counts:"
for threads in 1 2 4 8; do
    echo "Threads: $threads"
    OMP_NUM_THREADS=$threads ./build/openmp_compute 500 $threads 2>/dev/null | grep "execution time"
done

echo -e "\nMPI with different process counts:"
for procs in 1 2 4 8; do
    echo "Processes: $procs"
    mpirun -np $procs ./build/mpi_compute 500 2>/dev/null | grep "Execution time"
done
