#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*
 * Olimex WPC #42
 *
 * g++ -std=c++11 -Wall -fexceptions segments.cpp -o segments
 *
 */

const int max_segments = 100;

int problem[max_segments][4];
int solution[max_segments][4];
int used[max_segments];


int pro_count;
int sol_count;

void get_segments()
{
    cout << "Enter values for x1, y1, x2 and y2 separated by spaces:" << endl;
    cout << "Enter an empty line to finish: " << endl;

    pro_count = 0;
    sol_count = 0;
    string line;
    string number;
    int pos;

    getline(cin,line);
    while (!line.empty())
    {
      stringstream sstream(line);
      pos = 0;
      while (getline(sstream, number, ' '))
      {
        problem[pro_count][pos] = stoi(number);
        pos++;
      }
      used[pro_count] = 0;
      pro_count++;
      getline(cin,line);
    }
}

void print_problem()
{
    cout << endl << "Problem:" << endl;

    for (int i = 0 ; i < pro_count; i++)
        cout << "(" << problem[i][0]
             << "," << problem[i][1] << ") to "
             << "(" << problem[i][2]
             << "," << problem[i][3] << ")"
             << endl;

    cout << endl;
}


void print_solution()
{
    cout << endl << "Solution found:" << endl;

    for (int i = 0 ; i < sol_count; i++)
        cout << "(" << solution[i][0]
             << "," << solution[i][1] << ") to "
             << "(" << solution[i][2]
             << "," << solution[i][3] << ")"
             << endl;

    cout << endl;
}

int next(int level)
{
  level++;

  if (sol_count == pro_count)
    return 1;

  for (int i = 0; i < pro_count; i++)
  {
      if (used[i] == 0)
      {
        int flip = -1;

        if ((solution[sol_count-1][2] == problem[i][0]) &&
            (solution[sol_count-1][3] == problem[i][1]))
                    flip = 0;
        else if ((solution[sol_count-1][2] == problem[i][2]) &&
                 (solution[sol_count-1][3] == problem[i][3]))
                    flip = 1;

        if (flip >= 0)
        {
            if (flip == 0)
            {
                cout << string(level, ' ') << "Trying "
                     << "(" << problem[i][0] << "," << problem[i][1] << ") - "
                     << "(" << problem[i][2] << "," << problem[i][3] << ")" << endl;
                solution[sol_count][0] = problem[i][0];
                solution[sol_count][1] = problem[i][1];
                solution[sol_count][2] = problem[i][2];
                solution[sol_count][3] = problem[i][3];
            }
            else if (flip == 1)
            {
                cout << string(level, ' ') << "Trying "
                     << "(" << problem[i][2] << "," << problem[i][3] << ") - "
                     << "(" << problem[i][0] << "," << problem[i][1] << ")" << endl;
                solution[sol_count][0] = problem[i][2];
                solution[sol_count][1] = problem[i][3];
                solution[sol_count][2] = problem[i][0];
                solution[sol_count][3] = problem[i][1];
            }
            used[i] = 1;
            sol_count++;
            if (!next(level))
            {
                if (flip == 0)
                    cout << string(level, ' ')  << "Failed "
                         << "(" << problem[i][0] << "," << problem[i][1] << ") - "
                         << "(" << problem[i][2] << "," << problem[i][3] << ")" << endl;
                else
                    cout << string(level, ' ')  << "Failed "
                         << "(" << problem[i][2] << "," << problem[i][3] << ") - "
                         << "(" << problem[i][0] << "," << problem[i][1] << ")" << endl;
                used[i] = 0;
                sol_count--;
            }
            else
                return 1;
        }
      }
  }
  return 0;
}

void solve()
{
    for (int i = 0; i < pro_count; i++)
    {
        for (int flip = 0; flip <=1; flip++)
        {
            sol_count = 1;
            if (flip == 0)
            {
                solution[0][0] = problem[i][0];
                solution[0][1] = problem[i][1];
                solution[0][2] = problem[i][2];
                solution[0][3] = problem[i][3];
            }
            else
            {
                solution[0][0] = problem[i][2];
                solution[0][1] = problem[i][3];
                solution[0][2] = problem[i][0];
                solution[0][3] = problem[i][1];
            }
            for (int j = 0; j < pro_count; j++) used[j] = 0;
            used[i] = 1;

            cout << "Starting with "
                 << "(" << solution[0][0] << "," << solution[0][1] << ") - "
                 << "(" << solution[0][2] << "," << solution[0][3] << ")" << endl;

            if (next(0))
            {
                print_solution();
                return;
            }
            else
            {
                cout << "Failed with "
                 << "(" << solution[0][0] << "," << solution[0][1] << ") - "
                 << "(" << solution[0][2] << "," << solution[0][3] << ")" << endl << endl;
            }
        }
    }
    cout << "No solution found" << endl;
}

void fill(int p, int x1, int y1, int x2, int y2)
{
    problem[p][0] = x1;
    problem[p][1] = y1;
    problem[p][2] = x2;
    problem[p][3] = y2;
}

void test_pass_1()
{
    pro_count = 6;
    sol_count = 0;

    fill(0, 0, 0, 6, 0);
    fill(1, 6, 0, 6, 7);
    fill(2, 6, 7, 3, 10);
    fill(3, 3, 10, 0, 7);
    fill(4, 0, 7, 0, 0);
    fill(5, 0, 7, 6, 7);

    for(int i =0; i < pro_count; i++) used[i] = 0;
}

void test_pass_2()
{
    pro_count = 11;
    sol_count = 0;

    fill(0, 0, 7, 8, 7);
    fill(1, 0, 7, 4, 7);
    fill(2, 8, 7, 4, 7);
    fill(3, 8, 7, 12, 5);
    fill(4, 8, 7, 8, 0);
    fill(5, 12, 5, 12, 2);
    fill(6, 12, 2, 8, 0);
    fill(7, 8, 0, 4, 2);
    fill(8, 8, 0, 0, 0);
    fill(9, 4, 2, 0, 0);
    fill(10, 0, 7, 0, 0);

    for(int i =0; i < pro_count; i++) used[i] = 0;
}

void test_fail()
{
    pro_count = 8;
    sol_count = 0;

    fill(0, 0,  0, 6,  0);
    fill(1, 6,  0, 6,  7);
    fill(2, 6,  7, 3,  7);
    fill(3, 6,  7, 3, 10);
    fill(4, 3,  7, 3, 10);
    fill(5, 3,  7, 0,  7);
    fill(6, 3, 10, 0,  7);
    fill(7, 0,  7, 0,  0);

    for(int i =0; i < pro_count; i++) used[i] = 0;
}

int main()
{
    get_segments();
    //test_pass_1();
    //test_pass_2();
    //test_fail();
    print_problem();
    solve();
    return 0;
}
