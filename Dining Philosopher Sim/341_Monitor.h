//
// Created by Jace on 4/7/2017.
//

#ifndef PROGRAM_4_341_MONITOR_H
#define PROGRAM_4_341_MONITOR_H

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <sstream>

using namespace std;

pthread_mutex_t hold [5];
//Used to lock forks when they are being held

bool forks[5] = {true};
//Used to signal if a fork is being held or not.

const char *names[5] = {"Aristotle", "Kant", "Spinoza", "Marx", "Russell" };
//Used to hold all of the Philosophers names

void print(const char *str)
{

    pthread_mutex_t screen = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&screen);
    cout << str << endl;
    pthread_mutex_unlock(&screen);

}//This will print out the message passed to it

void get_forks(int pid){

    string pname = (names[pid]);

    int left = pid;
    int right = (pid + 1) % 5;
    //Left and Right are the IDs for the adjacent forks of a philosopher

    ostringstream lfid, rfid;

    lfid << left;
    rfid << right;

    if(!forks[left]){

        pthread_mutex_lock(&hold[left]);

    }//end if
    //If a fork is being held, the lock is called to block access to it

    forks[left] = false;
    //Signals the left fork is being held

    string s = "Philosopher " + pname + " acquired fork " + lfid.str() + ".";
    print(s.c_str());

    if(!forks[right]){

        pthread_mutex_lock(&hold[right]);

    }//end if
    //If a fork is being held, the lock is called to block access to it


    forks[right] = false;
    //Signals the left fork is being held

    s = "Philosopher " + pname + " acquired fork " + rfid.str() + ".";
    print(s.c_str());

}//end get_forks


void release_forks(int pid){

    string pname = (names[pid]);

    int left = pid;
    int right = (++pid) % 5;

    ostringstream lfid, rfid;

    lfid << left;
    rfid << right;


    forks[left] = true;
    //Signals that the left fork is no longer being used

    pthread_mutex_unlock(&hold[left]);
    //Unlocks processes waiting on this left fork

    forks[right] = true;
    //Signals that the right fork is no longer being used


    pthread_mutex_unlock(&hold[right]);
    //Unlocks processes waiting on this right fork


    string s = "Philosopher " + pname + " releasing forks " + lfid.str() + " and " + rfid.str() + ".";
    print(s.c_str());

}//end release_forks



#endif //PROGRAM_4_341_MONITOR_H
