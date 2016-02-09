/*
SHELL PARALELA - EXERCICIO 2
(par-shellCommands Implementation File)

Grupo 002
    80774	Nuno Henrique Sales Fernandes
    78974	Eduardo Jorge Beirão Janicas
    82448	Diana Neves Antunes

 Sistemas Operativos, DEI/IST/ULisboa 2015-16
*/

#include "par-shellCommands.h"

/*
newProcess:
  Crates a child process that executes an external program on background,
  meaning that the par-shell doesn't wait for it to end,
  and is ready to create new child processes.

Arguments:
 'argVector' should be a vector of char* previously allocated with
 as many entries as 'vectorSize'. The vector is of type [pathname [arg1 arg2 ...]],
 referring the path and the arguments of the new program to run.
*/
void newProcess(char **argVector, list_t* list) {

  int pid;

  pid = fork();

  if (pid < 0) {
    /* Error */
    perror("Fork doesn't work\n");
  }

  else if (pid == 0) {
    /* Child process */
    execv(argVector[0], argVector);
    /* Error */
    perror("Execv doesn't work\n");
    exit(EXIT_FAILURE);
  }

  else {
    /* Parent process */
    pthread_mutex_lock(&childMutex);
    numChildren++;
    pthread_mutex_unlock(&childMutex);

    insert_new_process(list, pid, time(NULL));
  }
}

/*
monitor:
  Checks for terminated processes and updates their status and endTime on the processList

Arguments:
 '*list' should be a list containing all child processes
 created on the par-shell.
*/
void *monitor(void *list) {

  int status, pid;

  while(TRUE) {

    if (numChildren > 0) {
      /* When there are child processes running, this thread always waits for them
      to end and retains information about them. */
      pid = wait(&status);

      numChildren--;

      if (WIFEXITED(status)) {
        /* Saves the status of a process that was terminated normally */
        pthread_mutex_lock(&listMutex);
        update_terminated_process(list, pid, WEXITSTATUS(status), time(NULL));
        pthread_mutex_unlock(&listMutex);
      }
      else if (WIFSIGNALED(status)){
        /* Saves the status of a process that was terminated due to the receipt of a signal */
        pthread_mutex_lock(&listMutex);
        update_terminated_process(list, pid, WTERMSIG(status), time(NULL));
        pthread_mutex_unlock(&listMutex);
      }

      else if (pid < 0)
        /* Error */
        perror("Wait doesn't work\n");

    }

    pthread_mutex_lock(&childMutex);
    pthread_mutex_lock(&statusMutex);
    if (numChildren == 0 && exitStatus == TRUE) {
      /* Checks if there are no child processes running and if the user ordered the
      program to exit. If this happens, this thread is ready to end */
      pthread_mutex_unlock(&statusMutex);
      pthread_mutex_unlock(&childMutex);

      pthread_exit(NULL);
    }

    else {
      /* If there are no child processes running but the user did not ordered the
      program to exit, this thread sleeps for 1 second before checking for new
      processes */
      pthread_mutex_unlock(&statusMutex);
      pthread_mutex_unlock(&childMutex);
      sleep(1);
    }

  }
}
