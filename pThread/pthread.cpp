#include<bits/stdc++.h>
#include <pthread.h>
  
#define no_of_threads 4
#define max_size 200000  
#define radius 1  
using namespace std;
    
float a[max_size];
int part = 0;
int noOfDarts;  
float pi_array[no_of_threads];
  
void* threadFunc(void* arg)
{
    int threadId = part++;
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
    return NULL;
}
  
// Driver Code
int main()
{
    srand(time(0));
    
    pthread_t threads[no_of_threads];
    noOfDarts = 50000;
    	
    // Creating threads
    for (int i = 0; i < no_of_threads; i++)
       pthread_create(&threads[i], NULL, threadFunc, (void*)NULL);
  
    // Joining threads
    for (int i = 0; i < no_of_threads; i++)
        pthread_join(threads[i], NULL);
  
    // adding sum of all 4 parts
    float total_sum = 0;
    for (int i = 0; i < no_of_threads; i++)
        total_sum += pi_array[i];
        	
    total_sum = total_sum/float(no_of_threads);
    
    cout<<"The value of pi for number of darts = "<<noOfDarts<<" is equal to = "<<total_sum<<"\n";
  
    return 0;
}

// Author -> Rahul Roy

// It is observed that the accuracy or precision of finding the value of pi increases with increase in the value of n (number of darts thrown)
