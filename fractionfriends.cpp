#include "fraction.h"

ostream& operator<<(ostream& out, const fraction &f)
{
    out<<f.num;
    if(f.denom != 1)
       out<<"/"<<f.denom;
    return out;
}

istream& operator>>(istream& in,  fraction &f)
{
    stringstream convert;
    char junk, digit;
    f.denom = 1;
    in>>f.num;
    if(in.peek() == '/')
    {
        in>>junk>>f.denom;
        f.reduce();
    }
    else
        if(in.peek() == '.')
        {
            string ans;
            in>>junk;
            stringstream number;
            number<<f.num<<".";
            while(in.peek()>='0' && in.peek() <= '9')
            {
                in>>digit;
                number <<digit;
            }
            number >> ans;
            f = fraction(ans);
        }

    return in;
}


fraction operator+(const fraction &x, const fraction &y)
{
    int num = x.num*y.denom + x.denom*y.num,
        denom = x.denom*y.denom;
    fraction ans(num,denom);
    return ans;
}


fraction operator-(const fraction &x, const fraction &y)
{
    int num = x.num*y.denom - x.denom*y.num,
        denom = x.denom*y.denom;
    fraction ans(num,denom);
    return ans;
}


fraction operator*(const fraction &x, const fraction &y)
{
    int num = x.num*y.num,
        denom = x.denom*y.denom;
    fraction ans(num,denom);
    return ans;
}


fraction operator/(const fraction &x, const fraction &y)
{
    int num = x.num*y.denom,
        denom = x.denom*y.num;
    fraction ans(num,denom);
    return ans;
}


bool operator==(const fraction &x, const fraction &y)
{
    return x.num*y.denom == x.denom*y.num;
}


bool operator!=(const fraction &x, const fraction &y)
{
    return x.num*y.denom != x.denom*y.num;
}


bool operator<(const fraction &x, const fraction &y)
{
    return x.num*y.denom < x.denom*y.num;
}


bool operator>(const fraction &x, const fraction &y)
{
    return x.num*y.denom > x.denom*y.num;
}


fraction operator<=(const fraction &x, const fraction &y)
{
    return !(x > y);
}


fraction operator>=(const fraction &x, const fraction &y)
{
    return !(x < y);
}
