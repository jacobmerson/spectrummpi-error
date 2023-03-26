This is a reproducer to show the MPI failure on dcs with MPI/PCU.

The failure requires the use of at least 2 processes.

run with : mpirun -hostfile hosts.txt -np 2 testmpierror/build/testmpi 2727
Any number of processes below 2727 does not triger the error. Any number of processes above 2727 triggers th error
