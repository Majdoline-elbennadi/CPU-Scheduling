/* This is code developed by <Majdoline EL BENNADI 22310812> */
#include "cmpe351.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
struct process{
int BurstTime;
int Priority;
int Arrival_Time;
int QueueID;
int WaitingTime;
 process* next;
};
struct Queue{
int QueueID;
process* processList;
Queue* next;
};

struct process* createprocess(int burstTime, int priority, int arrivalTime, int queueID);
struct Queue* createQueue(int QueueID, process* process);
struct Queue* InsertBackQueue(struct Queue* headerQueue, int QueueID, process* process);
struct process* InsertBackProcess(struct process* headerProcess, int burstTime, int priority, int arrivalTime, int queueID);
struct Queue* findQueue(struct Queue* headerQueue, int queueID);
void FCFS(struct Queue* headerQueue, int targetQueueID, ofstream& outputfile);
void SJF(struct Queue* headerQueue, int targetQueueID, ofstream& outputfile);
void Priority(struct Queue* headerQueue, int targetQueueID, ofstream& outputfile);

int
main(int argc, char *argv[])
{
struct Queue *headerQueue =NULL;
if (argc<3){
cout<< "no input or output file is founded , please check again "<<endl;
return 1;
}
ifstream inputfile(argv[1]);
ofstream outputfile(argv[2]);

cout<<"file is opened :"<<argv[1];
string line;
string part;
int lineCount=0;
while(getline(inputfile,line))
{
    lineCount++;
int index=0;
int burstTime=0,priority=0,arrivalTime=0,queueID=0;

stringstream ss(line);
while(getline(ss,part,':')){
string cleanPart = "";
            for (size_t i = 0; i < part.size(); i++) {
                if (part[i] != '\r' && part[i] != '\n') {
                    cleanPart += part[i];
                }}
if(index==0)
burstTime=stoi(cleanPart);
else if(index==1)
priority=stoi(cleanPart);
else if(index ==2)
arrivalTime=stoi(cleanPart);
else if (index==3)
queueID=stoi(cleanPart);
else
cout<<"error"<<endl;
index++;
}

struct process * headerprocess= NULL;
headerprocess =createprocess(burstTime,priority,arrivalTime,queueID);
Queue* foundQueue = findQueue(headerQueue, queueID);
if (foundQueue==NULL){
headerQueue=InsertBackQueue(headerQueue,queueID,headerprocess);
}
else foundQueue->processList =InsertBackProcess(foundQueue->processList, burstTime, priority, arrivalTime, queueID);

}

FCFS(headerQueue, 0, outputfile);
SJF(headerQueue, 0, outputfile);
Priority(headerQueue, 0, outputfile);
FCFS(headerQueue, 1, outputfile);
SJF(headerQueue, 1, outputfile);
Priority(headerQueue, 1, outputfile);



inputfile.close();
outputfile.close();

}

struct process  *createprocess(int burstTime ,int priority ,int arrivalTime, int queueID){
process* temp = new process();
temp->BurstTime=burstTime;
temp->Priority=priority;
temp->Arrival_Time=arrivalTime;
temp->QueueID=queueID;
temp->next=NULL;
return temp;}

struct Queue  *createQueue(int QueueID ,process* process){
struct Queue * temp=new Queue();
temp->QueueID=QueueID;
temp->processList=process;
temp->next=NULL;
return temp;
}
struct Queue * InsertBackQueue (struct Queue * headerQueue, int QueueID, process *process){
    struct Queue * temp=createQueue(QueueID,process);
    struct Queue * headertemp;
    if(headerQueue==NULL)
    {
        headerQueue=temp;
        return headerQueue;
    }
    headertemp=headerQueue;
    while(headertemp->next != NULL)
    headertemp=headertemp->next;
    headertemp->next=temp;
    return headerQueue;
}
struct process * InsertBackProcess(struct process *headerProcess,int burstTime ,int priority,int arrivalTime, int queueID){
    struct process * temp= createprocess(burstTime, priority, arrivalTime, queueID);
    if(headerProcess==NULL)
      {
        headerProcess=temp;
        return headerProcess;
    }
   struct process* headertemp=headerProcess;
    while(headertemp->next != NULL)
    headertemp=headertemp->next;
    headertemp->next=temp;
    return headerProcess;
}
struct Queue* findQueue(struct Queue* headerQueue, int queueID)
{
    while (headerQueue != NULL) {
        if (headerQueue->QueueID == queueID)
            return headerQueue;
        headerQueue = headerQueue->next;
    }
    return NULL;}

