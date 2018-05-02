#include "polynomial.h"
#include <sstream>
#include <vector>

polynomial::polynomial(string s) {
    stringstream ss;

    ss<<s;
    string current;
    while(ss>>current){
        term current_term(current);
        if(current_term.getCoeff() != 0)
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
        this->combineLikeTerms();
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

void polynomial::evaluate(fraction f){
    double sum = 0;
    double number = f.toDouble();
    cout<<"Evaluating Expression ("<<*this<<") at number "<<number<<"..."<<endl<<endl;
    for(int i = 0; i< poly.size();i++){
        sum += poly[i].getCoeff()*pow(number,poly[i].getPower());
    }
    cout<<"Result: "<<sum<<endl<<endl;

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
   // cout<<"i"<<endl;
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
    order();

    while(!poly.empty()){

        temp = poly[0]; //store first element in a variable

        poly.erase(poly.begin(),poly.begin()+1);//erase first element from vector
        if(temp.getPower() == poly[0].getPower()){

            temp = temp + poly[0];
            if(poly.size() >= 1)
             poly.erase(poly.begin(), poly.begin()+1);
        }
        if(temp.getCoeff() != 0)
            ans.push_back(temp);

    }

    poly = ans;
}

polynomial operator+(const polynomial& a, const polynomial &b){
    polynomial ans;

    for(int i=0; i<a.poly.size(); i++){
        ans.poly.push_back(a.poly[i]);

    }

    for(int i=0; i<b.poly.size(); i++){
        ans.poly.push_back(b.poly[i]);
    }

    ans.combineLikeTerms();

    return ans;
}


polynomial operator-(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(int i=0; i<a.poly.size(); i++){
        ans.poly.push_back(a.poly[i]);

    }

    for(int i=0; i<b.poly.size(); i++){
        ans.poly.push_back(-1*b.poly[i]);
    }
    ans.combineLikeTerms();
    return ans;
}


polynomial operator*(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(int i = 0; i < a.poly.size(); ++i){
        for(int j = 0; j < b.poly.size(); ++j){
            term temp = a.poly[i] * b.poly[j];
            ans.poly.push_back(temp);
        }
    }

    ans.combineLikeTerms();
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


istream& operator>>(istream& in, polynomial &p){
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



