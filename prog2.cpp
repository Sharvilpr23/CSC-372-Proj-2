#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits.h>

using namespace std;

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
	//for (int i = 0; i < dp.size(); i++)
	//	cout << dp[i] << " ";
	//cout << endl;
	int i = 0;
	while (i < n)
	{
		split.push_back(i + 1);
		split.push_back(row_change[i] + 1);
		i = row_change[i] + 1;
	}
	for (i = 0; i < split.size(); i++)
	{
		cout << split[i] << " ";
	}
	cout << endl;
	//return split;
	//cout << dp[0] << endl;
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
