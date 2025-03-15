#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<vector>
#include<fcntl.h>
#include<glob.h>
#include "kernel_utils.h"
using namespace std;

void change_directory(vector<string> args){
    if(args.size()<2){cout<<"Missing Argument"<<endl;}
    else if(chdir(args[1].c_str()) !=0){
        cout<<"Failed Directory Change"<<endl;
    }
}

void handleWildCards(string& path, vector<string> &args){
    bool status = true;
    for(auto x:path) if(x=='*' || x=='?') status = false;
    if(status){
        args.push_back(path);
        return;
    }

    cout<<"Handling path"<<endl;
    
    glob_t glob_result;
    glob(path.c_str(),GLOB_NOCHECK,NULL,&glob_result);
    for(size_t i=0;i<glob_result.gl_pathc;i++){
        args.push_back(glob_result.gl_pathv[i]);
    }
    globfree(&glob_result);
}

