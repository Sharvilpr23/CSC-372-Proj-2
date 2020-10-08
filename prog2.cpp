#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits.h>

using namespace std;

int calculate_board_cost(vector<int> &v, int width, int start, int end)
{
	int cost = v[start];
	while (start < end)
	{
		start += 1;
		cost += v[start];
	}
	return cost;
}

vector<int> find_splits(vector<int> &row_change, int n)
{
	vector<int> split;
	int i = 0;
	while (i < n)
	{
		split.push_back(i + 1);
		split.push_back(row_change[i] + 1);
		i = row_change[i] + 1;
	}
	return split;
}

void print_results(vector<int> &v, int width, vector<int> &split, int board_cost)
{
	cout << "Board cost: " << board_cost << "\n";
	for (int i = 0; i < split.size(); i += 2)
	{
		cout << "(" << split[i] << ", " << split[i + 1] << ") --> " << calculate_board_cost(v, width, split[i] - 1, split[i + 1] - 1) << "\n";
	}
	cout << "\n";
}

void minBoardCost(vector<int> &v, int w)
{
	int n = v.size();
	int currCost = 0;
	vector<int> dp;
	vector<int> row_change;
	vector<int> split;
	dp.resize(v.size() + 1);
	row_change.resize(v.size() + 1);
	dp[v.size()] = 0;
	dp[v.size() - 1] = 0;
	row_change[v.size() - 1] = v.size() - 1;

	for (int i = v.size() - 2; i >= 0; i--)
	{
		int rowLen = 0;
		int rowCost = INT_MAX;
		for (int j = i; j < v.size(); j++)
		{
			rowLen += v[j];
			if (rowLen > w)
				break;
			else if (j == n - 1)
				currCost = 0;
			else
				currCost = dp[j + 1] + int(pow((w - rowLen), 3));
			if (rowCost > currCost)
			{
				rowCost = min(rowCost, currCost);
				row_change[i] = j;
			}
		}
		dp[i] = rowCost;
	}
	split = find_splits(row_change, n);
	print_results(v, w, split, dp[0]);
}

int main()
{
	vector<int> v;
	int w = 6;
	int n;
	int a;

	cin >> w >> n;

	while (n--)
	{
		cin >> a;
		v.push_back(a);
	}

	minBoardCost(v, w);

	return 0;
}
