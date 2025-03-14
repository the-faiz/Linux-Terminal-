#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<vector>
#include<chrono>
#include<thread>
using namespace std;

void get_args(string &command, vector<string>& args){
    string temp = "";
    for(int i=0;i<command.size();i++){
        if(command[i]==' '){
            while(i+1<command.size() && command[i+1]==' ') i++;
            if(temp!="")
                args.push_back(temp);
            temp = "";
            continue;
        }
        else if(command[i]=='>' || command[i]=='<' || command[i] == '|'){
            if(temp!="")
                args.push_back(temp);
            args.push_back(string(1,command[i]));
            temp = "";
            continue;
        }
        temp+=command[i];
    }
    if(temp!="") args.push_back(temp);
    //for(auto x:args) cout<<x<<endl; --> checking all the arguments detected
}

void execute(vector<string>&args){
    vector<char*> c_args;
    for(auto& arg:args){
        c_args.push_back(&arg[0]);
    }
    c_args.push_back(NULL);

    pid_t pid = fork();
    if(pid<0){cerr<<"Fork failed"<<endl;return;}
    if(pid==0){
        execvp(c_args[0],c_args.data());
        cerr<<"execution failed"<<endl;
    }else{
        wait(NULL);
        cout<<"Child proces executed successfully"<<endl;
    }
}

void process(string &command){
    vector<string> args;
    get_args(command,args);

}

int main(){
    string msg;
    msg = "This is a message";
    // this_thread::sleep_for(chrono::seconds(4));
    cout<<"this is the message: "<<msg<<endl;
    // this_thread::sleep_for(chrono::seconds(20));
    // string command = "ls -l";
    // vector<string> args;
    // get_args(command,args);
    // execute(args);
    return 0;
}