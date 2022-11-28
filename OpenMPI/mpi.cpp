#include<bits/stdc++.h>
#include <mpi.h>
  
#define no_of_threads 4
#define max_size 200000  
#define radius 1  
using namespace std;
    
float a[max_size];
int part = 0;
int noOfDarts;  
  
int main(int argc, char* argv[])
{
    srand(time(0));
    int pid, np, elements_per_process, n_elements_recieved;
    noOfDarts = 50000;
    // np -> no. of processes
    // pid -> process id
  
    MPI_Status status;
  
    // Creation of parallel processes
    MPI_Init(&argc, &argv);
  
    // find out process ID,
    // and how many processes were started
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
  
    // master process
    if (pid == 0) {
        int index, i;
        elements_per_process = noOfDarts;
  
        // check if more than 1 processes are run
        if (np > 1) {
            // distributes the portion of array to child processes to calculate their respective values of pi
            for (i = 1; i < np; i++) {
                index = i * elements_per_process;
                MPI_Send(&elements_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
  
        // master process add its own sub array
        int count = 0;
        for (int i = 0; i < (noOfDarts); i++){
    		float dart_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    		float dart_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    		if(dart_x*dart_x + dart_y*dart_y <= radius*radius){
    			count++;
    		}	
    	}
    	float val_pi = (float(count)/float(noOfDarts))*float(4.00);
  
        // collects value of pi from other processes
        float tmp;
        float total_sum = val_pi;
        for (i = 1; i < np; i++) {
            MPI_Recv(&tmp, 1, MPI_FLOAT,MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            int sender = status.MPI_SOURCE;
            total_sum += tmp;
        }
  	
  	total_sum = total_sum/float(np);
       
       cout<<"The value of pi for number of darts = "<<noOfDarts<<" is equal to = "<<total_sum<<"\n";
    }
    
    // slave processes
    else {
        MPI_Recv(&n_elements_recieved,1, MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
  
        // calculates its respective pi value
        int count = 0;
    	for (int i = pid * (n_elements_recieved); i < (pid + 1) * (n_elements_recieved); i++){
    		float dart_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    		float dart_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    		if(dart_x*dart_x + dart_y*dart_y <= radius*radius){
    			count++;
    		}	
    	}
    	float val_pi = (float(count)/float(noOfDarts))*float(4.00);
  
        // sends the calculated pi value to the root process
        MPI_Send(&val_pi, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    }
  
    // cleans up all MPI state before exit of process
    MPI_Finalize();
  
    return 0;
}

// Author -> Rahul Roy

// It is observed that the accuracy or precision of finding the value of pi increases with increase in the value of n (number of darts thrown)
