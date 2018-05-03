#include "term.h"
#include <sstream>

term::term(double c, double p)
{
    if(c == 0){
        p = 0;
    }
    if(p < 0)
        set(c,0);
    else
        set(c,p);
}

term::term(string s) {

    stringToTerm(s);
}

term::term(fraction c, fraction p) {
    if(p < 0)
        set(c);
    else
        set(c,p);
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
    return coeff.toDouble() * pow(x, power.toDouble());
}

term& term::operator+=(const term &other)
{
    if(power == other.power){
        coeff = coeff + other.coeff;
    }

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
    return power.toDouble();
}

double term::getCoeff() const
{
    return coeff.toDouble();
}

void term::set(double c, double p)
{
    coeff = c;
    power = p;
}

void term::set(fraction c, fraction p){
    coeff = c.getNum()/c.getDenom();
    power = p.getNum()/p.getDenom();
}


bool operator<(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff < b.coeff))
            ||
            (a.power < b.power);
}


bool operator<=(const term& a, const term &b)
{
    return (a.power == b.power && (a.coeff <= b.coeff))
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
       out<<"X"<<"^"<<t.power;
    }
    out<<" ";
    return out;
}


istream& operator>>(istream& in, term &t)
{

    t.coeff = t.power = 0;
    //stringstream ss;
    string termString;
    cin>>termString;

    t.stringToTerm(termString);
    return in;
}

bool term::isMixedNum(string s) {
    return (s[0] == '|' && s[s.size()-1] == '|');
}

void term::stringToTerm(string s) {
    stringstream ss;

    if(s.find('x') != string::npos)
        s[s.find('x')] = 'X';

    bool yesUpperx = s.find('X') != string::npos;
    bool yesCap = s.find("^") != string::npos;

    if(yesUpperx && yesCap){
        if(isMixedNum(s.substr(0,s.find("X")))){
            fraction f(s.substr(1,s.find("X")-1));
            coeff = f;
        } else {
            fraction f(s.substr(0,s.find("X")));
            coeff = f;
        }

        if(isMixedNum(s.substr(s.find("^")+1,string::npos))){
            fraction g(s.substr(s.find("^")+2,string::npos-1));
            power = g;
        } else {
            fraction g(s.substr(s.find("^")+1,string::npos));
            power = g;
        }
    }
    else{
            ss<<s.substr(0,string::npos);
            ss>>coeff;
            power = 0;
    }
    if (coeff == 0)
        power = 0;
}
