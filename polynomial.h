#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include "term.h"


class polynomial
{
    public:
        polynomial();
        polynomial(string s);
        ~polynomial();
        polynomial(const polynomial &p);
        polynomial& operator=(const polynomial &p);

        double operator()(double x);
        polynomial operator-();
        bool empty();
        void evaluate(int number);
        polynomial derive();
        polynomial returnDerivative(int i);

        friend
        polynomial operator+(const polynomial& a, const polynomial &b);

        friend
        polynomial operator-(const polynomial& a, const polynomial &b);

        friend
        polynomial operator*(const polynomial& a, const polynomial &b);

        friend
        ostream& operator<<(ostream& out, const polynomial &p);

        friend
        istream& operator>>(istream& in, polynomial &p);

    private:
        std::vector<term> poly;

        void copy(const polynomial& p);
        void deleteAll();
        void order();
        void combineLikeTerms();
        void reduce();

};

#endif // POLYNOMIAL_H
