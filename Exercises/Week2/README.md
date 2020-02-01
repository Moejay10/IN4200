# Week 2 of Exercises


## Exercise 1)
Coming up with a "fair" test of the read/write speed of ASCII vs. binary is not as easy as it sounds. There are several different ways to read and write to files, both ASCII and binary in C.

Some possible functions you can use are:
```C
// Write:
// ASCII:
int fprintf (FILE *stream, const char *format, ... );
int fputs (const char *str, FILE *stream );
// Binary:
size_t fwrite (const void *ptr, size_t size, size_t count, FILE * stream);

// Read:
// ASCII:
int fscanf(FILE *stream, const char *format, ...);
char *fgets(char *str, int n, FILE *stream);
// Binary:
size_t fread (void *ptr, size_t size, size_t count, FILE *stream);
```

In the `fopen()` function you can specify if you want to open the file for writing ASCII, `"w", "r+"` or binary `"wb", "rb+"`. The different read/write methods does not care about the mode the file was opened in. The flag is only information for the operating system so some minor optimizations can be done depending on the mode. Eg. opening in binary mode and using `fprintf()` to write to the file will still write ASCII.

## Exercise 2)
The `memcpy()` function is defined in the `<string.h>` library and is called:
```C
void *memcpy (void * destination, const void * source, size_t num);
```
The `num` argument is the number of bytes to be copied.

Here is an example using memcpy
```C
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[])

    /* Create two arrays to hold our data */
    char original[10];
    char newcopy[10];

    /* Copy a string into the original array */
    strcpy(original, "Memcpy");

    /* Copy the first 7 characters of the original
     array into the newcopy array */
    memcpy(newcopy, original, 7);

    /* Set the character at position 24 to a null (char 0)
     in the newcopy array to ensure the string is terminated
     (This is important since memcpy does not initialize memory
     and printf expects a null at the end of a string) */
    newcopy[10] = 0;

    /* Display the contents of the new copy */
    printf("%s\n", newcopy);

    return 0;
```

## Exercise 3)
When compiling Ex3.c remember to compile it with the "-lm" command.
If not done so you will get the error message:
<undefined reference to sin
collect2: error: ld returned 1 exit status>

## Exercise 4)
We can simply count the number of operations needed to do one step in our algorithm.

\(u_{i,j,k} = v_{i,j,k} + \frac{v_{i-1,j,k} + v_{i,j-1,k} + v_{i,j,k-1} - 6v_{i,j,k} + v_{i+1,j,k} + v_{i,j+1,k} + v_{i,j,k+1}}{6}\)

There are 9 floating point operations here. 7 add/subtract and 2 multiply (if you code the division as a multiplication, any reason for doing this?).

We need to do this over all the inner indexes, which means \(9(n_x-2)(n_y-2)(n_z-2)\) FLOP for one iteration. Finally we can multiply with the number of iterations and divide by the total time to get the FLOPS.

\(\text{FLOPS} = \frac{9N(n_x-2)(n_y-2)(n_z-2)}{T}\)
