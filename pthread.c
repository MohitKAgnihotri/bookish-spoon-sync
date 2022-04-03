
#include <stdio.h>
#include <stdint.h>

#define Max 10
#define Limit 1000000

int counter = 0;

// function that each thread will execute
void *increment (void *arg)
{ int j, id = (intptr_t) arg;

  printf ("Thread %d  started!\n", id);
  for (j=0; j<Limit; j++) { counter++; }
  printf ("Thread %d  is ending!\n", id);
}

void main()
{ int i, numT;

  printf ("Enter number of threads to create: (<= 10)");
  scanf ("%d", &numT);

  // Create numT of identical threads 
  for ( i = 0; i < numT; i++ ){
    pthread_t* treadID[numT];
     int*temp = i;
      pthred_create(&threadID[i],NULL,&increment,temp);
  }
   int count;
   for(count =0; count < numT;count++) {
     pthread_join(treadID[count],NULL);
   }

   printf ("\nFinal value of counter: %d (should be %d)\n",
          counter, numT * Limit);
}
