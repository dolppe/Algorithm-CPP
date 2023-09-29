#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

int N, K;
pair<int, int> inputValue[105];

// 0은 무게, 1은 가치
// D[i] i 번째 보석을 선택했을 때의 값
int W[105];
int V[105];

bool compare(pair<int, int> a, pair<int, int> b)
{
	if (a.first > b.first)
		return true;
	else if (a.first < b.first)
		return false;
	else
	{
		return a.second > b.second;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;

	for (int i = 1; i <= N; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		inputValue[i] = { temp1, temp2 };
	}

	sort(inputValue + 1, inputValue + N + 1, compare);

	for (int i = 1; i <= N; i++)
	{
		int maxValue = 0;
		int maxIndex = 0;
		for (int j = 1; j <= i; j++)
		{
			// 이전에 담은 주머니들 중 현재 i도 넣을수 있는 주머니
			if (W[j] + inputValue[i].first <= K)
			{
				int tempValue = V[j] + inputValue[i].second;
				if (tempValue > maxValue)
				{
					maxValue = tempValue;
					maxIndex = j;
				}
			}
		}
		if (maxValue != 0)
		{
			W[i] = W[maxIndex] + inputValue[i].first;
			V[i] = V[maxIndex] + inputValue[i].second;
		}
		else
		{
			W[i] = inputValue[i].first;
			V[i] = inputValue[i].second;
		}

	}
	cout << *max_element(V + 1, V + N + 1);




}