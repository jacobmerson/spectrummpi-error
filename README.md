This is a reproducer to show the MPI failure on dcs with MPI/PCU.

# on AiMOS
The failure requires the use of at least 2 processes.
Running with spectrum-mpi and pumi@2.2.7

run with : mpirun -hostfile hosts.txt -np 2 testmpierror/build/testmpi 2727
Any number of processes below 2727 does not triger the error. Any number of processes above 2727 triggers th error

# On Summit
Using:
  - gcc@11.2.0
  - spectrum-mpi/10.4.0.3-20210112
  - pumi@2.2.7 (also tested error exists with master)
On summit the error is occuring using either 1 or 2 ranks

Running the two rank job as follows gives the error
jsrun -n1  -a 2 -c2 ./testmpi 2726
On summit running with 2726 or greater triggers the error.

With a single rank on summit we can trigger the error with:
jsrun -n1  -a 1 -c1 ./testmpi 4089

## Example Error Message
    [g36n15:210477] Out of resources: all 4095 communicator IDs have been used.
    [g36n15:210477] *** An error occurred in MPI_Comm_dup
    [g36n15:210477] *** reported by process [47,0]
    [g36n15:210477] *** on communicator MPI COMMUNICATOR 6 DUP FROM 0
    [g36n15:210477] *** MPI_ERR_INTERN: internal error
    [g36n15:210477] *** MPI_ERRORS_ARE_FATAL (processes in this communicator will now abort,
    [g36n15:210477] ***    and potentially your MPI job)
