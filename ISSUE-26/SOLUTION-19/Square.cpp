// (c) Adrian, England, 29th September 2013
// Released by the author into the public domain

#include <algorithm>
#include <iostream>
#include <utility>

// A point (of course)
struct Point { long x, y; };

// Compute the square as long long to reduce risk of overflow
long long Square(long u)
{
    return long long(u) * long long(u);
}

// The square of the length of the line between two points
long long LengthSquared(Point p, Point q)
{
    return Square(p.x - q.x) + Square(p.y - q.y); 
}

// Whether 4 points constitute a square
// The points may be in any order
// If all 4 points are the same it is not considered a square
bool IsSquare(Point a, Point b, Point c, Point d)
{
    // We can draw 6 lines between the 4 points
    // Compute the squares of the lengths of the lines
    long long lengthsquared[6];
    lengthsquared[0] = LengthSquared(a, b);
    lengthsquared[1] = LengthSquared(a, c);
    lengthsquared[2] = LengthSquared(a, d);
    lengthsquared[3] = LengthSquared(b, c);
    lengthsquared[4] = LengthSquared(b, d);
    lengthsquared[5] = LengthSquared(c, d);

    // Sort the lengths into ascending numerical order
    std::sort(std::begin(lengthsquared), std::end(lengthsquared));

    // If and only if it is a square we have 4 sides and 2 diagonals
    // The sides should be identical and the diagonals twice as long (when squared)
    long long sidesquared = lengthsquared[0];
    if (sidesquared == 0)
    {
        // All 4 points coincident
        return false;
    }
    if (lengthsquared[1] != sidesquared || lengthsquared[2] != sidesquared || lengthsquared[3] != sidesquared)
    {
        // Not a rhombus
        return false;
    }
    if (lengthsquared[4] != sidesquared * 2 || lengthsquared[5] != sidesquared * 2)
    {
        // Rhombus but not a square
        return false;
    }
    return true;
}

int main()
{
    std::cout << IsSquare({ 0, 0}, { 0, 1}, { 1, 1}, { 1, 0}) << std::endl;
    std::cout << IsSquare({ 0, 0}, { 2, 1}, { 3,-1}, { 1,-2}) << std::endl;
    std::cout << IsSquare({ 0, 0}, { 1, 1}, { 0, 1}, { 1, 0}) << std::endl;
    std::cout << IsSquare({ 0, 0}, { 0, 2}, { 3, 2}, { 3, 0}) << std::endl;
    std::cout << IsSquare({ 0, 0}, { 3, 4}, { 8, 4}, { 5, 0}) << std::endl;
    std::cout << IsSquare({ 0, 0}, { 0, 0}, { 1, 1}, { 0, 0}) << std::endl;
    std::cout << IsSquare({ 0, 0}, { 0, 0}, { 1, 0}, { 0, 1}) << std::endl;
    return 0;
}
