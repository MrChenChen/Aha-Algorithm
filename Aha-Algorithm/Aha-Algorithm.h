#pragma once

//list  should sava last and next both point

template<typename T>
class MyList
{

	struct MyStruct
	{
		T data;

		MyStruct *next = nullptr;

		MyStruct *previous = nullptr;

	};



public:


	void Add(T _i)
	{
		if (m_mark == nullptr)
		{
			m_mark = new MyStruct;

			auto temp = new MyStruct;

			temp->data = _i;

			m_mark->next = temp;

			m_mark->previous = temp;


			m_size++;
		}
		else if (m_size > 0)
		{

			auto temp = new MyStruct;

			temp->data = _i;

			m_mark->next->next = temp;

			temp->previous = m_mark->next;

			m_mark->next = temp;

			m_size++;

		}

	}


	T operator[](unsigned n)
	{
		auto s = m_mark->previous;

		for (size_t i = 0; i < n; i++)
		{
			s = s->next;
		}

		return s->data;
	}


	void RemoveAt(size_t n)
	{
		auto s = GetItemAt(n);

		if (s->previous != nullptr && s->next != nullptr)
		{
			s->previous->next = s->next;

			s->next->previous = s->previous;

		}
		else if (s->previous == nullptr && s->next != nullptr)
		{
			m_mark->previous = s->next;

			s->next->previous = nullptr;
		}
		else if (s->next == nullptr && s->previous != nullptr)
		{
			m_mark->next = s->previous;

			s->previous->next = nullptr;
		}

		m_size--;

		delete s;
	}


	MyStruct* GetItemAt(size_t n)
	{
		if (n >= m_size)
		{
			throw out_of_range("List GetItemAt Out Of Range");
		}

		auto s = m_mark->previous;

		for (size_t i = 0; i < n; i++)
		{
			s = s->next;
		}

		return s;
	}


	size_t size()
	{
		return m_size;
	}

private:

	MyStruct *m_mark = nullptr;

	size_t m_size = 0;

};
