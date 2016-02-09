/*
SHELL PARALELA - EXERCICIO 2
Header File

Grupo 002
    80774	Nuno Henrique Sales Fernandes
    78974	Eduardo Jorge Beirão Janicas
    82448	Diana Neves Antunes

 Sistemas Operativos, DEI/IST/ULisboa 2015-16
*/
#ifndef PARSHELL_H
#define PARSHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "list.h"
#include "commandlinereader.h"
#include "par-shellCommands.h"


#define MAX_INPUT 5
#define TRUE 1
#define FALSE 0

pthread_t tid;
pthread_mutex_t statusMutex;
pthread_mutex_t childMutex;
pthread_mutex_t listMutex;
int exitStatus;
int numChildren;

/*
Par-Shell is a program that alows a user to execute several programs
on the machine file system in parallel.
*/
int main (int argc, char **argv);

#endif
