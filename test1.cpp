#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<vector>
#include<fcntl.h>
#include<chrono>
#include<thread>
#include<mutex>
using namespace std;

int var;
mutex m;

int main(){
    cout<<"Hi from test.cpp side"<<endl;
    cout<<"Waiting "<<endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout<<"Wait completed"<<endl;
}