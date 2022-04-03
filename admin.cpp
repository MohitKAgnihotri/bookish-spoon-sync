#include <iostream>
#include <unistd.h>
#include <wait.h>
#include <fstream>
#include <cstring>
using namespace std;

extern void calculate(char*,int,int);

struct Data{ //struct to pass data to the child process from pipe
    char command[100];
    int a;
    int b;
};

int main(int argc, char** argv){
    if(argc!=2){ //checking if arguments not passed or extra arguments passed
        cerr<<"Invalid arguments!"<<endl;
    }

    pid_t pid;
    int p[2];
	int p1[2];
    pipe(p); //for child process
	pipe(p1); //for parent process


    pid = fork();

    if(pid==0){ //This is the child process
        close(p[0]); //closing the ends of the pipes that are not to be used by child process
        close(p1[1]);
        Data d;
        int signal = 1; //Variable that will signal parent process to send next instruction

        while(true){
            read(p1[0],&d,sizeof(Data)); //reading the instruction

            if(!strcmp(d.command,"exit")){ //if instruction is to exit
                write(p[1],&signal,sizeof(int)); //signal the parent
                break; //breaks the loop and exits
            }

            calculate(d.command,d.a,d.b); //calling calculate function from cal-new.cpp
            write(p[1],&signal,sizeof(int)); //signaling the parent process for next instruction
        }

        close(p[1]); //closing the pipes
        close(p1[0]);
        return 0; //child process ends here
    }
   
    //parent process
    cout << "Process ID for parent Process " << getpid() << endl;;
    cout << "returned-PID " << pid << endl;
    close(p[1]); //closing the ends of the pipes that are not to be used by parent process
    close(p1[0]);

    ifstream file(argv[1]);
    int lines = 0;

    file>>lines; //reading no of lines in file

    char func[100];
    int a,b;

    Data d;
    int signal;

    for(int x=0;x<lines;x++){
        file>>func>>a>>b; //reading instruction and operands
        strcpy(d.command,func); //adding data to d
        d.a = a;
        d.b = b;
        write(p1[1],&d,sizeof(Data)); //sending data to child process through pipe
        read(p[0],&signal,sizeof(int)); //waiting for signal from child
    }
    
    file.close();

    strcpy(d.command,"exit"); 
    write(p1[1],&d,sizeof(Data)); //sending exit instruction to child 
    read(p[0],&signal,sizeof(int)); //waiting for signal from child

    close(p[1]); //closing pipes
    close(p1[0]);
    return 0;
}