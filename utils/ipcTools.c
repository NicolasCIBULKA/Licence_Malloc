#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ipcTools.h"
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
// STRUCTURES
#define SIZE 1024

static struct{
    long type;
    char msg[SIZE];
}buffer;


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

void* shmalloc(key_t key, int size){
    int shmid = shmget(key, 0,644);
    void* mem;
    int owner = 0;
    if(shmid == -1){
        owner = 1;
        shmid = shmget(key, size, IPC_CREAT|IPC_EXCL|0644);
    }
    if(shmid == -1){
        return 0;
    }
    mem = shmat(shmid, 0,0);
    if(mem == (void*) -1 && owner == 1){
        shmctl(shmid, IPC_RMID,0);
        return 0;
    }
    return mem;
}

int shmfree(key_t key){
    int shmid = shmget(key, 0, 644);
    shmctl(shmid, IPC_RMID, 0);
}

int msgalloc(key_t key){
    int msgid = msgget(key, 0644);
    if(msgid == -1){
        msgid = msgget(key, IPC_CREAT|IPC_EXCL|0644);
    }
    return msgid;
}

int msgfree(int msgqid){
    return msgctl(msgqid, IPC_RMID,0);
}

int msgsend(int msqid, char* msg, int msgSize){
    if(msgSize > SIZE){
        perror("message trop long");
        return -1;
    }

    buffer.type = 1;
    strncpy(buffer.msg, msg, msgSize);
    return msgsnd(msqid, &buffer, msgSize, 0);
}

int msgrecv(int msqid, char* msg, int msgSize){
    if(msgSize > SIZE){
        perror("message trop long");
        return -1;
    }
    int rcv = msgrcv(msqid, &buffer, msgSize, 1, 0);
    if(rcv != -1){
        strncpy(msg, buffer.msg, msgSize);
    }
    return rcv;

}