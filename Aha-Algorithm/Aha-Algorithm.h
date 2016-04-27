#pragma once


class MyList
{

	struct MyStruct
	{
		int data;

		MyStruct *ptr = nullptr;

	};

public:

	MyList()
	{

	}

	~MyList()
	{

	}

	void Add(int _i)
	{
		if (m_start == nullptr && m_end == nullptr)
		{
			auto t = static_cast<MyStruct*>(malloc(sizeof(MyStruct)));

			t->data = _i;

			m_start = t;

			m_end = t;

		}
		if (m_start != nullptr && m_end != nullptr)
		{
			auto t = static_cast<MyStruct*>(malloc(sizeof(MyStruct)));

			t->data = _i;

			m_end->ptr = t;

			m_end = t;
		}

	}

	MyStruct* Start()
	{
		return m_start;
	}

	MyStruct* end()
	{
		return m_end;
	}

	size_t size()
	{
		size_t t = 0;

		if (m_start->ptr == nullptr)
		{
			return 0;
		}

		auto s = m_start->ptr;

		while (s != nullptr)
		{
			t++;
			s = s->ptr;
		}

		return t;
	}

private:

	MyStruct *m_start = nullptr;

	MyStruct *m_end = nullptr;

};
