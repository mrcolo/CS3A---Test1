/* EXPRESSION_CALCULATOR v0.1.0
 * I, Francesco Colonnese, do hereby certify that I have derived no assistance for this project or examination from any sources whatever, whether oral, written, or in print. I also understand that if it is found that I have received unauthorized assistance, then I and the individuals involved will receive a failing grade.
 * I, Arman Mansourian, do hereby certify that I have derived no assistance for this project or examination from any sources whatever, whether oral, written, or in print. I also understand that if it is found that I have received unauthorized assistance, then I and the individuals involved will receive a failing grade.
 * CREATED BY FRANCESCO COLONNESE AND ARMAN MANSOURIAN
 */

#include <iostream>
#include "polynomial.h"
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include<fstream>

using namespace std;

//DEFINE FUNCTION POINTER FOR STATE CONTROLLER
typedef void (*fptr)(string, polynomial [], string);

//STRUCT FOR STATE CONTROLLER
struct StateStruct {
    fptr f;
};

//DEFINE FUNCTION POINTER FOR ARGUMENTS
typedef void (*argptr)(char*[], polynomial[], string&, bool&, string, stack<StateStruct>&,vector<string>&);

//HELPER FUNCTIONS
void getInput(const string& prompt, string& line, vector<string> &str);
void fillStack(string line, polynomial polys [26],stack<StateStruct>& g_StateStack);
void clearStack(stack<StateStruct>& g_StateStack);
void cleanInput(string& line);
bool fileExists(const string& filename);
int getDerivation(string s );
bool isExiting(string s);
void input(const string WELCOMEMSG, const string INPUTPROMPT,const string ALPHABET, string command, vector<string>& strRecord,polynomial polys [26], stack<StateStruct>& g_StateStack);

//ARGUMENT FUNCTIONS
void handleArg(int argc,char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack,vector<string>&);
void oneArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack,vector<string>& strRecord);
void twoArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack, vector<string>& strRecord);

//CONTROLLER FUNCTIONS
void let(string line, polynomial polys [26], string ALPHABET);
void eval(string line, polynomial polys [26], string ALPHABET);
void print(string line, polynomial polys [26], string ALPHABET);
void save(string line, polynomial polys [26], string ALPHABET);
void load(string line, polynomial polys [26], string ALPHABET);
void help(string line, polynomial polys [26], string ALPHABET);
void err(string line, polynomial polys [26], string ALPHABET);

int main(int argc, char* argv[]) {

    //INITIAL CONTAINERS FOR DATA
    stack<StateStruct> g_StateStack;
    polynomial polys [26];
    vector<string> strRecord;

    //INITIAL VARS FOR RECORD MODE
    string command, record_filename;
    bool recording = false;

    //CONSTANT VARS
    const string WELCOMEMSG = "Welcome to Expression Calculator. If you don't know what to do, type HELP.\n",
                 INPUTPROMPT = "INPUT: ";
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //HANDLE ARGUMENTS
    try{
        handleArg(argc,argv, polys, record_filename, recording, ALPHABET, g_StateStack, strRecord);
    }
    catch(string& e){
        cout<<"ERROR:"<<endl<<e<<endl<<endl;
        return 0;
    }

    //EXECUTE ALL THE STATES
    input(WELCOMEMSG,INPUTPROMPT,ALPHABET,command,strRecord,polys,g_StateStack);

    //RECORD DATA IF OPTION IS ON
    if(recording) {
        ofstream outfile;
        outfile.open(record_filename);

        for(int i = 0;i < strRecord.size();i++) {
            cout<<"Writing EXPRESSION "<<i<<endl;
            outfile<<strRecord[(strRecord.size()-1)-i]<<endl;
        }
        cout<<"TERMINATING..."<<endl;
        outfile.close();
    }

    return 0;
}

