#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

int busy_work(void *t) {
  long tid = (long)t;
  double result = 0.0;
  printf("Thread %ld starting\n", tid);

  for (int i = 0; i < 10000000; i++) {
    result = result + sin(i) * tan(i);
  }

  printf("Thread %ld done. Result = %e\n", tid, result);
  thrd_exit((int)tid+3);
}

int main(int argc, char *argv[]) {
  thrd_t thread_id;
  int rc;
  long t = 1;
  int status;

  printf("Main: creating thread %ld\n", t);
  rc = thrd_create(&thread_id, busy_work, (void *)t);
  if (rc != thrd_success) {
    printf("ERROR in thrd_create():\n");
    exit(-1);
  }

  rc = thrd_join(thread_id, &status); // status is the int value that busy_work returns. So &status is a pointer to it. 
  // This function call tells the program to wait until the thread identified by thread_id terminates.
  // It ensures that main does not proceed beyond thrd_join until the thread finishes executing busy_work and exits via thrd_exit
  if (rc != thrd_success) {
    printf("ERROR in thrd_join():\n");
    exit(-1);
  }
  printf("Main: completed join with thread %ld having a status of %d\n", t,
         status);

  printf("Main: program completed. Exiting.\n");
  //thrd_exit(0);
  return EXIT_SUCCESS; // this is the same as using thrd_exit(0) since we used join. If we delete join and use return, the thread executing busy_work won't terminate.
}
