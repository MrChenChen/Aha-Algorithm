#include "stdafx.h"
#include "Aha-Algorithm.h"
#include <list>

using namespace std;


#ifdef UNICODE
#define _T(x) L ## x
#define STRING LPCWSTR
#else
#define _T(x) x
#define STRING LPCTSTR
#endif


bool RequireAdmin(STRING path)
{
	SHELLEXECUTEINFO info = { sizeof(SHELLEXECUTEINFO) };
	info.nShow = SW_NORMAL;
	info.lpFile = path;
	info.lpVerb = _T("runas");

	return ShellExecuteEx(&info);
}


static map<char, int> map_char_int = {
	{ '1', 1 },
	{ '2', 2 },
	{ '3', 3 },
	{ '4', 4 },
	{ '5', 5 },
	{ '6', 6 },
	{ '7', 7 },
	{ '8', 8 },
	{ '9', 9 },
};


static size_t GetNumberLen(long long num)
{
	return int(log(num) / log(10)) + 1;
}



#pragma region Random
//��ȡ�����
//type = 1  int;
//type = -1 double;


template<class T>
T* GetRandomArray(size_t len, T _min, T _max)
{

	if (typeid(int) == typeid(T))
	{
		uniform_int_distribution<> u(min(_min, _max), max(_min, _max));

		default_random_engine e;

		e.seed(Stopwatch::GetSystemTime());

		auto temp = new  T[len];

		for (size_t i = 0; i < len; i++)
		{
			temp[i] = u(e);

			//OUT(temp[i]);
		}

		return temp;

	}
	else if (typeid(double) == typeid(T))
	{
		uniform_real_distribution<> u(min(_min, _max), max(_min, _max));

		default_random_engine e;

		e.seed(Stopwatch::GetSystemTime());

		auto temp = new  T[len];

		for (size_t i = 0; i < len; i++)
		{
			temp[i] = u(e);
		}

		return temp;
	}

	return nullptr;

}

#pragma endregion Random



#pragma region Bucket_Sort 
//Ͱ����   O(m+n)
//Max value is related to your Memory and Platform!!! 
//This Must Be Unsigned Integer Array

//1-10      ��   0.002 ~ 0.005 ms
//1-100     :    0.18  ~ 0.25  ms
//1-1000    :    0.02  ~ 0.03  ms
//1-10000   :    About   0.15  ms
//1-100000  :    About      2  ms


//if Lenght ==  10000000  : 65 ms

const unsigned int Aha_Max(const int *temp, const size_t len, bool ascending = true)
{
	int t_max = 0;

	for (size_t i = 0; i < len; i++)
	{
		t_max = max(temp[i], t_max);
	}

	return t_max;
}


