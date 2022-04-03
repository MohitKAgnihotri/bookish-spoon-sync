#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//These funtions are in files: quadratic.c, sum.c, and triples.c
extern "C" void solve_quadratic (int, int);
extern "C" void modular_sum (int, int);
extern "C" void find_triples (int, int);

int main(int argc, char** argv){
    if(argc!=2){ //checking if arguments not passed or extra arguments passed
        cerr<<"Invalid arguments!"<<endl;
    }

    ifstream file(argv[1]);

    int lines = 0;

    file>>lines; //reading no of lines in file

    char func[100];
    int a,b;

    for(int x=0;x<lines;x++){ 
        file>>func>>a>>b; //reading instruction and operands

        if(!strcmp(func,"quadratic")){ //simply checking the command and calling the corresponding function
            solve_quadratic(a,b);
        }else if(!strcmp(func,"triples")){
            find_triples(a,b);
        }else if (!strcmp(func,"mod-sum"))
        {
            modular_sum(a,b);
        }else{
            cerr<<"Invalid file!"<<endl;
            break;
        }
    }
    
    return 0;
}