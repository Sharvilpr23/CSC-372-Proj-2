#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <limits.h>

using namespace std;

void minBoardCost(vector<int> &v, int w)
{
	int currCost = 0;
    	vector<int> dp;
    	dp.resize(v.size() + 1);
    	dp[v.size()] = 0;
  	dp[v.size() - 1] = 0;
	int lastRow = v[v.size() - 1];
	
	/*
	for(end = v.size() - 2; end >= 0; end--)
	{
		lastRow += v[end];
		if(lastRow <= w)
			dp[end] = 0;	
	}
	*/	

	for (int i = v.size()- 2; i >= 0; i--)
    	{
        	int rowLen = v[i];
        	int rowCost = dp[i + 1] + int(pow((w - rowLen), 3));
        	for (int j = i + 1; j < v.size(); j++)
        	{
            		rowLen += v[j];
            		if (rowLen > w) currCost = 1000000;
            		else currCost = dp[j + 1] + int(pow((w - rowLen), 3));
            		
			rowCost = min(rowCost, currCost);
        	}
        	dp[i] = rowCost;
    	}
	cout << dp[0] << endl;
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

