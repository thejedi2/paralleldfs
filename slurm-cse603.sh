#!/bin/bash

### Make sure that nodes are exclusive for you
#SBATCH --exclusive
#SBATCH --partition=debug
#SBATCH --constraint=CPU-E5-2660

### Set number of nodes and number of cores per node
### and max time for the job (hh:mm:ss)
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=0:25:00
###SBATCH --mem=64000
#SBATCH --job-name="gaddi"
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

### Load CILK required modules
module load boost/1.59.0
module load cilk/5.4.6
module load intel/16.0
module load intel-tbb/2016
module load gcc/4.9.2

###g++ oldserial.cpp -std=c++11
###./a.out 

# snoop composer path
COMPOSER=`echo $LD_LIBRARY_PATH | tr ':' '\n' | grep 'intel/composer' | tr '/' '\n' | grep composer`
TBB_LIB=$INTEL/$COMPOSER/tbb/lib/intel64/gcc4.4
TBB_INC=$INTEL/$COMPOSER/tbb/include

g++ -fcilkplus -std=c++11 -I $TBB_INC -c cilkcode.cpp

g++ -fcilkplus -o ck1 cilkcode.o -L $TBB_LIB -ltbb
export CILK_NWORKERS=8
###export OMP_NUM_THREADS=2
./ck1
