#include <iostream>
#include "polynomial.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

string getInput(const string& prompt, string& line);
void evalCommand(string line, polynomial polys [26]);
bool exitCondition(string line);
void cleanInput(string& line);
bool fileExists(const string& filename);

int main(int argc, char* argv[]){

                 const string WELCOMEMSG = "Welcome to Expression Calculator. If you don't know what to do, type HELP.\n",
                 INPUTPROMPT = "INPUT: ";

    //TODO Create Functions for each case.
    switch (argc){
        case 1:
            cout<<"No arguments."<<endl;
            break;
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
            evalCommand(getInput(INPUTPROMPT, command), polys);

        }
        catch (string& e){
            cout << "ERROR:"<<endl<<e<<endl;
        }

    }while(exitCondition(command));

    //TODO save;
    return 0;
}

string getInput(const string& prompt, string& line){
    cout<<prompt;
    getline(cin, line);
    cleanInput(line);
    cout<<endl;
    return line;
}

void evalCommand(string line, polynomial polys[26]){
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                 INSTRUCTIONS =
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

    //TODO use string.find_first_of() instead
    string command(line.substr(0,line.find(' ')));

    //turns string to uppercase
    for(int i = 0; i < command.length(); i++ )
        command[i] = toupper(command[i]);

    //TODO use function pointers to execute rather than if statements
    if(command == "LET"){
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
    else if(command == "EVAL"){

        string current_eval = line.substr(line.find("EVAL")+6,string::npos);

        current_eval[0] = toupper(current_eval[0]);

        polys[ALPHABET.find(current_eval[0])].evaluate(atoi(&current_eval[2]));

    }
    else if(command == "PRINT"){
        string current_print = line.substr(line.find("PRINT")+7,string::npos);

        if(current_print.length() == 1){
            current_print = toupper(current_print[0]);
            cout<<current_print<<" = "<<polys[ALPHABET.find(current_print)]<<endl;
        }


    }
    else if(command == "SAVE") {
        string outfile_name(command.find("SAVE")+6, string::npos);
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
        cout<<INSTRUCTIONS<<endl;
    }
    else if(command == "LOAD") {
        string infile_name(command.find("LOAD")+6, string::npos);
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
        cout<<INSTRUCTIONS<<endl;
    }
    else if(command == "EXIT" || command == ""){
        cout<<"Exiting Expression Calculator..."<<endl;
        return;
    }
    else if(command == "HELP"){
        cout<<INSTRUCTIONS<<endl;
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
