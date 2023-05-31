#include <iostream>
#include <stdlib.h>
#include <array>
#include <functional>
#include <string>
#include<omp.h>
using namespace std;

//For the purpose of open mp
#include<omp.h>

//to calculate CPU execution time
#include <chrono>

void s_bubble(int *, int);
void p_bubble(int *, int);

//Sequential Bubble Sort
void s_bubble(int *a, int n) {
	for (int i = 0; i < n; i++) 
	{
		int first = i % 2;
		for (int j = first; j < n - 1; j += 2) 
		{
			if (a[j] > a[j + 1]) 
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

void p_bubble(int *a, int n) {
	for (int i = 0; i < n; i++) {
		int first = i % 2;
		//starting the parallel thread for loop
		//num of thread are 2 due to no of cpu core
		#pragma omp parallel for shared(a, first) num_threads(2)
		for (int j = first; j < n - 1; j += 2) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}
}

int main() {
	
	int *a, n;
	cout << "Specify array length.\n";
	cin >> n;
	a = new int[n];
	
	//creating array of random number for testing purpose
	for (int i = 0; i < n; i++) {
		a[i] = rand() % n;
	}
	
	cout << "Generated random array of length " << n << "\n\n";
	
	double startTime = omp_get_wtime();
	s_bubble(a,n);
	double endTime = omp_get_wtime();
	
	cout << "Sequential Bubble sort: " << endTime - startTime << "s\n";
	
	startTime = omp_get_wtime();
	omp_set_num_threads(2);
	p_bubble(a,n);
	endTime = omp_get_wtime();
	cout << "Parallel (2) Bubble sort: "<< endTime - startTime << "s\n";

	return 0;
}