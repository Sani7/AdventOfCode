#include <stdio.h>
#include <stdbool.h>

class quickSort
{
    private:
        void swap(int *n, int num1, int num2);
        int partition(int *n, int left, int right, int pivot);
    public:
        void printline(int count);
        void sort(int *n, int left, int right);
        void display(int *n);
};