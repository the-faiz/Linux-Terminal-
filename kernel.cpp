#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<vector>
#include<fcntl.h>
#include "kernel_utils.h"
#include "history.h"
using namespace std;

pid_t current_forground_process=-1;

void signalHandler(int signum){
    if(signum==SIGINT){
        if(current_forground_process!=-1){
            kill(current_forground_process,SIGKILL);
            current_forground_process = -1;
            cout<<"Process Interrupted. Returning to the shell"<<endl;
        }
    }
    else if(signum == SIGTSTP && current_forground_process!=-1){
        kill(current_forground_process,SIGSTOP);
        setpgid(current_forground_process,current_forground_process); //detach the child process from the parent
        kill(current_forground_process,SIGCONT);
        current_forground_process = -1;
        cout<<"Process moved to background"<<endl;
    }
}

void get_args(string &command, vector<string>& args){
    string temp = "";
    for(int i=0;i<command.size();i++){
        if(command[i]==' '){
            while(i+1<command.size() && command[i+1]==' ') i++;
            if(temp!="")
                handleWildCards(temp,args);
            temp = "";
            continue;
        }
        else if(command[i]=='>' || command[i]=='<' || command[i] == '|'){
            if(temp!="")
                handleWildCards(temp,args);
            args.push_back(string(1,command[i]));
            temp = "";
            continue;
        }
        temp+=command[i];
    }
    if(temp!="") handleWildCards(temp,args);
    //for(auto x:args) cout<<x<<endl; --> checking all the arguments detected
}

void redirection(vector<string> &args,string& inputFilename, string& outputFilename){
    vector<string> temp;
    for(int i=0;i<args.size();i++){
        if(args[i]==">") {outputFilename = args[i+1]; i++;continue;}
        else if(args[i]=="<") {inputFilename = args[i+1];i++;continue;}
        temp.push_back(args[i]);
    }
    args.clear();
    for(auto x:temp) args.push_back(x);
}

void handleInputOutputRedirection(string& inputFilename, string& outputFilename,int inpipe, int outpipe){
    if(inputFilename!=""){
        int fd = open(inputFilename.c_str(),O_RDONLY);
        if(fd<0) {perror("can not open the file");return;}
        dup2(fd,STDIN_FILENO);
        close(fd);
    }
    if(outputFilename!=""){
        int fd = open(outputFilename.c_str(),O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd<0) {perror("can not open the output file");return;}
        dup2(fd,STDOUT_FILENO);
        close(fd);
    }
    if(inpipe!=-1)
        dup2(inpipe,STDIN_FILENO);
    if(outpipe!=-1)
        dup2(outpipe,STDOUT_FILENO);
}

void execute_external_command(vector<string>&args,int inpipe, int outpipe,bool background){

    string inputFilename="",outputFilename="";
    redirection(args,inputFilename,outputFilename);

    vector<char*> c_args;
    for(auto& arg:args){
        c_args.push_back(&arg[0]);
    }
    c_args.push_back(NULL);
    
    pid_t pid = fork();
    if(pid<0){cerr<<"Fork failed"<<endl;return;}
    if(pid==0){
        handleInputOutputRedirection(inputFilename,outputFilename,inpipe,outpipe);
        execvp(c_args[0],c_args.data());
        cerr<<"execution failed"<<endl;
    }else if(!background){
        current_forground_process = pid;
        waitpid(pid,NULL, WUNTRACED); 
        current_forground_process = -1;
        cout<<"Child proces executed successfully"<<endl;
    }
}

void execute_internal_command(){
}

void execute(vector<string>&args,int inpipe,int outpipe, bool background){
    if(args[0]=="cd"){
        change_directory(args);
    }else if(args[0]=="exit"){
        exit(0);
    }
    else{
        execute_external_command(args,inpipe,outpipe,background);
    }
}

void process(string &command){
    vector<string> args;
    get_args(command,args);
    
    bool background = false;
    if(args.back()=="&") {background=true;args.pop_back();}

    vector<string> subcommand;
    int pipefd[2];

    int inpipe = -1;
    for(int i=0;i<args.size();i++){
        if(args[i]=="|"){
            if(pipe(pipefd)==-1) {cerr<<"Pipe Creation Failed";return;}

            pid_t pid = fork();
            
            if(pid==0){
                execute(subcommand,inpipe,pipefd[1],background);
                close(pipefd[0]);
                close(pipefd[1]);
                exit(0);
            }else{
                wait(NULL);
                close(pipefd[1]);
                if(inpipe!=-1) close(inpipe);
                inpipe = pipefd[0];
            }
            subcommand.clear();
        }else{
            subcommand.push_back(args[i]);
        }
    }
    execute(subcommand,inpipe,-1,background);
    if(inpipe!=-1) close(inpipe);
}

int main(){
    signal(SIGINT,signalHandler);
    signal(SIGTSTP,signalHandler);
    while(1){
        cout<<"Atif'sKernel:~$";cout.flush();
        string command="";
        while(true){
            int ch = getch();
            if(ch=='\n') break;
            else if(ch==27) {get_history(command);}
            else if (ch == 127){ //backspace
                if(command.size()>0){
                    cout << "\b \b";
                    command.pop_back();
                }
            } 
            else{cout<<char(ch);command+=ch;}
        }
        process(command);
        save_to_history(command);
        cout<<"Main---------------->Executed successfully"<<endl;
    }
    return 0;
}