int* Bucket_Sort(int *temp, const size_t len, bool ascending = true)
{
	auto t_Max_len = Aha_Max(temp, len) + 1;

	auto t_Max = new int[t_Max_len];  //This code is very important

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

#pragma endregion Bucket_Sort



#pragma region Bubble_Sort
//ð������  O(pow(N,2))

//This Can be Signed Integer Array or Double Array

//0-10       About 0.0028    ms
//0-100      About 0.200     ms
//0-1000     About 20        ms
//0-10000    About 2050-2070 ms

//if Length > 100000 It will be slow incredibly!!!;

int* Bubble_Sort(int *temp, const size_t len, bool ascending = true)
{
	for (size_t i = 0; i < len - 1; i++)
	{
		for (size_t j = 1; j < len - i; j++)
		{
			if (ascending)
			{
				if (temp[j - 1] > temp[j])
				{
					swap(temp[j - 1], temp[j]);
				}
			}
			else
			{
				if (temp[j - 1] < temp[j])
				{
					swap(temp[j - 1], temp[j]);
				}
			}

		}
	}

	return temp;
}


#pragma endregion Bubble_Sort



#pragma region Quick_Sort
//����     O(NlogN)
//This Can be Signed Integer Array or Double Array

//0-10       About  0.0015   ms
//0-100       0.015 - 0.02   ms
//0-1000        0.2 - 0.3    ms
//0-10000         3 -   4    ms
//0-100000     About   40    ms
//0-1000000    About  460    ms       

void Quick_Sort(int* array, int left, int right, bool ascendind = true)
{
	int base;

	int i, j;

	if (left > right) return;

	base = array[left];

	i = left;
	j = right;

	while (i != j)
	{

		if (ascendind)
		{
			while (array[j] >= base && i < j)
			{
				j--;
			}

			while (array[i] <= base && i < j)
			{
				i++;
			}
		}
		else
		{
			while (array[j] <= base && i < j)
			{
				j--;
			}

			while (array[i] >= base && i < j)
			{
				i++;
			}
		}


		if (i < j)
		{
			swap(array[i], array[j]);
		}
	}

	array[left] = array[i];

	array[i] = base;


	Quick_Sort(array, left, i - 1, ascendind);

	Quick_Sort(array, i + 1, right, ascendind);

}

#pragma endregion Quick_Sort



#pragma region Match Number


size_t GetMatchNumberCount(size_t num)
{
	int f[10] = { 6,2,5,5,4,5,6,3,7,6 };

	char str[100];

	sprintf_s(str, "%d", num);



	size_t t = 0;

	int k = 0;

	while (str[k] != '\0')
	{

		t += f[map_char_int[str[k]]];
		k++;
	}

	return t;

}


#pragma endregion Match Number



#pragma region Full Array

#pragma region ���� ȫ����

bool HasAllNum(unsigned int n)
{
	int len = GetNumberLen(n);

	auto base = new int[len];

	for (size_t i = 0; i < len; i++)
	{
		base[i] = 0;
	}

	int temp = n;

	for (size_t i = 0; i < len; i++)
	{
		auto t = temp % 10;

		if (t - 1 >= len || t - 1 < 0)
		{
			delete[] base;

			return false;
		}

		base[t - 1]++;

		temp /= 10;
	}

	for (size_t i = 0; i < len; i++)
	{
		if (base[i] != 1)
		{
			delete[] base;

			return false;
		}
	}

	delete[] base;

	return true;
}


long Get_1_N_Max(int n)
{
	auto base = new int[n];

	for (size_t i = 0; i < n; i++)
	{
		base[i] = i + 1;
	}

	long max = 0;

	for (size_t i = n - 1; i > 0; i--)
	{
		max += base[i] * pow(10, i);
	}

	delete[] base;

	return max + 1;
}


long Get_1_N_Min(int n)
{
	auto base = new int[n];

	for (size_t i = 0; i < n; i++)
	{
		base[i] = i + 1;
	}

	long min = 0;

	for (size_t i = 0; i < n; i++)
	{
		min += base[i] * pow(10, n - i - 1);
	}

	delete[] base;

	return min;
}


void ShowFullArray(int n)
{

	long min = Get_1_N_Min(n);
	long max = Get_1_N_Max(n);

	for (long i = min; i <= max; i++)
	{
		if (HasAllNum(i))
		{
			OUT(i);
		}
	}


}

#pragma endregion ���� ȫ����


// Depth - First - Search  // ���ǵ�ǰ��N��ʱ�������Ȼ��ݹ��N+1
namespace Depth_First_Search {

	int a[10], box[10], n = 7;

	void dfs(int step)  //step ��ʾ����վ�� �Ǹ� ������ǰ��׼��Ҫ�Ŷ�����ȥ�ˣ�����Ҫ�õ�
	{

		if (step == n + 1)
		{
			for (size_t i = 1; i <= n; i++)
			{
				cout << (a[i]);
			}

			cout << endl;

			return;
		}


		for (size_t i = 1; i <= n; i++)
		{
			if (box[i] == 0)  //box[i]==0;˵���� i ������û�Ŷ���
			{
				a[step] = i;

				box[i] = 1;

				dfs(step + 1);

				box[i] = 0;

			}

		}
		return;
	}

	void Test_DFS()
	{



		dfs(1);

	}


}



#pragma endregion Full Array







int main()
{
	//list<int> m_list = { 1,2,3,4,5,6,7,8,9,1 };

	//m_list.remove(1);


	////std::initializer_list<int> _Ilist = { 1,2,4,5,1 };



	//for each (auto item in m_list)
	//{
	//	OUT(item);
	//}

	Depth_First_Search::Test_DFS();


	system("Pause");

	return 0;

}

