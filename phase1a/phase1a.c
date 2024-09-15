#include <phase1.h>
#include <stdio.h>
//#include <usloss.h>
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

int pidCount;
pcbStruct pcbTable[MAXPROC];
//I put 7 elements so that theres no translating thats needed, just 1 for 1
//in the priority system
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
    testcase_main()
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

int pidCounter(int prevPid){
    return prevPid++;
}

int spork(char *name, int (*startFunc)(char*), char *arg, 
int stackSize, int priority){
    pcbStruct spork;
    spork.name= *name;
    spork.pid = pidCounter(pidCount);
    spork.prio=priority;
    if(stackSize<USLOSS_MIN_STACK){
        return -2;
    }
    if(priority<1 or priority>5){
        return -1;
    }
    pcbTable[priority] = addToQueue(spork);
    return spork.pid;
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

void main(){
    phase1_init();
}