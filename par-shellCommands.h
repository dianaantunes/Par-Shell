/*
SHELL PARALELA - EXERCICIO 2
(par-shellCommands Header File)

Grupo 002
    80774	Nuno Henrique Sales Fernandes
    78974	Eduardo Jorge Beirão Janicas
    82448	Diana Neves Antunes

 Sistemas Operativos, DEI/IST/ULisboa 2015-16
*/

#ifndef PARSHELLCOMMANDS_H
#define PARSHELLCOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "list.h"
#include "par-shell.h"

#define VALUE 2
#define TRUE 1
#define FALSE 0

/*
newProcess:
  Crates a child process that executes an externel program on background,
  meaning that the par-shell doesn't wait for it to end,
  and is ready to create new child processes.

Arguments:
 'argVector' should be a vector of char* previously allocated with
 as many entries as 'vectorSize'. The vector is of type [pathname [arg1 arg2 ...]],
 referring the path and the arguments of the new program to run.
*/
void newProcess(char **argVector, list_t* list);

/*
monitor:
  Checks for terminated processes and updates their status and endTime on the processList

Arguments:
 '*list' should be a list containing all child processes
 created on the par-shell.
*/
void *monitor(void *list);

#endif
