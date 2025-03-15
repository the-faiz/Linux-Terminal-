#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include<vector>
#include "history.h"
using namespace std;

int current_index=0;
deque<string> his; //For storing the history
#define MAXLEN 100 //Maximum length of deque

void save_to_history(string& command){
    his.push_front(command);
    if(his.size()>MAXLEN) his.pop_back();
}

//Function to get input character without pressing enter
int getch(){
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void get_history(string &command){
    int ch = getch();
    if(ch=='['){
        ch = getch();
        if(ch=='A'){//Up Arrow
            if(current_index<his.size()-1){
                current_index++;
                cout<<"\33[2K\rAtif'sKernel:~$"<<his[current_index];cout.flush();
                command = his[current_index];
            }
        }
        else if(ch=='B'){ //Down Arrow
            if(current_index>0){
                current_index--;
                cout<<"\33[2K\rAtif'sKernel:~$"<<his[current_index];cout.flush();
                command = his[current_index];
            }
        }
    }
}