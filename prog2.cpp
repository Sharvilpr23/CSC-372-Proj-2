#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits.h>

using namespace std;

#define INFIN INT_MAX //Infinity

/*
	Calculates the sum of the widths of the announcements on a particular row
	
	Indexing: 0-based
*/
int calculate_board_cost(vector<int> &v, int width, int start, int end)
{
	int sum = v[start];
	while (start < end)
	{
		start += 1;
		sum += v[start];
	}
	return sum;
}

/*
	Creates a split vector where split[i] is the start and split[i + 1] is 
	where the index of the last announcement on the row.

	Indexing: 0-based
*/
vector<int> find_splits(vector<int> &jump, int n)
{
	vector<int> split;
	int i = 0;
	while (i < n)
	{
		split.push_back(i + 1);
		split.push_back(jump[i] + 1);
		i = jump[i] + 1;
	}
	return split;
}

/*
	Prints the minimum boardcost and tthen lists the splits with their 
	corresponding costs.

	Indexing: 0-based
*/
void print_results(vector<int> &v, int width, vector<int> &split, int board_cost)
{
	cout << "Board cost: " << board_cost << "\n";
	for (int i = 0; i < split.size(); i += 2)
	{
		cout << "(" << split[i] << ", " << split[i + 1] << ") --> " << calculate_board_cost(v, width, split[i] - 1, split[i + 1] - 1) << "\n";
	}
	cout << "\n";
}

/*
	Generates a dp vector which stores the most optimal solution for each of 
	the announcements

	Indexing: 0-based
*/
void minBoardCost(vector<int> &v, int w, int n)
{
	int currCost = 0;
	vector<int> dp;
	vector<int> jump;  //Tracks where to and how much to jump
	vector<int> split; //Stores the

	dp.resize(n + 1);
	jump.resize(n);

	dp[n] = 0;
	dp[n - 1] = 0;
	jump[n - 1] = n - 1;

	for (int i = n - 2; i >= 0; i--)
	{
		int rowLen = 0;
		int rowCost = INFIN;
		for (int j = i; j < n; j++)
		{
			rowLen += v[j];
			if (rowLen > w)
				break;
			else if (j == n - 1)
				currCost = 0; //GRADING UPDATE
			else
				currCost = dp[j + 1] + int(pow((w - rowLen), 3)); //GRADING: REUSE
			if (rowCost > currCost)
			{
				rowCost = min(rowCost, currCost); //GRADING: UPDATE
				jump[i] = j;
			}
		}
		dp[i] = rowCost; //GRADING: UPDATE
	}
	split = find_splits(jump, n);
	print_results(v, w, split, dp[0]);
}

int main()
{
	vector<int> v;
	int w = 6;
	int n;
	int a;

	// Row width, number of announcements
	cin >> w >> n;

	int loop_counter = n;
	while (loop_counter--)
	{
		cin >> a;
		v.push_back(a);
	}

	minBoardCost(v, w, n);

	return 0;
}
