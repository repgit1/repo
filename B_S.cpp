// 

#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<functional>
#include<chrono>
#include<array>

using namespace std;

void s_bubble(int*,int);
void p_bubble(int*,int);

void s_bubble(int*a,int n){
    for (int i=0, i<n, i++){
        int first= i%2;
        for(int j=first, j<n-i, j+=2){
            if (a[j]<a[j-1]){
                swap (a[j],a[j-1]);
            }
        }
    }
}

void p_bubble(int*a,int n) {
    for(int i=o, i<n, i++){
        int first= i%2;
        for(int j=first, j<n-1, j+=2){
            if(a[j<a[j-1]]){
                swap (a[j],a[j-1]);
            }
        }
    }
}

int main(){
    int*a,n;
    cout<<"specify array lkength .\n";
    cin>>n;
    a= new int[n];

    for (int i=0, i<n, i++){
        a[i]=rand()%n;
    }
    cout<<"generatee random array"<<n<<"\n\n";

    double startTime = omp_get_wtime();
    s_bubble (a,n);
    double endTime = omp_get_wtime();
    cout<<"s_b_s"<<endTime - startTime<<"s\n";


    startTime = omp_get_wtime();
    omp_set_num_threads(2);
    p_bubble(a,n);
    endTime = omp_get_Wtime();
    cout<<"p_b_s"<<endTime - startTime<<"s\n";

    return 0;

}
