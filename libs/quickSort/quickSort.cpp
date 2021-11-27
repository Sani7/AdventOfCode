#include "quickSort.h"

//#define DEBUG

#ifdef DEBUG
#define dprintf(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dprintf(fmt, ...)
#endif

#define MAX 10

#ifdef TEST
int main(void)
{
    quickSort QuickSort;
    int intArray[MAX] = {4, 6, 3, 2, 1, 9, 7, 5, 8};
    dprintf("Input Array: ");
    QuickSort.display(intArray);
    QuickSort.printline(50);
    QuickSort.sort(intArray, 0, MAX - 1);
    QuickSort.printline(50);
    dprintf("Output Array: ");
    QuickSort.display(intArray);
}
#endif

void quickSort::printline(int count)
{
    int i;

    for (i = 0; i < count - 1; i++)
    {
        dprintf("=");
    }

    dprintf("=\n");
}

void quickSort::display(int *n)
{
    int i;
    dprintf("[");

    // navigate through all items
    for (i = 0; i < MAX; i++)
    {
        dprintf("%d ", n[i]);
    }

    dprintf("]\n");
}

void quickSort::swap(int *n, int num1, int num2)
{
    int temp = n[num1];
    n[num1] = n[num2];
    n[num2] = temp;
}

int quickSort::partition(int *n, int left, int right, int pivot)
{
    int leftPointer = left - 1;
    int rightPointer = right;

    while (true)
    {
        while (n[++leftPointer] < pivot);

        while (rightPointer > 0 && n[--rightPointer] > pivot);
        
        if (leftPointer >= rightPointer)
            break;
            
        else
        {
            dprintf(" item swapped:\t%d,%d\n", n[leftPointer], n[rightPointer]);
            swap(n, leftPointer, rightPointer);
        }
    }

    dprintf(" pivot swapped:\t%d,%d\n", n[leftPointer], n[right]);
    swap(n, leftPointer, right);
    dprintf("Updated Array: ");
    display(n);
    return leftPointer;
}

void quickSort::sort(int *n, int left, int right)
{
    if (right - left <= 0)
        return;

    else
    {
        int pivot = n[right];
        int partitionPoint = partition(n, left, right, pivot);
        sort(n, left, partitionPoint - 1);
        sort(n, partitionPoint + 1, right);
    }
}
