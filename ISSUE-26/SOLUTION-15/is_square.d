/*
 * Olimex WPC #26
 *
 * Determine whether or not four points lie on a square.
 *
 * The program calculates the (squared) distances between all points
 * and makes a determination based on the distribution of the distances.
 *
 * Compiled with DMD32 v2.063.2 on Linux Mint 15
 * Note: does not work when compiled with gdc 4.6.4
 *
 */

import std.regex;
import std.string;
import std.conv;
import std.stdio;
import std.math;

void preamble()
{
     writeln();
     writeln("Determine whether or not four points form a square");
     writeln();
     writeln("Enter four 2D points, e.g.:");
     writeln("(0,0),(0,1),(1,1),(1,0)");
     writeln("or");
     writeln("(0.5,0.5),(0.5,1.5),(1.5,1.5),(1.5,0.5)");
     writeln();
     writeln("Enter a blank line to exit the program");
     writeln();
}

// Perform the actual check
bool perform_check(real points[4][2])
{
    int[real] distances;

    for(size_t p1 = 0; p1 < 3; p1++)
    {
        for(size_t p2 = p1 + 1; p2 < 4; p2++ )
        {
            real squared_distance = pow(points[p1][0] - points[p2][0], 2) + pow(points[p1][1] - points[p2][1], 2);
            distances[squared_distance]++;
        }
    }

    int[] lengths = distances.values.sort;

    if ((lengths.length == 2) && (lengths[0] == 2) && (lengths[1] == 4))
    {
        writeln("Square");
        return true;
    }
    else
    {
        writeln("Not square");
        return false;
    }
}

// Parse the input and extract the four points
bool try_parse(char[] input, ref real points[4][2])
{
    const number = r"((?:\+|-)*\d+(?:.(?:\d+)*)*)";
    const coordinate = r"\(" ~ number ~ "," ~ number ~ r"\)";
    const pattern = coordinate ~ "," ~ coordinate ~ "," ~ coordinate ~ "," ~ coordinate;

    auto matcher = regex(pattern);
    auto parts = match(input, matcher);

    if (parts.empty())
    {
        writeln("Input does not match required pattern");
    }
    else
    {
        auto coords = parts.captures();

        if (coords.length() != 9)
        {
          writeln("Not enough points");
        }
        else
        {
            coords.popFront();
            for(size_t p = 0; p < points.length; p++)
            {
                points[p][0] = to!real(coords[p*2]);
                points[p][1] = to!real(coords[1+p*2]);
            }
            return true;
        }
    }
    return false;
}

// Process a line of input
bool check_squareness(char[] input)
{
    real points[4][2];

    if (try_parse(input, points))
        return perform_check(points);
    else
        return false;
}

void main()
{
    preamble();

    foreach(line; stdin.byLine)
    {
      char[] input = removechars(line, " ".dup);

      if (input == "")
        break;
      else
        check_squareness(input);
    }
}

unittest
{
    string tests[9][2] =
    [
        ["(0,0),(0,1),(1,1),(1,0)", "true"],    //normal square
        ["(0,0),(2,1),(3,-1),(1,-2)", "true"],  //not aligned square
        ["(0,0),(1,1),(0,1),(1,0)", "true"],    //different order of the points
        ["(0,0),(0,2),(3,2),(3,0)", "false"],   //rectangle
        ["(0,0),(3,4),(8,4),(5,0)", "false"],   //rhombus
        ["(0,0),(0,0),(1,1),(0,0)", "false"],   //three points are same
        ["(0,0),(0,0),(1,0),(0,1)", "false"],    //two points are same
        ["(0.5,0.5),(0.5,1.5),(1.5,1.5),(1.5,0.5)", "true"],
        ["(0.333,-0.333),(2.333,-0.333),(2.333,-2.333),(0.333,-2.333)", "true"]
    ];

    for(size_t test = 0; test < tests.length; test++)
    {
        write("Testing: " ~ tests[test][0] ~ " ");
        assert(check_squareness(tests[test][0].dup) == to!bool(tests[test][1]));
    }

    writeln("Tests done");
}
