#include <stdio.h>
#include <stdlib.h>

unsigned long strong(unsigned int n) {
   unsigned long ret = 1;
   do {
      ret *= n;
   } while (--n);
   return ret;
}

/**
 * @brief permutation - Dijksra permutation algorithm
 * @param t - input array
 * @param n - array size
 */
void permutation(int *t, int n)
{
    int i, j, k;

    if (n < 2)
        return;

    i = n - 1;
    while ((i > 0) && (t[i - 1] >= t[i]))
        i--;

    if (i > 0) {
        j = n;
        while ((j > 0) &&(t[j - 1] <= t[i - 1]))
            j--;
    }

    if ((i > 0) && (j > 0)) {
        k = t[i - 1];
        t[i - 1] = t[j - 1];
        t[j - 1] = k;
    }

    for (i++, j = n; i < j; i++, j--) {
        k = t[i - 1];
        t[i - 1] = t[j - 1];
        t[j - 1] = k;
    }
}


/**
 * @brief check - check whether the array meets the conditions
 * @param array - input array
 * @param n - array size
 * @return 1 - array ok, 0 - not ok
 */
int check(int* array, size_t n){
    size_t i;
    int diff1,diff2,res = 1;

    diff1 = array[0] - array[1];
    for (i=1;i<n-1;i++){
        diff2 = array[i]-array[i+1];
        if (diff1 >= diff2) { //change to "diff1 > diff2" if you want not descending
            res = 0;
            break;
        }
        diff1 = diff2;
    }

    return res;
}

/**
 * @brief sort - try find solution
 * @param array - input array
 * @param n - array size
 * @return 1 - ok, 0 - no solution
 */
int sort(int* array,size_t n){

    unsigned long i,max = strong(n);
    int res;
    res = check(array,n);

    if (res == 1)
        return 1;

    for (i = 0; i < max - 1; i++) {
            permutation(array, n);

            res = check(array,n);

            if (res == 1)
                return 1;

        }
    return 0;
}

int main(void){

    char input[10];
    size_t i,arraySize;
    int *array;

    printf("Enter array size (2 - 20): ");
    fgets(input,10,stdin);
    arraySize = atoi(input);

    if (arraySize < 2)
        return -1;

    array = malloc(arraySize * sizeof(int));

    for (i=0;i<arraySize;i++){
        printf("Enter %d. number: ",(i+1));
        fgets(input,10,stdin);
        array[i] = atoi(input);
    }
    printf("\n");

    printf("Input array:\n");
    for (i=0;i<arraySize;i++){
        printf("%d ",array[i]);
    }
    printf("\n");

    if (sort(array,arraySize))
    {
        printf("Solution:\n");
        for (i=0;i<arraySize;i++){
            printf("%d ",array[i]);
        }
        printf("\n");
    } else {
        printf("No solution :(\n");
    }

    free (array);

    return 0;
}

