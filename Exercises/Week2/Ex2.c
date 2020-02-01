#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    /* Create a place to store our results */
    double result;

    /* The number of indices in the arrays */
    int n = 10;

    /* Create arrays to hold our data */
    double a[n]; // Original
    double b[n]; // Hand-coded copy

    double newcopy[n]; // Copied using mempcy

    /* Hand-coded copy opertion between two arrays */
    for (int i = 0; i < n; i++){
      a[i] = i;
      b[i] = a[i];
    }

    /* Copy a string into the original array
    strcpy(a, "C memcpy at TechOnTheNet.com");*/

    /* Copy the first 24 characters of the original
     array into the newcopy array */
    memcpy(newcopy, a, n);

    /* Set the character at position 10 to a null (char 0)
     in the newcopy array to ensure the string is terminated
     (This is important since memcpy does not initialize memory
     and printf expects a null at the end of a string) */
    //newcopy[10] = 0;

    /* Display the contents of the new copy */
    printf("%f \n", a[9]);
    printf("%f \n", b[9]);
    printf("%f \n", newcopy[9]);

    return 0;
}
