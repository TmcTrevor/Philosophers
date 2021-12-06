#include "Philo.h"
int main()
{
    int *a;

    a = (int*)malloc(15 * sizeof(int));
    int i = 20;
    while (i >= 0)
    {
        a[i] = 15;
        i--;
    }
    free(a);
}