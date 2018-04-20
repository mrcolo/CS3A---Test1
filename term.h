#ifndef TERM_H
#define TERM_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "fraction.h"
using namespace std;

class term
{
    public:
        term(double c = 1, double p = 0);
        term(string s);
        term(fraction c,fraction p);
        ~term();
        term(const term &other);
        term& operator=(const term &other);
        term& operator+=(const term &other);
        double operator()(double x);
        term& operator*=(double x);
        double getPower() const;
        double getCoeff() const;
        void set(double c = 1, double p = 0);
        void set(fraction c = 1, fraction p = 0);

        friend
        bool operator<(const term& a, const term &b);

        friend
        bool operator<=(const term& a, const term &b);

        friend
        bool operator==(const term& a, const term &b);

        friend
        bool operator!=(const term& a, const term &b);

        friend
        bool operator>=(const term& a, const term &b);

        friend
        bool operator>(const term& a, const term &b);

        friend
        term operator+(const term& a, const term &b);

        friend
        term operator-(const term& a, const term &b);

        friend
        term operator*(const term& a, const term &b);

        friend
        ostream& operator<<(ostream& out, const term &t);

        friend
        istream& operator>>(istream& in, term &t);
    private:
        fraction coeff, power;
        void stringToTerm(string s);
        void copy(const term &other);
        void deleteMe();
};

#endif // TERM_H
