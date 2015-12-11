# Parallel Depth-First Search for Shared Memory using Cilk
Implemented a parallel formulation of the Depth-First Search Graph traversal algorithm using the Cilk API

Files:

cilkcode.cpp - parallel project code
serial.cpp - serial code
slurm-cse603.sh - ccr slurm script for parallel and serial implementations

edits:
cilkcode.cpp - change global variable cores to number of cores the code running on.
            - change read file
            - change NODE_SIZE according to graph size

serial.cpp - change read file
           - change NODE_SIZE according to graph size

slurm-cse603.sh - change number of cilk nworkers according to the number of cores the code should run on.
