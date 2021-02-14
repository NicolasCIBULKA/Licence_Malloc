#include <stdio.h>
#include <stdlib.h>
#include "ipcTools.h"
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

// STRUCTURES

// CODE FONCTIONS

int semalloc(key_t key, int valInit){
    int semid = semget(key, 1, 0);
    if(semid == -1){
        semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0600);
        if(semid == -1)return -1;
        int init = semctl(semid, 0, SETVAL, valInit);
        if(init == -1){
            semctl(semid, 0, IPC_RMID, 0);
            return -1;
        }
    }
    return semid;
}

// decrementation
void P(int semid){
    struct sembuf sP = {0,-1,0};
    semop(semid, &sP, 1);
}

// incrementation
void V(int semid){
    struct sembuf sP = {0,1,0};
    semop(semid, &sP, 1);
}

int semfree(int semid){
    return semctl(semid, 0, IPC_RMID, 0);
}

int mutalloc(key_t key){
    return semalloc(key, 1);
}

int mutfree(int semid){
    return semctl(semid, 0, IPC_RMID, 0);
}