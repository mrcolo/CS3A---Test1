#include <iostream>
#include "polynomial.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stack>
using namespace std;

typedef void (*fptr)(string, polynomial [], string);

struct StateStruct {
    fptr f;
};

string getInput(const string prompt, string& line);
void evalCommand(string line, polynomial polys [26],stack<StateStruct>& g_StateStack);
bool exitCondition(string line);
void cleanInput(string& line);
bool fileExists(const string& filename);
int getDerivation(string s );

void let(string line, polynomial polys [26], string ALPHABET);
void eval(string line, polynomial polys [26], string ALPHABET);
void print(string line, polynomial polys [26], string ALPHABET);
void save(string line, polynomial polys [26], string ALPHABET);
void load(string line, polynomial polys [26], string ALPHABET);
void help(string line, polynomial polys [26], string ALPHABET);
void exit(string line, polynomial polys [26], string ALPHABET);

stack<StateStruct> g_StateStack;

int main(int argc, char* argv[]){

    const string WELCOMEMSG = "Welcome to Expression Calculator. If you don't know what to do, type HELP.\n",
                 INPUTPROMPT = "INPUT: ";

    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

     //fptr commands[7] = {&let,&eval,&print,&save,&load,&help, &exit};
    //TODO Create Functions for each case.
    switch (argc){
        case 2:
            cout<<"One Argument"<<argv[1]<<endl;
            break;
        case 3:
            cout<<"Two arguments!"<<argv[2]<<endl;
    }

    string command = "";

    //App starts
    cout<<WELCOMEMSG<<endl;
    polynomial polys [26];

    //Basic Controller
    do{

        try {
            command = getInput(INPUTPROMPT,command);
            evalCommand(command, polys ,g_StateStack);
            g_StateStack.top().f(command ,polys, ALPHABET); 
        }
        catch (string& e){
            cout << "ERROR:"<<endl<<e<<endl<<endl;
        }

    }while(exitCondition(command));

    //TODO save;

    return 0;
}

string getInput(const string prompt, string& line){

    cout<<prompt;
    getline(cin, line);

    cleanInput(line);

    cout<<endl;
    return line;
}

void evalCommand(string line, polynomial polys[26], stack<StateStruct>& g_StateStack){

    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    StateStruct LET,EVAL,PRINT,SAVE,LOAD,HELP,EXIT;

    LET.f = &let;
    EVAL.f = &eval;
    PRINT.f = &print;
    SAVE.f = &save;
    LOAD.f = &load;
    HELP.f = &help;
    EXIT.f = &exit;

    string command(line.substr(0,line.find(' ')));

    //turns string to uppercase
    for(int i = 0; i < command.length(); i++ )
        command[i] = toupper(command[i]);

    //TODO use function pointers to execute rather than if statements
    if(command == "LET"){
        g_StateStack.push(LET);
    }
    else if(command == "EVAL"){
        g_StateStack.push(EVAL);
    }
    else if(command == "PRINT"){
        g_StateStack.push(PRINT);
    }
    else if(command == "SAVE") {
        g_StateStack.push(SAVE);
    }
    else if(command == "LOAD") {
        g_StateStack.push(LOAD);
    }
    else if(command == "EXIT" || command == ""){
        g_StateStack.push(EXIT);
    }
    else if(command == "HELP"){
        g_StateStack.push(HELP);
    }
    else
    {
        string exception = "INCORRECT_INPUT";
        throw exception;
    }
}

bool exitCondition(string line){
    for(int i = 0; i < line.length();i++)
        line[i] = toupper(line[i]);

    return (line != "EXIT" && line != "");

}

void cleanInput(string& line){
    for(int i = 0; 1; i++){
        if(line[i] == ' ') {
            line = line.substr(i, string::npos);
        }
        else{
            line = line.substr(i , string::npos);
            break;
        }
    }
}

bool fileExists(const string &filename) {
    ifstream infile(filename.c_str());
    return infile.good();
}

int getDerivation(string s ) {
    //get the number of the derivative we are looking for.
    int counter = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '\'')
            counter++;
    }
    return counter;
}

