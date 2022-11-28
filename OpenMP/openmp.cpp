#include<bits/stdc++.h>
#include<omp.h>

#define no_of_threads 4
#define max_size 200000  
#define radius 1  
using namespace std;
    
float a[max_size];
int part = 0;
int noOfDarts;  
float pi_array[no_of_threads];

int main(){
	srand(time(0));
	noOfDarts = 50000;

	#pragma omp parallel num_threads(no_of_threads)
	{
		int threadId=omp_get_thread_num();
		int count = 0;
    		for (int i = threadId * (noOfDarts); i < (threadId + 1) * (noOfDarts); i++){
    			float dart_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    			float dart_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    			if(dart_x*dart_x + dart_y*dart_y <= radius*radius){
    				count++;
    			}	
    		}
    		float val_pi = (float(count)/float(noOfDarts))*float(4.00);
    		pi_array[threadId] = val_pi;
	}
	
	float total_sum = 0;
    	for (int i = 0; i < no_of_threads; i++)
        	total_sum += pi_array[i];
        	
    	total_sum = total_sum/float(no_of_threads);
    
    	cout<<"The value of pi for number of darts = "<<noOfDarts<<" is equal to = "<<total_sum<<"\n";
	
	return 0;
}

// Author -> Rahul Roy

// It is observed that the accuracy or precision of finding the value of pi increases with increase in the value of n (number of darts thrown)
