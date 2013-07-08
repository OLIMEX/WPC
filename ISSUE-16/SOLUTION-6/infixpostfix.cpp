/*!
 * \file infixpostfix.cpp
 *
 * \author Simon Meaden
 * \date   5 July 2013
 *
 * Converts an infix statement to it's equivalent postfix form.
 */

#include <ctype.h>

#include "infixpostfix.h"

using namespace std;

// brackets
const char InfixPostfix::left('(');
const char InfixPostfix::right(')');
// operators
const char InfixPostfix::addition('+');
const char InfixPostfix::subtraction('-');
const char InfixPostfix::multiplication('*');
const char InfixPostfix::division('/');
const char InfixPostfix::modulo('%');
const char InfixPostfix::power('^');
// useful characters
const char InfixPostfix::space(' ');


/*!
 * \brief Constructor for InfixPostfix converter.
 */
InfixPostfix::InfixPostfix() {
}

/*!
 * \brief Converts the incoming string from infix to postfix forms..
 *
 * Converts an infix statement to it's equivalent postfix form. The result is returned in the
 * instring parameter.
 *
 * Returns an integer error code if there is an error.
 * 0 - No error detected.
 * 1 - Unbalanced brackets.
 * 2 - Wrong bracket types. Only () style brackets are catered for.
 *
 * \param[in,out] instring the statement to convert as a std::string.
 * \return an integer error code.
 */
int InfixPostfix::convert(string& instring) {
    string result;
    /*
     * Bracket count. The recursive code doesn't particularly like unbalanced brackets
     * so check first.
     */
    int lCount = 0, rCount = 0;
    for (unsigned int i = 0; i < instring.length(); i++) {
        char c = instring.at(i);
        if (c == left) lCount++;
        if (c == right) rCount++;
        /*
         * If I had the time and was planning on using this extensively I would
         * look into balancing and matching different bracket types. As I don't
         * just throw out the other types.
         */
        if (c == '[' || c == ']' || c == '{' || c == '}') return 2;
    }
    if (lCount != rCount) return 1;

    openBracket(instring, result);
    instring = result;
    return 0;
}

/*
 * Recursive method to convert the infix statement.
 */
string InfixPostfix::openBracket(string& instring, string& outstring)
{
    char inChar, outChar;
    string sub, ops, s = instring;

    while (s.length() > 0)
    {
        inChar = s.at(0);
        sub = s.substr(1);

        switch (inChar)
        {
        case space:
            break; // lose spaces.
        case left:
            s = openBracket(sub, outstring);
            while (ops.length() > 0) {
                outstring += space;
                outstring += ops.at(ops.length() - 1);
                ops = ops.substr(0, ops.length() - 1); // pop off stack
            }
            break; // break out of open case.
        case right:
            while (ops.length() > 0) {
                outstring += space;
                outstring += ops.at(ops.length() - 1);
                ops = ops.substr(0, ops.length() - 1); // pop off stack
            }
            return sub;
        default:
            if (isdigit(inChar))
            {
                if (outstring.length() > 0) outstring += space;
                outstring += inChar;
            } else if (isOperator(inChar))
            {
                while (ops.length() > 0) // there are ops on stack
                {
                    outChar = ops.at(ops.length() - 1); // read top of stack
                    if (testPrecedence(inChar, outChar)) // test it's precedence
                    {
                        outstring += space;
                        outstring += outChar; // copy to queue
                        //                        ops.pop_back(); // Cpp11
                        ops = ops.substr(0, ops.length() - 1); // pop off stack
                    } else {
                        break; // break out of while loop
                    }
                }
                ops += inChar; // push onto stack
            }
            s = sub;
            break; // break out of default
        }
    }
    // finish up the outstanding ops.
    for (unsigned int i = ops.length(); i > 0 ; i--) {
        outstring += space;
        outstring += ops.at(i - 1);
    }
    return s;
}

/*
 * checks whether a character is an operator.
 */
bool InfixPostfix::isOperator(char c)
{
    switch (c)
    {
    case addition:
    case subtraction:
    case multiplication:
    case division:
    case modulo:
        return true;
    default:
        return false;
    }
}
/*
 * Tests for the precedence of the operator. This is based on Edsger Dijkstra's
 * Shunting yard algorithm. See http://en.wikipedia.org/wiki/Shunting-yard_algorithm.
 */
bool InfixPostfix::testPrecedence(char in, char out)
{
    if (
            (in == addition || in == subtraction) ||
            ((in == multiplication || in == division || in == modulo) && !(out == addition || out == subtraction))
            )
    {
        return true;
    }
    return false;

}
