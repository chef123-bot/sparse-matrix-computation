## Test System
- Ubuntu 22.04
- 8-core CPU
- 16GB RAM=== Running Serial Version ===
=== Serial Implementation ===
Matrix size: 500x500

Results:
Execution time: 0.002584 seconds
Denominator (X·X): 165.932159
First 5 elements of a:
  a[0] = 0.004638
  a[1] = 0.003702
  a[2] = 0.001386
  a[3] = 0.004260
  a[4] = 0.000987

=== Running OpenMP Version ===
=== OpenMP Implementation ===
Matrix size: 500x500, Threads: 4
Thread 1 created matrix I
Thread 3 created vector X
Thread 2 created matrix C
Thread 0 created matrix B

Results:
OpenMP execution time: 0.020442 seconds
Speedup compared to serial (theoretical): 2.50x

=== Running MPI Version ===
=== MPI Implementation ===
Processes: 1, Matrix size: 500x500
Execution time: 0.001282 seconds
Global dot product: 148.803342

Amdahl's Law Analysis:
  Processes: 1, Theoretical Speedup: 1.00x
  Processes: 2, Theoretical Speedup: 1.54x
  Processes: 4, Theoretical Speedup: 2.11x
  Processes: 8, Theoretical Speedup: 2.58x
=== MPI Implementation ===
Processes: 1, Matrix size: 500x500
Execution time: 0.001290 seconds
Global dot product: 148.803342

Amdahl's Law Analysis:
  Processes: 1, Theoretical Speedup: 1.00x
  Processes: 2, Theoretical Speedup: 1.54x
  Processes: 4, Theoretical Speedup: 2.11x
  Processes: 8, Theoretical Speedup: 2.58x
=== MPI Implementation ===
Processes: 1, Matrix size: 500x500
Execution time: 0.001296 seconds
Global dot product: 148.803342

Amdahl's Law Analysis:
  Processes: 1, Theoretical Speedup: 1.00x
  Processes: 2, Theoretical Speedup: 1.54x
  Processes: 4, Theoretical Speedup: 2.11x
  Processes: 8, Theoretical Speedup: 2.58x
=== MPI Implementation ===
Processes: 1, Matrix size: 500x500
Execution time: 0.001282 seconds
Global dot product: 148.803342

Amdahl's Law Analysis:
  Processes: 1, Theoretical Speedup: 1.00x
  Processes: 2, Theoretical Speedup: 1.54x
  Processes: 4, Theoretical Speedup: 2.11x
  Processes: 8, Theoretical Speedup: 2.58x

=== Scalability Tests ===
OpenMP with different thread counts:
Threads: 1
OpenMP execution time: 0.002584 seconds
Threads: 2
OpenMP execution time: 0.022900 seconds
Threads: 4
OpenMP execution time: 0.011740 seconds
Threads: 8
OpenMP execution time: 0.008569 seconds

MPI with different process counts:
Processes: 1
Execution time: 0.000055 seconds
Processes: 2
Execution time: 0.000063 seconds
Execution time: 0.000035 seconds
Processes: 4
Execution time: 0.000040 seconds
Execution time: 0.000036 seconds
Execution time: 0.000037 seconds
Execution time: 0.000037 seconds
Processes: 8
Execution time: 0.000039 seconds
Execution time: 0.000047 seconds
Execution time: 0.000047 seconds
Execution time: 0.000381 seconds
Execution time: 0.000037 seconds
Execution time: 0.000033 seconds
Execution time: 0.000041 seconds
Execution time: 0.000048 seconds
