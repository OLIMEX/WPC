/*
Problem:
	insert + and – in the equation below to make it right

	1 2 3 4 5 6 7 8 9 = 100

	like

	1 + 2 + 3 – 4 + 5 + 6 + 7 8 + 9 = 100
*/

#include <iostream>
#include <vector>

enum OpType_t { OP_EMPTY = 0, OP_PLUS, OP_MINUS, OP_MAX };

int main(int argc, char* argv[])
{
	std::vector<OpType_t> sln(8, OP_EMPTY);

	while (true)
	{
		// 1. compute solution
		int result = 0, temp = 1;
		char op = 1;
		for (size_t i = 2; i < 10; ++i)
		{
			if (sln[i - 2] == OP_PLUS)
			{
				result += temp * op;
				op = 1;
				temp = i;
			}
			else if (sln[i - 2] == OP_MINUS)
			{
				result += temp * op;
				op = -1;
				temp = i;
			}
			else // empty
			{
				temp = temp * 10 + i;
			}
			if (i == 9)
			{
				result += temp * op;
			}
		}
		
		// 2. print result
		if (result == 100)
		{
			std::cout << 1;
			for (size_t i = 2; i < 10; ++i)
			{
				switch (sln[i - 2])
				{
				case OP_PLUS:
					std::cout << " + ";
					break;
				case OP_MINUS:
					std::cout << " - ";
					break;
				}
				std::cout << i;
			}
			std::cout << " = " << result << std::endl;
		}

		// 3. iterate next solution
		bool flag = false;
		for (auto it = sln.rbegin(); it != sln.rend(); ++it)
		{
			int pos = *it + flag;
			if (it == sln.rbegin()) pos++;
			flag = pos >= OP_MAX;
			if (flag && it != sln.rend()) pos %= OP_MAX;

			*it = static_cast<OpType_t>(pos);
		}
		
		// 4. iteration ended
		if (flag &&	sln[0] == OP_EMPTY)
		{
			break;
		}
	}

	return 0;
}
