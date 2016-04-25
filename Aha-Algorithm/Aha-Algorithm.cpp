#include "stdafx.h"
#include "Aha-Algorithm.h"
using namespace std;


//max value 370000000
const unsigned int Aha_Max(const int *temp, const size_t len, bool ascending = true)
{
	int t_max = 0;

	for (size_t i = 0; i < len; i++)
	{
		t_max = max(temp[i], t_max);
	}

	return t_max;
}


int* Aha_Sort(int *temp, const size_t len, bool ascending = true)
{
	auto t_Max_len = Aha_Max(temp, len) + 1;

	auto t_Max = new int[t_Max_len];

	memset(t_Max, 0, t_Max_len * sizeof(decltype(t_Max[0])));

	for (size_t i = 0; i < len; i++)
	{
		t_Max[temp[i]]++;
	}

	if (ascending)
	{
		int x = 0;

		for (size_t i = 0; i < t_Max_len; i++)
		{
			if (t_Max[i] != 0)
			{
				for (size_t j = 0; j < t_Max[i]; j++)
				{
					temp[x] = i;
					x++;
				}
			}
		}
	}
	else
	{
		int x = len - 1;

		for (size_t i = 0; i < t_Max_len; i++)
		{
			if (t_Max[i] != 0)
			{
				for (size_t j = 0; j < t_Max[i]; j++)
				{
					temp[x] = i;
					x--;
				}
			}
		}
	}


	delete[] t_Max;

	return temp;
}



int main()
{
	int a[] = { 5,8,2,5,3,0,92,74,52,370000000 };


	Stopwatch sw;
	sw.Start();

	auto r = Aha_Sort(a, LEN(a), false);

	for (size_t i = 0; i < LEN(a); i++)
	{
		OUT(r[i]);
	}

	OUT("Time: " << sw.Stop() << " ms");


	system("Pause");

	return 0;

}

