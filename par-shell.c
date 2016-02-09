/*
SHELL PARALELA - EXERCICIO 2

Grupo 002
    80774	Nuno Henrique Sales Fernandes
    78974	Eduardo Jorge Beirão Janicas
    82448	Diana Neves Antunes

 Sistemas Operativos, DEI/IST/ULisboa 2015-16
*/

#include "par-shell.h"

/*
Par-Shell is a program that alows a user to execute several programs
on the machine file system in parallel.
*/
int main (int argc, char **argv) {

  /* One mutex is initialized for each shared variable
  The variables are initialized inside a critical section */
  pthread_mutex_init(&childMutex, NULL);
  pthread_mutex_lock(&childMutex);
  numChildren = 0;
  pthread_mutex_unlock(&childMutex);
  /* numChildren is the active number of child processes running */

  pthread_mutex_init(&statusMutex, NULL);
  pthread_mutex_lock(&statusMutex);
  exitStatus = FALSE;
  pthread_mutex_unlock(&statusMutex);
  /* exitStatus informs other threads if the user ordered the program to exit */

  pthread_mutex_init(&listMutex, NULL);
  pthread_mutex_lock(&listMutex);
  list_t* list;
  list = lst_new();
  pthread_mutex_unlock(&listMutex);
  /* processList retains info from all the processes executed or in execution */

  char **argVector = (char**)malloc(MAX_INPUT * sizeof(char*));

  if (!argVector) {
    /* Error */
    perror("Malloc doesn't work\n");
  }

  if (pthread_create(&tid, 0, monitor, (void*)list) != 0) {
    /* Error */
    perror("Failed to create thread\n");
  }

  while(TRUE) {

      readLineArguments(argVector, MAX_INPUT);
      /* Returns an int that is not used afterwards, therefore it's not saved */

      if (*argVector == NULL) {
        /* If the user does not provide any input */
        printf("No arguments\n");
      }

      else if (!strcmp(argVector[0], "exit")) {
        /* Exits the program */
        pthread_mutex_lock(&statusMutex);
        exitStatus = TRUE;
        pthread_mutex_unlock(&statusMutex);

        pthread_join(tid, NULL);
        /* Waits for the other thread to end */
        break;
      }

      else {
        /* Creates a new process */
        pthread_mutex_lock(&listMutex);
        newProcess(argVector, list);
        pthread_mutex_unlock(&listMutex);
      }
  }

  /* Prepare to end program */
  lst_print(list);
  lst_destroy(list);
  free(argVector);
  return EXIT_SUCCESS;
}
