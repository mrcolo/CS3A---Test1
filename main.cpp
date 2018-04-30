#include <iostream>
#include "polynomial.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

string getInput(const string& prompt, string& line, vector<string> &str);
void evalCommand(string line, polynomial polys[26]);
bool exitCondition(string line);
void cleanInput(string& line);
bool fileExists(const string& filename);
int getDerivation(string s);
void oneArg(char* argv[], polynomial polys[26]);
void twoArg(char* argv[], polynomial polys[26], string record_filename, bool recording);

int main(int argc, char* argv[]) {

    polynomial polys [26];
    vector<string> strRecord;
    string command, record_filename;
    bool recording = false;

    const string WELCOMEMSG = "Welcome to Expression Calculator. If you don't know what to do, type HELP.\n",
                 INPUTPROMPT = "INPUT: ";

    //TODO Create Functions for each case.
    switch (argc){
        case 2:
            cout<<"One Argument! Loading "<<argv[1]<<endl;
            oneArg(argv, polys);
            break;
        case 3:
            cout<<"Two arguments! "<<argv[1]<<" "<<argv[2]<<endl;
            twoArg(argv, polys, record_filename, recording);
            break;
        default:
            if(argc>3)
                cout<<"ERROR: TOO MANY ARGUMENTS IN CddOMMAND LINE"<<endl;
            break;
    }

    //App starts
    cout<<WELCOMEMSG<<endl;

    //Basic Controller
    do{
        try {
            evalCommand(getInput(INPUTPROMPT, command, strRecord), polys);
        }
        catch (string& e){
            cout << "ERROR:"<<endl<<e<<endl;
        }

    }while(exitCondition(command));

    //TODO save;
    if(recording) {
        ofstream outfile;
        outfile.open(record_filename);
        for(const auto &i : strRecord) {
            outfile<<i<<endl;
        }
        outfile.close();
    }
    return 0;
}

string getInput(const string& prompt, string& line, vector<string> &str){
    cout<<prompt;
    getline(cin, line);
    cleanInput(line);
    str.push_back(line);
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

    string command(line.substr(0,line.find(' ')));

    //turns string to uppercase
    for (char &i : command)
        i = toupper(i);

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
    else if(command == "SAVE") {
        string outfile_name(line.substr(line.find("SAVE")+6, string::npos));
        if(fileExists(outfile_name)) {
            string filename_exists = "FILENAME_ALREADY_EXISTS";
            throw filename_exists;
        }
        else {
            ofstream outfile;
            outfile.open(outfile_name);
            for(size_t i = 0; i < 26; ++i) {
                outfile<<polys[i]<<endl;
            }
            outfile.close();
        }
        //TODO add a few couts that explain what the program is doing
    }
    else if(command == "LOAD") {
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
        //TODO add a few couts that explain what the program is doing
        else {
            string file_find_error = "FILE_DOESNT_EXIST";
            throw file_find_error;
        }
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

int getDerivation(string s) {

    int counter = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '\'')
            counter++;
    }
    return counter;
}

void oneArg(char* argv[], polynomial polys[26]) {
    if(fileExists(argv[1])) {
        string expression;
        int lineNumber = 0;
        ifstream infile;
        infile.open(argv[1]);
        while(getline(infile, expression)) {
            polynomial temp_poly(expression);
            polys[lineNumber] = temp_poly;
            lineNumber++;
        }
        infile.close();
    }
    else {
        cout<<"FILE_DOESNT_EXIST"<<endl;
    }
}

void twoArg(char* argv[], polynomial polys[26], string record_filename, bool recording) {
    if(argv[1] == "EXECUTE") {
        if(fileExists(argv[2])) {
            string expression;
            ifstream infile;
            infile.open(argv[2]);
            while(getline(infile, expression)) {
                evalCommand(expression, polys);
            }
            infile.close();
        }
    }
    else if(argv[1] == "RECORD") {
        if(fileExists(argv[2])) {
            cout<<"FILENAME_ALREADY_EXISTS"<<endl;
        }
        else {
            record_filename = argv[2];
            recording = true;
        }
    }
    else {
        cout<<"ERROR: INCORRECT INPUT FORMAT"<<endl;
    }
}
