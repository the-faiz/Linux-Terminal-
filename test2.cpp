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
    cout<<"This is a short command with no wait"<<endl;
    cout<<"Completed the short command"<<endl;
}