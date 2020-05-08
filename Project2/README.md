# Finding "triple-friends of 10"

Given a 2D table that has M rows and N columns of non-negative integers,
the code finds the total number of “triple-friends of 10”. Here, a “triple-friend
of 10” is defined as three neighboring numbers (in the horizontal, vertical, or
diagonal directions) that sum up to 10.


# Compilation

Compile the code by:
```
$ make all
```

You execute the serialized program by:
```
$ ./program.exe
```

And you execute the parallelized program by:
```
$ mpirun -n num_process ./mpi_program.exe
```
Where the command line argument "num_process" is the number of processes that are initialized in the program.  

# References

https://www.geeksforgeeks.org/
https://www.uio.no/studier/emner/matnat/ifi/IN3200/v20/teaching-material/in3200_in4200_home_exam2_v20.pdf
