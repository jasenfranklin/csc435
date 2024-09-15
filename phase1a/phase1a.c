#include "phase1.h"
#include <stdio.h>
#include <usloss.h>
#include <stdlib.h>
#include <string.h>
typedef struct pcbStruct{
int pid;
int prio;
char name[MAXNAME];
void *stack;
int parent_pid;
int children[MAXPROC];
int siblings[MAXPROC];
struct procStruct *next;
}pcbStruct;

pcbStruct pcbTable[MAXPROC];

pcbStruct *runQueue[7];

void phase1_init(void){
    //inputs init into pcbtable
    pcbTable[0].pid=1;
    pcbTable[0].prio = 6;
    char *intName = "init";
    pcbTable[0].name[0]=intName;
    for(int i =0;i<7;i++){
        runQueue[i]=NULL;
    }
    runQueue[7]= &pcbTable[0];
}
void addToQueue(pcbStruct *process){
    int priority = process->prio;
   if(runQueue[priority]==NULL){
        runQueue[priority] = process;
        process->next = NULL;
   }else{
    pcbStruct *current = runQueue[priority];
    while(current->next !=NULL){
        current = current ->next;
    }
    current->next = process;
    process ->next = NULL;
   }

}

pcbStruct *removeFromQueue(int priority){
    pcbStruct *process = runQueue[priority];
    runQueue[priority] = process->next;
    process->next = NULL;
    return process;
}

int spork(char *name, int (*startFunc)(char*), char *arg, 
int stackSize, int priority){
    
}

int join(int *status){

}

void quit(int status){

}

void zap(int pid){

}

int getpid(void){

}

void dumpProccesses(void){

}

void blockMe(){

}

int unblockProc(int pid){

}

void errorPrint(char *code){
printf(code);
}