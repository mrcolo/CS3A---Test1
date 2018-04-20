#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class fraction
{
    public:
       // fraction();  // Default constructor
        fraction(int n = 0, int d = 1); //Two argument constructor
        fraction(double x);
        fraction(string x);
        ~fraction(); // Destructor
        fraction(const fraction& other); // Copy constructor

        fraction& operator+=(const fraction& other); //Assignment operator
        fraction& operator-=(const fraction& other);
        fraction& operator/=(const fraction& other);
        fraction& operator*=(const fraction& other);
        fraction& operator=(const fraction& other);

        void set(int n, int d); //Mutator - 2 argument
        int getNum() const; //Accessor
        int getDenom() const;//Accessor
        double toDouble() const;
        void display() const;//Display values

        friend
        ostream& operator<<(ostream& out, const fraction &f);

        friend
        istream& operator>>(istream& in, fraction &f);

        friend
        fraction operator+(const fraction &x, const fraction &y);

        friend
        fraction operator-(const fraction &x, const fraction &y);

        friend
        fraction operator*(const fraction &x, const fraction &y);

        friend
        fraction operator/(const fraction &x, const fraction &y);

        friend
        bool operator==(const fraction &x, const fraction &y);

        friend
        bool operator!=(const fraction &x, const fraction &y);

        friend
        bool operator<(const fraction &x, const fraction &y);

        friend
        bool operator>(const fraction &x, const fraction &y);

        friend
        bool operator<=(const fraction &x, const fraction &y);

        friend
        bool operator>=(const fraction &x, const fraction &y);

        void reduce(); //Helper function

    private:
        int num, denom;


        int gcd(int p, int q);//Helper function
        void stringToFraction(string x);

};

#endif // FRACTION_H
