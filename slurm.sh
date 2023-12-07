#!/bin/bash

####### specify cluster configuration
#SBATCH --cluster=ub-hpc
#SBATCH --partition=general-compute
#SBATCH --qos=general-compute

####### select resources (here we specify required memory)
#SBATCH --mem=8000
#SBATCH --constraint=AVX512

####### make sure no other jobs are assigned to your nodes
#SBATCH --exclusive

####### further customizations
### name of your job
#SBATCH --job-name="changeme"

### files to store stdout and stderr (%j will be replaced by the job id)
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

### how many nodes to allocate for the job
### for shared memory jobs we need only one node
#SBATCH --nodes=1

### how many cores to use on each node
#SBATCH --ntasks-per-node=16

### max time the job will run
#SBATCH --time=00:08:00


# here go regular commands, these commands will be run
# on the first node allocated to the job
hostname

# in the similar way we run OMP app
# tasket limits the number of cores we are going to use
echo "------with 2 processing units-------"
echo "n = 2000, m = 4000"
taskset -c 0-1 ./a1 2000 4000
echo "n = 4000, m = 4000"
taskset -c 0-1 ./a1 4000 4000
echo "n = 8000, m = 4000"
taskset -c 0-1 ./a1 8000 4000
echo "n = 12000, m = 4000"
taskset -c 0-1 ./a1 12000 4000
echo "n = 8000, m = 8000"
taskset -c 0-1 ./a1 8000 8000
echo "-------end of p = 2-----------------"

echo "------with 4 processing units-------"
echo "n = 2000, m = 4000"
taskset -c 0-3 ./a1 2000 4000
echo "n = 4000, m = 4000"
taskset -c 0-3 ./a1 4000 4000
echo "n = 8000, m = 4000"
taskset -c 0-3 ./a1 8000 4000
echo "n = 12000, m = 4000"
taskset -c 0-3 ./a1 12000 4000
echo "n = 8000, m = 8000"
taskset -c 0-3 ./a1 8000 8000
echo "-------end of p = 4-----------------"

echo "------with 8 processing units-------"
echo "n = 2000, m = 4000"
taskset -c 0-7 ./a1 2000 4000
echo "n = 4000, m = 4000"
taskset -c 0-7 ./a1 4000 4000
echo "n = 8000, m = 4000"
taskset -c 0-7 ./a1 8000 4000
echo "n = 12000, m = 4000"
taskset -c 0-7 ./a1 12000 4000
echo "n = 8000, m = 8000"
taskset -c 0-7 ./a1 8000 8000
echo "-------end of p = 8-----------------"

echo "------with 12 processing units-------"
echo "n = 2000, m = 4000"
taskset -c 0-11 ./a1 2000 4000
echo "n = 4000, m = 4000"
taskset -c 0-11 ./a1 4000 4000
echo "n = 8000, m = 4000"
taskset -c 0-11 ./a1 8000 4000
echo "n = 12000, m = 4000"
taskset -c 0-11 ./a1 12000 4000
echo "n = 8000, m = 8000"
taskset -c 0-11 ./a1 8000 8000
echo "-------end of p = 12-----------------"

echo "------with 16 processing units-------"
echo "n = 2000, m = 4000"
taskset -c 0-15 ./a1 2000 4000
echo "n = 4000, m = 4000"
taskset -c 0-15 ./a1 4000 4000
echo "n = 8000, m = 4000"
taskset -c 0-15 ./a1 8000 4000
echo "n = 12000, m = 4000"
taskset -c 0-15 ./a1 12000 4000
echo "n = 8000, m = 8000"
taskset -c 0-15 ./a1 8000 8000
echo "-------end of p = 16-----------------"

