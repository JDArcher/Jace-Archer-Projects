#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include "341_Monitor.h"

#define N 5
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock
using namespace std;

const char *name[N] = {"Aristotle", "Kant", "Spinoza", "Marx", "Russell" };
pthread_mutex_t forks2[N];


void eat(int id)
{

    get_forks(id);

    string pname(name[id]);
    int lfork = id;
    int rfork = (id + 1)%N;

    ostringstream lfid, rfid;

    lfid << lfork;
    rfid << rfork;

    string s = "Philosopher " + pname + " beginning to eat.";
    print(s.c_str());
    sleep(rand()%4+2);

    release_forks(id);

}//The eat method tries to grab the forks through the monitor, wait, and then release the forks through the monitor


void think(int id)
{

    string pname(name[id]);
    string s = "Philosopher " + pname + " is thinking.";
    print(s.c_str());
    sleep(rand()%5 + 5);
    s = "Philosopher " + pname + " is hungry, ready to eat.";
    eat(id);

}//The think method will print out the philosophers who are currently thinking, wait for a second, and then try to eat

void* Philosophize(void *id)
{

    int threadid = (int)id;

    cout << threadid << ": " << name[threadid] << endl;

    while(true){

        think(threadid);

    }//This loop will run infinitely, placing philosophers back in to the thinking state

    pthread_exit(NULL);

}//end Philosophize


int main(int argc, char **argv){

    int id[N];
    pthread_t tid[N];
    srand(time(NULL));

    for(int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_mutex_init(&forks2[i], NULL);
    }

    for(int i = 0; i < N; i++) {

        pthread_create(&tid[i], NULL, Philosophize, (void*)i);

    }

    for(int i = 0; i < N; i++) {

        pthread_join(tid[i], NULL);

    }

    pthread_exit(NULL);

    return 0;

}//end main

