#include <iostream>
#include "polynomial.h"
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

//DEFINE FUNCTION POINTER FOR STATE CONTROLLER
typedef void (*fptr)(string, polynomial [], string);

//struct for STATE CONTROLLER
struct StateStruct {
    fptr f;
};


typedef void (*argptr)(char*[], polynomial[], string&, bool&, string, stack<StateStruct>&);

//Functions for controller --- CONTROLLER
void getInput(const string& prompt, string& line, vector<string> &str);
void evalCommand(string line, polynomial polys [26],stack<StateStruct>& g_StateStack);
void cleanInput(string& line);
bool fileExists(const string& filename);
int getDerivation(string s );

//Functions returning from pointer --- ACTIONS
void let(string line, polynomial polys [26], string ALPHABET);
void eval(string line, polynomial polys [26], string ALPHABET);
void print(string line, polynomial polys [26], string ALPHABET);
void save(string line, polynomial polys [26], string ALPHABET);
void load(string line, polynomial polys [26], string ALPHABET);
void help(string line, polynomial polys [26], string ALPHABET);
void err(string line, polynomial polys [26], string ALPHABET);

//Functions for cmd line args -- ARGS
void handleArg(int argc,char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack);
void oneArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack);
void twoArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack);

int main(int argc, char* argv[]) {

    //INITIAL CONTAINERS FOR DATA
    stack<StateStruct> g_StateStack;
    polynomial polys [26];
    vector<string> strRecord;

    string command, record_filename;
    bool recording = false;

    //CONSTANT VARS
    const string WELCOMEMSG = "Welcome to Expression Calculator. If you don't know what to do, type HELP.\n",
                 INPUTPROMPT = "INPUT: ";
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //HANDLE ARGUMENTS
    try{
        handleArg(argc,argv, polys, record_filename, recording, ALPHABET, g_StateStack);
    }
    catch(string& e){
        cout<<"ERROR:"<<endl<<e<<endl<<endl;
    }

    //DISPLAY WELCOME MSG
    cout<<WELCOMEMSG<<endl;

    //START ITERATION CONTROLLER
    do{
        try {
            getInput(INPUTPROMPT, command, strRecord);
            evalCommand(command, polys, g_StateStack);
            g_StateStack.top().f(command, polys, ALPHABET);
        }
        catch (string& e) {
            cout << "ERROR:"<<endl<<e<<endl<<endl;
        }
        
        if(g_StateStack.size() == 2){
            g_StateStack.pop();
        }

    } while(!g_StateStack.empty());

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

void getInput(const string& prompt, string& line, vector<string> &str){
    cout<<prompt;
    getline(cin, line);
    cleanInput(line);
    str.push_back(line);
    cout<<endl;
}

void evalCommand(string line, polynomial polys[26], stack<StateStruct>& g_StateStack){

    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    StateStruct LET,EVAL,PRINT,SAVE,LOAD,HELP,ERR;

    LET.f = &let;
    EVAL.f = &eval;
    PRINT.f = &print;
    SAVE.f = &save;
    LOAD.f = &load;
    HELP.f = &help;
    ERR.f = &err;

    string command(line.substr(0,line.find(' ')));

    //turns string to uppercase
    for (char &i : command)
        i = toupper(i);

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
        cout<<"Exiting Expression Calculator..."<<endl;
        g_StateStack.pop();

    }
    else if(command == "HELP"){
        g_StateStack.push(HELP);

    }
    else
    {
        g_StateStack.push(ERR);

    }
}

void cleanInput(string& line){
    for(int i = 0; true; i++){
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

void oneArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack) {

    cout<<"Loading "<<argv[1]<<endl;
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

void twoArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack) {

    cout<<argv[1]<<" "<<argv[2]<<endl;
    if(argv[1] == "EXECUTE") {
        if(fileExists(argv[2])) {
            string expression;
            ifstream infile;
            infile.open(argv[2]);
            while(getline(infile, expression)) {
                evalCommand(expression, polys, g_StateStack);
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

void let(string line, polynomial polys [26], string ALPHABET){

    string exception;
    size_t pos;


    if((pos = line.find('=')) != string::npos){
        char current_exp = toupper(line[pos-2]);

        polynomial p(line.substr(pos+2, string::npos));

        cout<<"Generated "<<current_exp<< " = "<<p<<endl<<endl;

        polys[ALPHABET.find(current_exp)] = p;
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

    string infile_name(line.substr(line.find("LOAD") + 6, string::npos));

    if (fileExists(infile_name)) {
        string expression;
        int lineNumber = 0;
        ifstream infile;
        infile.open(infile_name);
        while (getline(infile, expression)) {
            polynomial temp_poly(expression);
            polys[lineNumber] = temp_poly;
            lineNumber++;
        }
        infile.close();
    } else {
        cout << "FILE_DOESNT_EXIST" << endl;
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
void err(string line, polynomial polys [26], string ALPHABET){
    string exception = "BAD_INPUT";
    throw exception;
}

void handleArg(int argc,char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack){

    argptr argfunctions [2] = {&oneArg,&twoArg};

    if(argc > 3){
        string exception = "OVERLOAD OF ARGUMENTS";
        throw exception;
    }
    else{
        argfunctions[argc - 2](argv, polys, record_filename, recording, ALPHABET, g_StateStack);
    }
}


