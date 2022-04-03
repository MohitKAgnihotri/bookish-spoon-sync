#include <iostream>
#include <cstring>
using namespace std;

//These funtions are in files: quadratic.c, sum.c, and triples.c
extern "C" void solve_quadratic (int, int);
extern "C" void modular_sum (int, int);
extern "C" void find_triples (int, int);

void calculate(char* command,int a,int b){ //simply checking the command and calling the corresponding function
    if(!strcmp(command,"quadratic")){
        solve_quadratic(a,b);
    }else if(!strcmp(command,"triples")){
        find_triples(a,b);
    }else if (!strcmp(command,"mod-sum"))
    {
        modular_sum(a,b);
    }else{
        cerr<<"Invalid command!"<<endl;
    }
}