#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    /* Create a place to store our results */

    /* The number of indices in the arrays */
    int n = 20;

    /* Create arrays to hold our data */
    char a[n]; // Original - String
    char b[n]; // Hand-coded copy - String
    char newcopy[n]; // Memcpy - String

    char a1[n]; // Original - Numbers
    char b1[n]; // Hand-coded copy - Numbers
    char newcopy1[n]; // Memcpy - Numbers


    /* Copy a string into the original array */
    strcpy(a, "Hello World");

    /* Hand-coded copy opertion between two arrays */
    for (int i = 0; i < n; i++){
      b[i] = a[i];
      a1[i] = i;
      b1[i] = a1[i];
    }

    /* Copy the first 24 characters of the original
     array into the newcopy array */
    memcpy(newcopy, a, n);
    memcpy(newcopy1, a1, n);


    /* Set the character at position 10 to a null (char 0)
     in the newcopy array to ensure the string is terminated
     (This is important since memcpy does not initialize memory
     and printf expects a null at the end of a string) */
    //newcopy[10] = 0;

    /* Display the contents of the new copy (Numbers) */
    printf("Original: %d \n", a1[n/2]);
    printf("Hand-coded copy: %d \n", b1[n/2]);
    printf("Memcpy: %d \n", newcopy1[n/2]);



    /* Display the contents of the new copy (String) */

    printf("Original: %s \n", a);
    printf("Hand-coded copy: %s \n", b);
    printf("Memcpy: %s \n", newcopy);


    return 0;
}