//HELPER FUNCTIONS
void getInput(const string& prompt, string& line, vector<string> &str){
    cout<<prompt;
    getline(cin, line);
    cleanInput(line);
    str.push_back(line);
    cout<<endl;
}
void fillStack(string line, polynomial polys[26], stack<StateStruct>& g_StateStack){

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

    //TURNS STRING TO UPPERCASE
    for (char &i : command)
        i = toupper(i);

    if(command == "LET")
        g_StateStack.push(LET);
    else if(command == "EVAL")
        g_StateStack.push(EVAL);
    else if(command == "PRINT")
        g_StateStack.push(PRINT);
    else if(command == "SAVE")
        g_StateStack.push(SAVE);
    else if(command == "LOAD")
        g_StateStack.push(LOAD);
    else if(command == "EXIT" || command == "")
        cout<<"Exiting Expression Calculator..."<<endl;
    else if(command == "HELP")
        g_StateStack.push(HELP);
    else
        g_StateStack.push(ERR);
}
void clearStack(stack<StateStruct>& g_StateStack){
    for(int i = 0; i< g_StateStack.size();i++)
        g_StateStack.pop();
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
bool isExiting(string s){
    cleanInput(s);
    string command(s.substr(0,s.find(' ')));
    return (command == "EXIT" || command == "");
}
void input(const string WELCOMEMSG, const string INPUTPROMPT,const string ALPHABET, string command, vector<string>& strRecord,polynomial polys [26], stack<StateStruct>& g_StateStack){
    //DISPLAY WELCOME MSG
    bool isCin = true;
    int current = 0;

    //START ITERATION CONTROLLER
    if(g_StateStack.size() != 0){
        isCin = false;
    }
    else{
        cout<<WELCOMEMSG<<endl;
    }

    do{
        try {
            if(isCin){
                getInput(INPUTPROMPT, command, strRecord);
                fillStack(command, polys, g_StateStack);
            }
            else{
                command = strRecord[(strRecord.size()-1)-current];
                if(command != "")
                    cout<<"EXECUTING:"<<command<<endl;
                else
                    cout<<"TERMINATING..."<<endl;

                current++;
            }

            if(!isExiting(command)){
                g_StateStack.top().f(command, polys, ALPHABET);
            }
            else{
                clearStack(g_StateStack);
            }

        }
        catch (string& e) {
            cout << "ERROR:"<<endl<<e<<endl<<endl;
        }

        if(g_StateStack.size() >= 2){
            g_StateStack.pop();
        }
    } while(!g_StateStack.empty());

}

//ARGUMENT FUNCTIONS
void handleArg(int argc,char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack, vector<string>& strRecord){

    argptr argfunctions [2] = {&oneArg,&twoArg};

    if(argc > 3){
        string exception = "OVERLOAD OF ARGUMENTS";
        throw exception;
    }
    else if (argc == 2 || argc == 3){
        argfunctions[argc - 2](argv, polys, record_filename, recording, ALPHABET, g_StateStack, strRecord);
    }
}
void oneArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack,vector<string>& strRecord) {

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
void twoArg(char* argv[], polynomial polys[26], string& record_filename, bool& recording, string ALPHABET, stack<StateStruct>& g_StateStack, vector<string>& strRecord) {
    string first = argv[1], second = argv[2];
    cout<<first<<" "<<second<<endl;
    if(first == "EXECUTE") {
        if(fileExists(argv[2])) {
            string expression;
            ifstream infile;
            infile.open(argv[2]);
            while(getline(infile, expression)){
                    fillStack(expression, polys, g_StateStack);
                    strRecord.push_back(expression);
            }

            infile.close();
        }
        else{
            string ex = "FILE_DOES_NOT_EXIST";
            throw ex;
        }
    }
    else if(first == "RECORD") {
        if(fileExists(argv[2])) {
            string ex = "FILENAME_ALREADY_EXISTS";
            throw ex;
        }
        else {
            record_filename = argv[2];
            recording = true;
        }
    }
    else {
        cout<<argv[1]<<endl;
        string ex = "INCORRECT INPUT FORMAT";
        throw ex;
    }
}

//CONTROLLER FUNCTIONS
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
        cout<<current_print<<" = "<<polys[ALPHABET.find(current_print)]<<endl<<endl;
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
                        cout<<"RESULT: "<< polys[ALPHABET.find(exp1)] + polys[ALPHABET.find(exp2)]<<endl<<endl;
                        polys[ALPHABET.find(editFunction[0])] = polys[ALPHABET.find(exp1)] + polys[ALPHABET.find(exp2)];
                        break;
                    case '-':
                        cout<<"RESULT: "<< polys[ALPHABET.find(exp1)] - polys[ALPHABET.find(exp2)]<<endl<<endl;
                        polys[ALPHABET.find(editFunction[0])] = polys[ALPHABET.find(exp1)] - polys[ALPHABET.find(exp2)];
                        break;
                    case '*':
                        cout<<"RESULT: "<< polys[ALPHABET.find(exp1)] * polys[ALPHABET.find(exp2)]<<endl<<endl;
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

                cout<<editFunction<<" = "<<polys[ALPHABET.find(receiver)].returnDerivative(getDerivation(instruction))<<endl<<endl;
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
                    "\texample: LET F = 2X^1 + 4\n\n"
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