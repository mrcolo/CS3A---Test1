#include "polynomial.h"
#include <sstream>
#include <vector>

polynomial::polynomial(string s) {
    stringstream ss;

    ss<<s;
    string current;
    while(ss>>current){
        term current_term(current);
        poly.push_back(current_term);
    }
    this->order();

}

polynomial::polynomial()
{

}

polynomial::~polynomial()
{
    deleteAll();
}

polynomial::polynomial(const polynomial &p)
{
    copy(p);
}

polynomial& polynomial::operator=(const polynomial &other)
{
    if(this != &other)
    {
        deleteAll();
        copy(other);
    }
    return *this;
}

double polynomial::operator()(double x)
{
    double ans = 0;
    for(size_t i = 0; i < poly.size(); ++i)
        ans += poly[i](x);
    return ans;
}

polynomial polynomial::operator-()
{
    for(size_t i = 0; i < poly.size(); ++i)
        poly[i] *= -1;
    return *this;
}

void polynomial::copy(const polynomial& p)
{
    poly = p.poly;
}

void polynomial::deleteAll()
{
    poly.clear();
}

void polynomial::evaluate(int number){
    int sum = 0;
    cout<<"Evaluating Expression ("<<*this<<") at number "<<number<<"..."<<endl;
    for(int i = 0; i< poly.size();i++){
        sum += poly[i].getCoeff()*pow(number,poly[i].getPower());
    }
    cout<<"Result: "<<sum<<endl;

}

polynomial polynomial::derive(){
    string result = "";
    stringstream ss;
    for(int i = 0;i < poly.size(); i++){
        string current;
        term current_term(poly[i].getPower()*poly[i].getCoeff(),poly[i].getPower()-1);
        if(current_term.getCoeff() != 0){
            ss<<current_term;
            ss>>current;
            result+=(current+" ");
            ss.clear();
        }
    }
    polynomial p(result);
    return p;
}

polynomial polynomial::returnDerivative(int i){
    polynomial actual = *this;
    for(int j = 0 ; j < i ; j++){
        actual = actual.derive();
    }

    return actual;
}

bool polynomial::empty(){
    return poly.size() == 0;
}

void polynomial::reduce()
{
    order();
    combineLikeTerms();
}

void polynomial::order()
{
    for(size_t i = 0; i < poly.size(); ++i)
        for(size_t j = 0; j < poly.size(); ++j)
            if(poly[i] > poly[j])
            {
                term temp = poly[i];
                poly[i] = poly[j];
                poly[j] = temp;
            }
    for(size_t i = 0; i < poly.size(); ++i){
        if(poly[i] == 0)
            poly.erase(poly.begin()+i);
    }
}

void polynomial::combineLikeTerms()
{
    vector<term> ans;
    term temp;
    while(!poly.empty())
    {
        temp = poly[0];
        poly.erase(poly.begin(),poly.begin()+1);
        while(temp.getPower() == poly[0].getPower())
        {
            temp += poly[0];
            poly.erase(poly.begin(), poly.begin()+1);
        }
        ans.push_back(temp);
    }
    poly = ans;
}

polynomial operator+(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(size_t i = 0; i < a.poly.size(); ++i)
        for(size_t j = 0; j < b.poly.size(); ++j)
            if(a.poly[i].getPower() == b.poly[j].getPower())
                ans.poly.push_back(a.poly[i] + b.poly[j]);
    ans.reduce();
    return ans;
}


polynomial operator-(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(size_t i = 0; i < a.poly.size(); ++i)
        for(size_t j = 0; j < b.poly.size(); ++j)
            if(a.poly[i].getPower() == b.poly[j].getPower())
                ans.poly.push_back(a.poly[i] - b.poly[j]);
    ans.reduce();
    return ans;
}


polynomial operator*(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(size_t i = 0; i < a.poly.size(); ++i)
        for(size_t j = 0; j < b.poly.size(); ++j)
            ans.poly.push_back(a.poly[i] * b.poly[j]);
    ans.reduce();
    return ans;
}


ostream& operator<<(ostream& out, const polynomial &p)
{
    if(p.poly.empty())
        out<<0;
    else
        for(size_t i = 0; i <p.poly.size(); ++i)
            out<<p.poly[i];
    return out;
}


istream& operator>>(istream& in, polynomial &p)
{
    term input;
    p.poly.clear();

    if(&in == &cin) {
        cout << "Please, write your polynomial expression." << endl;
        string s;
        getline(cin,s);
        polynomial temp(s);
        p = temp;
    }
    else{
        while(in>>input)
            p.poly.push_back(input);
    }

    p.order();

    return in;
}


