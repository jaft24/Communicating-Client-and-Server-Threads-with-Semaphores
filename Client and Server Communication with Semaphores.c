/* Author: Jaleta Tesgera 
   CSC 474: Operating Systems Concepts
   March 1*/

// Include the necessary libriaries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


// Declare both Semaphore and Thread values initially
sem_t thread_initialization, connection_confirm, acknowledgment_confirm, final_confirm;
pthread_t clientSideThread, serverSideThread;


// The Client Function with Printable statements as per the instruction
void* client(void*) {


   // Action Connecting to Server
   printf("Client: Connecting to a server\n");
   sleep(1);
   sem_post(&connection_confirm); // Make the next connection accessibe in the Server Function


   sem_wait(&acknowledgment_confirm); // Wait for the acknowledgment to be available from the Server Function
   // Recieved an acknowledgment
   printf("Client: Receiving an acknowledgement\n");
   sleep(1);

   // Sent Final Confirmation (Execute this after Acknowledgment is done)
   printf("Client: Sending final confirmation\n");
   sleep(1);
   sem_post(&final_confirm); // Make the next final confirmation accessibe in the Server Function


   return NULL;
}

// The Server Function with Printable statements as per the instruction
void* server(void*) {


   sem_wait(&connection_confirm); // Wait for the connection to be available from the Client Function
   // Received a connection signal
   printf("Server: Receiving a connection signal.\n"); 
   sleep(1);


   // Sent an acknowledgment (Execute this after recieving connection is done)
   printf("Server: Sending an acknowledgement\n");
   sleep(1);
   sem_post(&acknowledgment_confirm); // Make the next ack accessibe in the Client Function


   sem_wait(&final_confirm); // Wait for the final confirmtion to be available from the Client Function
   // Received Final Confirmation
   printf("Server: Receiving final confirmation\n");
   sleep(1);
  
   return NULL;
}


int main(int argc, char* aegv[]) {


   // Initialize Semaphore values
   sem_init(&connection_confirm, 0, 0);
   sem_init(&acknowledgment_confirm, 0, 0);
   sem_init(&final_confirm, 0, 0);


   // Create and join the threads in the correct order
   pthread_create(&serverSideThread, NULL, &server, NULL);
   pthread_create(&clientSideThread, NULL, &client, NULL);
   pthread_join(clientSideThread, NULL);
   pthread_join(serverSideThread, NULL);


   // Destroy the semaphores
   sem_destroy(&connection_confirm);
   sem_destroy(&acknowledgment_confirm);
   sem_destroy(&final_confirm);


   return 0;
}