void FCFS(struct Queue* headerQueue, int targetQueueID, ofstream& outputfile ){
    Queue* currentQueue = headerQueue;
while(currentQueue != NULL && currentQueue->QueueID != targetQueueID){
    currentQueue = currentQueue->next;
}
if(currentQueue == NULL) return;

      int WT=0 ,count=0 , sumWT=0,currentTime=0;
    float AWT=0.00;
    process* currentProcess = currentQueue->processList;

    outputfile << currentQueue->QueueID << ":1:0:";
    cout<< currentQueue->QueueID << ":1:0:";
while (currentProcess != NULL ) {
    if(currentTime < currentProcess->Arrival_Time)
    currentTime = currentProcess->Arrival_Time;
    currentProcess->WaitingTime = currentTime - currentProcess->Arrival_Time;
    outputfile << currentProcess->WaitingTime << ":";
    cout<< currentProcess->WaitingTime << ":";
    sumWT += currentProcess->WaitingTime;
    currentTime += currentProcess->BurstTime;
    currentProcess = currentProcess->next;
    count++;
}

if(count>0){
AWT=(float)sumWT/count;
  outputfile << fixed << setprecision(2) << AWT << endl;
  cout<<fixed<<setprecision(2)<<AWT<<endl;}
    
}



void SJF(struct Queue* headerQueue, int targetQueueID, ofstream& outputfile){
 Queue * currentQueue=headerQueue;
 while(currentQueue!=NULL && currentQueue->QueueID != targetQueueID){
    currentQueue = currentQueue->next;
 }
 if(currentQueue == NULL) return;

     int WT=0,count=0, sumWT=0 ,currentTime = 0;
     float  AWT=0.00;
     for(process* p=currentQueue->processList;p!=NULL;p=p->next){
p->WaitingTime=-1;      }
     outputfile << currentQueue->QueueID << ":2:0:";
     cout<<currentQueue->QueueID << ":2:0:";
         int flag=0;
        while(flag==0){

            process* temp =NULL;
           int min=10000;
          for(process* p = currentQueue->processList; p != NULL; p = p->next){
                if(p->WaitingTime == -1 && p->Arrival_Time <= currentTime){
                    if(p->BurstTime < min){
                        min = p->BurstTime;
                   temp = p;
                 }
                }}
          if (temp!=NULL){
              temp->WaitingTime= currentTime - temp->Arrival_Time;
              outputfile<<temp->WaitingTime<<":";
              cout<<temp->WaitingTime<<":";
              currentTime+=temp->BurstTime;
              sumWT+=temp->WaitingTime;
              count++;
          }
          else {
              int minArrival=10000;
              for(process* p = currentQueue->processList; p != NULL; p = p->next){
                   if(p->WaitingTime == -1 && p->Arrival_Time < minArrival)
                        minArrival = p->Arrival_Time;
                }
                currentTime = minArrival;

              }

              flag=1;
               for(process* p = currentQueue->processList; p != NULL; p = p->next){
                if(p->WaitingTime == -1){
                    flag= 0;
                    break;}
          }
            }
            if(count > 0){
        AWT = (float)sumWT / count;
        outputfile << fixed << setprecision(2) << AWT << endl;
        cout<<fixed << setprecision(2) << AWT << endl;}
        
        }

    void Priority(struct Queue* headerQueue, int targetQueueID, ofstream& outputfile) {

    Queue* currentQueue = headerQueue;
    while (currentQueue != NULL && currentQueue->QueueID != targetQueueID) {
        currentQueue = currentQueue->next;
    }
    if (currentQueue == NULL) return;

    int WT=0, count = 0, sumWT = 0, currentTime = 0;
    float AWT = 0.00;
    process* p = currentQueue->processList;
        while (p != NULL) {
            p->WaitingTime = -1;
            p = p->next;
        }
        outputfile << currentQueue->QueueID << ":3:0:";
        cout << currentQueue->QueueID << ":3:0:";
        int flag = 0;
        while (flag == 0) {
            process* temp = NULL;
            int minPriority = 100000;
            for (p = currentQueue->processList; p != NULL; p = p->next) {
                if (p->WaitingTime == -1 && p->Arrival_Time <= currentTime) {
                    if (p->Priority < minPriority) {
                        minPriority = p->Priority;
                        temp = p;
                    }
                }
            }

            if (temp != NULL) {
                temp->WaitingTime = currentTime - temp->Arrival_Time;
                outputfile << temp->WaitingTime << ":";
                cout << temp->WaitingTime << ":";
                currentTime += temp->BurstTime;
                sumWT += temp->WaitingTime;
                count++;
            } else {
                int minArrival = 100000;
                process* t = currentQueue->processList;
                while (t != NULL) {
                    if (t->WaitingTime == -1 && t->Arrival_Time < minArrival)
                        minArrival = t->Arrival_Time;
                    t = t->next;
                }
                currentTime = minArrival;
            }
            flag = 1;
            for (p = currentQueue->processList; p != NULL; p = p->next) {
                if (p->WaitingTime == -1) {
                    flag = 0;
                    break;
                }}
        }
        if (count > 0) {
            AWT = (float)sumWT / count;
            outputfile << fixed << setprecision(2) << AWT << endl;
            cout << fixed << setprecision(2) << AWT << endl;
        }
        
    }

