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
#SBATCH --nodes=4

### how many cores to use on each node
#SBATCH --ntasks-per-node=8

### max time the job will run
#SBATCH --time=00:08:00

# load module intel which provides Intel MPI
# this code is Intel MPI specific
module load intel
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

# run MPI code in parallel on all requested nodes/cores
srun --mpi=pmi2 ./mpi-test

echo "RUNNING ONLY HOSTNAME:"
hostname

echo "RUNNING SRUN HOSTNAME:"
srun hostname
