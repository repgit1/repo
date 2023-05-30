#include <omp.h>
#include <stdlib.h>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void merge(int arr[], int left[], int left_size, int right[], int right_size)
{
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int size)
{
    if (size < 2)
    {
        return;
    }

    int mid = size / 2;
    int left[mid], right[size - mid];

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

#pragma omp parallel sections
    {
#pragma omp section
        {
            merge_sort(left, mid);
        }
#pragma omp section
        {
            merge_sort(right, size - mid);
        }
    }

    merge(arr, left, mid, right, size - mid);
}

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        cout << "Specify array length.\n";
        return 1;
    }

    int *a, n;
    n = stoi(argv[1]);
    int arr[n];
    int num_threads_array[] = {16};
    int num_threads_array_size = sizeof(num_threads_array) / sizeof(int);

    // Initialize the array with random values
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % n;
    }

    // Sort the array using normal merge sort
    clock_t start_time = clock();
    merge_sort(arr, n);
    clock_t end_time = clock();
    double normal_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Sort the array in parallel using OpenMP
    for (int i = 0; i < num_threads_array_size; i++)
    {
        int num_threads = num_threads_array[i];
        printf("Number of threads: %d\n", num_threads);
        start_time = clock();
        omp_set_num_threads(num_threads);

#pragma omp parallel
        {
#pragma omp single
            {
                merge_sort(arr, n);
            }
        }

        end_time = clock();
        double parallel_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        // Print the time taken by both merge sorts
        printf("Time taken (normal merge sort): %f ms\n", normal_time * 1000);
        printf("Time taken (parallel merge sort): %f ms\n", parallel_time * 1000);

        float speedUp = normal_time / parallel_time;
        float efficiency = speedUp / num_threads;
        cout << "Speed Up: " << speedUp << "\n";
        cout << "Efficiency: " << efficiency << "\n";
        printf("\n");
    }

    return 0;
}