void let(string line, polynomial polys [26], string ALPHABET){
    string exception;
    size_t pos;


    if((pos = line.find('=')) != string::npos){
        char current_exp = toupper(line[pos-2]);

        polynomial p(line.substr(pos+2, string::npos));

        cout<<"Generated "<<current_exp<< " = "<<p<<endl<<endl;

        polys[ALPHABET.find(current_exp)] = p;
        cout<<polys[ALPHABET.find(current_exp)]<<endl;
    }
    else{
        exception = "LET not valid. Function not provided.";
        throw exception;
    }
}
void eval(string line, polynomial polys [26], string ALPHABET){
    string current_eval = line.substr(line.find("EVAL")+6,string::npos);

    current_eval[0] = toupper(current_eval[0]);

    polys[ALPHABET.find(current_eval[0])].evaluate(atoi(&current_eval[2]));

}
void print(string line, polynomial polys [26], string ALPHABET){
    string current_print = line.substr(line.find("PRINT")+7,string::npos);

    if(current_print.length() == 1){
        current_print = toupper(current_print[0]);
        cout<<current_print<<" = "<<polys[ALPHABET.find(current_print)]<<endl;
    }
    else{
        int pos;
        if((pos = current_print.find("=")) != string::npos){

            string editFunction = current_print.substr(pos-2,pos-1);
            editFunction[0] = toupper(editFunction[0]);
            string instruction = current_print.substr(pos+2,string::npos);

            char exp1,exp2,op;
            if(instruction.find('\'') == string::npos){
                exp1 = toupper(instruction[0]);
                op = instruction [2];
                exp2 = toupper(instruction[4]);

                switch(op){
                    case '+':
                        cout<<"RESULT: "<< polys[ALPHABET.find(exp1)] + polys[ALPHABET.find(exp2)]<<endl;
                        polys[ALPHABET.find(editFunction[0])] = polys[ALPHABET.find(exp1)] + polys[ALPHABET.find(exp2)];
                        break;
                    case '-':
                        cout<<"RESULT: "<< polys[ALPHABET.find(exp1)] - polys[ALPHABET.find(exp2)]<<endl;
                        polys[ALPHABET.find(editFunction[0])] = polys[ALPHABET.find(exp1)] - polys[ALPHABET.find(exp2)];
                        break;
                    case '*':
                        cout<<"RESULT: "<< polys[ALPHABET.find(exp1)] * polys[ALPHABET.find(exp2)]<<endl;
                        polys[ALPHABET.find(editFunction[0])] = polys[ALPHABET.find(exp1)] * polys[ALPHABET.find(exp2)];
                        break;

                    default:
                        string exception = "BAD_INPUT";
                        throw exception;
                }
            }
            else{
                int editFunctionIndex = ALPHABET.find(editFunction[0]);

                char receiver = toupper(instruction[0]);

                polys[editFunctionIndex] = polys[ALPHABET.find(receiver)].returnDerivative(getDerivation(instruction));

                cout<<editFunction<<" = "<<polys[ALPHABET.find(receiver)].returnDerivative(getDerivation(instruction))<<endl;
            }
        }
    }
}
void save(string line, polynomial polys [26], string ALPHABET){
    string outfile_name(line.substr(line.find("SAVE")+6, string::npos));

    if(fileExists(outfile_name)) {
        string filename_error = "FILENAME_ALREADY_EXISTS";
        throw filename_error;
    }
    else {
        ofstream outfile;
        outfile.open(outfile_name);
        for(size_t i = 0; i < 26; ++i) {
            outfile<<polys[i]<<endl;
        }
        outfile.close();
    }

}
void load(string line, polynomial polys [26], string ALPHABET){

    string infile_name(line.substr(line.find("LOAD")+6, string::npos));

    if(fileExists(infile_name)) {
        string expression;
        int lineNumber = 0;
        ifstream infile;
        infile.open(infile_name);
        while(getline(infile, expression)) {
            polynomial temp_poly(expression);

            polys[lineNumber] = temp_poly;
            lineNumber++;
        }
        infile.close();
    }
    else {
        string file_error = "FILE_DOESNT_EXIST";
        throw file_error;
    }

}
void help(string line, polynomial polys [26], string ALPHABET){
    const string INSTRUCTIONS =
            "POSSIBLE INSTRUCTIONS: \n\n"
                    "- LET  => Stores algebraic expression as capital letter A-Z\n\n"
                    "\texample: LET F = 2X + 4\n\n"
                    "- EVAL => evaluates pre-stored algebraic expression at a given value\n\n"
                    "\texample: EVAL F(1/4)\n\n"
                    "- PRINT => prints pre-stored algebraic expression\n\n"
                    "\texample: PRINT F\n\n"
                    "- SAVE => saves in the following file 26 pre-stored algebraic expression\n\n"
                    "\texample: SAVE file.exp\n\n"
                    "- LOAD => loads from the following file 26 pre-stored algebraic expression\n\n"
                    "\texample: LOAD file.exp\n\n";

    cout<<INSTRUCTIONS<<endl;
}
void exit(string line, polynomial polys [26], string ALPHABET){
    cout<<"Exiting Expression Calculator..."<<endl;
    return;
}

