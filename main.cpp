#include <iostream>
#include "polynomial.h"

using namespace std;
void getInput(const string &prompt, string &line);
void evalCommand(string &line);

int main()
{
    const string
            COMMAND_PROMPT =
                "input the following: \n"
                "LET (stores algebraic expression as capital letter A-Z)\n"
                "\texample: LET F = 2X + 4\n"
                "EVAL (evaluates pre-stored algebraic expression at a given value)\n"
                "\texample: EVAL F(1/4)\n"
                "PRINT (prints pre-stored algebraic expression)\n"
                "\texample: PRINT F\n"
                ": ",
            ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string command;

    try
    {
        getInput(COMMAND_PROMPT, command);
        cout<<command<<endl;
        evalCommand(command);
        polynomial t;
        cin>>t;
        cout<<t;
    }
    catch (string &e)
    {
        cout << "ERROR:"<<endl<<e<<endl;
    }

    return 0;
}

void getInput(const string &prompt, string &line)
{
    cout<<prompt;
    getline(cin, line);
}

void evalCommand(string &line)
{
    string command(line.substr(0,line.find(' ')));

    if(command == "LET" || command == "let")
    {
        cout<<"input: LET/let"<<endl;
//        if(line.find('=') == line.npos)
//        {
//
//        }
    }
    else if(command == "EVAL" || command == "eval")
    {
        cout<<"input: EVAL/eval"<<endl;
    }
    else if(command == "PRINT" || command == "print")
    {
        cout<<"input: PRINT/print"<<endl;
    }
    else
    {
        cout<<"Incorrect Input Format!!!"<<endl;
    }
}

