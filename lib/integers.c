#include <unistd.h>

void    print_number(int* number, int n) 
{
    int i;
    int c;  

    i = 0;
    while (i++ < n)
    {
        c = '0' + number[i - 1];
        c = write(1, &c, 1);
    }
    c = write(1, " ", 1);
    return;
}

int next_number(int* number, int n) 
{
    int i;
    
    i = n - 1;
    while (i >= 0 && number[i] == 9 - n + i + 1) 
        i--;
    if (i == -1) 
        return (0);
    number[i]++;
    i++;
    while (i++ < n) 
        number[i - 1] = number[i - 2] + 1;
    return (1);
}

void    print_combinations(int n) 
{
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