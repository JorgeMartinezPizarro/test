#include <unistd.h>

void print_number(int* number, int n) {
    int i;
    int c;

    i = 0;
    while (i < n) {
        c = '0' + number[i];
        c = write(1, &c, 1);
        i++;
    }
    c = write(1, " ", 1);
    return;
}

// Return 0 if the number is the last one, 1 otherwise.
int next_number(int* number, int n) {
    int i;
    int j;
    
    i = n - 1;
    // Obtain the first index that can be increased counting from the end
    while (i >= 0 && number[i] == 9 - n + i + 1) {
        i--;
    }
    // If no index can be increased return false (0)
    if (i == -1) 
        return (0);
    // We get the next element by increasing number
    number[i]++;
    j = i + 1;
    while (j < n) {
        number[j] = number[j - 1] + 1;
        j++;
    }
    // We increased the value, return true (1)
    return (1);
}

void print_combinations(int n) {
    int number[n];
    int i;

    i = 0;
    while (i++ < n) 
        number[i-1] = i-1;
    print_number(number, n);
    while (next_number(number, n) == 1) 
        print_number(number, n);
    
    return;
}