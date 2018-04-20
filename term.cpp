#include "term.h"
#include <sstream>

term::term(double c, double p)
{
    if(p < 0)
        set(c,0);
    else
        set(c,p);
}

term::term(string s) {
    int pos;
    if(s.find('x') != string::npos)
        s[s.find('x')] = 'X';
    stringToTerm(s);
}

term::~term()
{
    deleteMe();
}

term::term(const term &other)
{
    copy(other);
}

term& term::operator=(const term &other)
{
    if(this != &other)
    {
        deleteMe();
        copy(other);
    }
    return *this;
}

double term::operator()(double x)
{
    return coeff * pow(x,power);
}

term& term::operator+=(const term &other)
{
    if(power == other.power)
        coeff += other.coeff;
    return *this;
}

term& term::operator*=(double x)
{
    coeff *= x;
    return *this;
}

void term::copy(const term &other)
{
    coeff = other.coeff;
    power = other.power;
}

void term::deleteMe()
{
    coeff = power = 0;
}

double term::getPower() const
{
    return power;
}

double term::getCoeff() const
{
    return coeff;
}

void term::set(double c, double p)
{
    coeff = c;
    power = p;
}

bool operator<(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff < b.coeff))
            ||
            (a.power < b.power);
}


bool operator<=(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff <= b.coeff))
            ||
            (a.power <= b.power);
}


bool operator==(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff == b.coeff));
}


bool operator!=(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff != b.coeff))
            ||
            (a.power != b.power);
}


bool operator>=(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff >= b.coeff))
            ||
            (a.power >= b.power);
}


bool operator>(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff > b.coeff))
            ||
            (a.power > b.power);
}


term operator+(const term& a, const term &b)
{
    return (a.power == b.power) ? term(a.coeff+b.coeff,a.power)
           : term(0);
}


term operator-(const term& a, const term &b)
{
    return (a.power == b.power) ? term(a.coeff-b.coeff,a.power)
           : term(0);
}


term operator*(const term& a, const term &b)
{
    return term(a.coeff * b.coeff, a.power + b.power);
}


ostream& operator<<(ostream& out, const term &t)
{

    out<<std::showpos<<t.coeff;
    if(t.power != 0)
    {
       out<<"X"<<"^"<<t.power<<"";
    }
    out<<" ";
    return out;
}


istream& operator>>(istream& in, term &t)
{

    t.coeff = t.power = 0;
    stringstream ss;
    string termString;
    cin>>termString;
    if(((termString.find('x') == string::npos) || (termString.find('X') == string::npos)) && (termString.find('^') == string::npos)){
        ss<<termString.substr(0,string::npos);
        ss>>t.coeff;
        t.power = 0;

    }
    else{
        while(!(((termString.find('x') != string::npos) || (termString.find('X') != string::npos)) && (termString.find('^') != string::npos)) || termString.length() < 4){
            cout<<"Please, insert a valid term in the format aX^b"<<endl;
            cin>>termString;
        }

        ss<<termString.substr(0,termString.find("x"));
        ss>>t.coeff;
        ss.clear();
        ss<<termString.substr(termString.find("^"),string::npos);
        ss>>t.power;

    }

    return in;
}

void term::stringToTerm(string s) {
    stringstream ss;
    if(((s.find('x') == string::npos) || (s.find('X') == string::npos)) && (s.find('^') == string::npos)){
        ss<<s.substr(0,string::npos);
        ss>>coeff;
        power = 0;
    }
    else{
        if(!(((s.find('x') != string::npos) || (s.find('X') != string::npos)) && (s.find('^') != string::npos)) || s.length() < 4){
            coeff = 0;
            power = 0;
            return;
        }
        ss<<s.substr(0,s.find("X"));
        ss>>coeff;
        ss.clear();
        ss<<s.substr(s.find("^")+1,string::npos);
        ss>>power;
    }

}


