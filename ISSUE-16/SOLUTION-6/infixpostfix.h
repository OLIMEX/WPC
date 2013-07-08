#ifndef INFIXPOSTFIX_H
#define INFIXPOSTFIX_H

#include <string>

/*!
 * \class InfixPostfix
 *
 * \brief Converts an infix statement to it's equivalent postfix form.
 * *
 * \author Simon Meaden
 * \date   5 July 2013
 */
class InfixPostfix {
public:
    InfixPostfix();

    int convert(std::string &instring);

protected:
    static const char left;
    static const char right;
    static const char addition;
    static const char subtraction;
    static const char multiplication;
    static const char division;
    static const char modulo;
    static const char power;
    static const char space;

    std::string openBracket(std::string& instring, std::string &outstring);
    bool isOperator(char c);
    bool testPrecedence(char in, char out) ;
};

#endif // INFIXPOSTFIX_H
