#pragma once


template<typename T>
class MyList
{
public:

	typedef long long __size_t;

	struct MyStruct
	{
		T data;

		MyStruct *next = nullptr;

		MyStruct *previous = nullptr;

		MyStruct & operator=(T _val)
		{
			data = _val;

			return *this;
		}

		bool operator<(MyStruct & _mystruct)
		{
			return data < _mystruct.data;
		}

		bool operator>(MyStruct & _mystruct)
		{
			return data > _mystruct.data;
		}

		bool operator<=(MyStruct & _mystruct)
		{
			return data <= _mystruct.data;
		}

		bool operator>=(MyStruct & _mystruct)
		{
			return data >= _mystruct.data;
		}

		bool operator==(MyStruct & _mystruct)
		{
			return data == _mystruct.data;
		}


	};


	class Iterator
	{

	public:

		MyStruct* m_data;

		__size_t m_index = 0;

		Iterator() = default;

		Iterator(MyStruct* p, __size_t _index) : m_data(p), m_index(_index)
		{
		}


#pragma region 重载运算符

		Iterator operator++()
		{
			m_index++;
			m_data = m_data->next;
			return *this;
		}

		Iterator operator--()
		{
			m_index--;
			m_data = m_data->previous;
			return *this;
		}

		Iterator  operator++(int)
		{
			m_index++;
			m_data = m_data->next;
			return *this;
		}

		Iterator operator--(int)
		{
			m_index--;
			m_data = m_data->previous;
			return *this;
		}

		Iterator operator+(__size_t _val)
		{
			for (__size_t i = 0; i < _val; i++)
			{
				++(*this);
			}

			return *this;
		}

		Iterator operator-(int _val)
		{
			for (__size_t i = 0; i < _val; i++)
			{
				--(*this);
			}
			return *this;
		}

		T operator*()
		{
			return m_data->data;
		}

		MyStruct* operator->()
		{
			return m_data;
		}

		bool operator!=(Iterator i)
		{
			return i.m_index != m_index;
		}

		bool operator<(Iterator & i)
		{
			return m_index < i.m_index;
		}

		bool operator>(Iterator & i)
		{
			return m_index > i.m_index;
		}

		bool operator<=(Iterator & i)
		{
			return m_index <= i.m_index;
		}

		bool operator>=(Iterator & i)
		{
			return m_index >= i.m_index;
		}

#pragma endregion 重载运算符


	};

public:


#pragma region 构造函数

	MyList() = default;


	MyList(std::initializer_list<T> _Ilist)
	{
		Clear();

		for each (const T & item in _Ilist)
		{
			Add(item);
		}

	}


	MyList(const MyList<T> &)
	{
		Clear();

		for each (auto item in _list)
		{
			Add(item);
		}
	}


	MyList(MyList<T> && _list)
		:m_mark(_list.m_mark), m_size(_list.m_size)
	{
		_list.m_size = 0;
		_list.m_mark->previous = _list.m_mark->next = nullptr;
	}


	MyList<T> & operator=(MyList<T> && _list) noexcept
	{
		if (&_list != this)
		{
			Clear();

			m_mark = _list.m_mark;

			m_size = _list.m_size;


			_list.m_mark = nullptr;

		}

		return *this;
	}


	MyList<T> & operator=(const MyList<T> & _list)
	{
		Clear();

		for each (T item in _list)
		{
			Add(item);
		}
	}


#pragma endregion 构造函数


	~MyList()
	{
		Clear();
	}


	void Add(const T & _i)
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


	T & operator[](__size_t n)
	{
		auto s = m_mark->previous;

		for (__size_t i = 0; i < n; i++)
		{
			s = s->next;
		}

		return s->data;
	}


	void Insert(__size_t i, const T & _val)
	{
		if (i > m_size)
		{
			throw out_of_range("List GetItemAt Out Of Range");
		}
		else if (i == 0)
		{
			auto temp = new MyStruct();

			temp->data = _val;

			m_mark->previous->previous = temp;

			temp->next = m_mark->previous;

			m_mark->previous = temp;

			m_size++;

			return;
		}
		else if (m_size == i)
		{
			Add(_val);

			return;
		}
		else
		{
			auto temp = new MyStruct();

			temp->data = _val;

			auto mid_ptr = GetItemAt(i);

			mid_ptr->previous->next = temp;

			temp->previous = mid_ptr->previous;

			temp->next = mid_ptr;

			mid_ptr->previous = temp;

			m_size++;

			return;
		}

	}


	void RemoveAt(__size_t n)
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


	void Clear()
	{
		if (m_mark)
		{
			auto s = m_mark->previous;

			while (s != nullptr)
			{
				auto _next = s->next;

				delete s;

				s = _next;
			}

			delete m_mark;
		}

	}


	void Empty()
	{
		return m_size == 0;
	}


	void Sort(Iterator _begin, Iterator _end, bool ascendind = true)
	{
		//cout << _begin.m_index << " , " << _end.m_index << endl;

		if (_begin.m_index >= _end.m_index) return;   //Must Be First Row!!!

		auto base = _begin->data;

		auto i = _begin;

		auto j = _end;

		while (i.m_index != j.m_index)
		{

			if (ascendind)
			{
				while (j->data >= base && i.m_index < j.m_index)
				{
					j--;
				}

				while (i->data <= base && i.m_index < j.m_index)
				{
					i++;
				}
			}
			else
			{
				while (j->data <= base && i.m_index < j.m_index)
				{
					j--;
				}

				while (i->data >= base && i.m_index < j.m_index)
				{
					i++;
				}

			}

			if (i < j)
			{
				swap(i->data, j->data);
			}

		}


		swap(i->data, _begin->data);


		Sort(_begin, i, ascendind);

		Sort(i + 1, _end, ascendind);

	}


	MyStruct & GetItemAt(__size_t n)
	{
		if (n >= m_size)
		{
			throw out_of_range("List GetItemAt Out Of Range");
		}

		auto s = m_mark->previous;

		for (__size_t i = 0; i < n; i++)
		{
			s = s->next;
		}

		return *s;
	}


	__size_t size()
	{
		return m_size;
	}


	Iterator begin()
	{
		return Iterator(m_mark->previous, 0);
	}


	Iterator end()
	{
		return Iterator(m_mark->next, m_size - 1);
	}


private:

	MyStruct *m_mark = nullptr;

	__size_t m_size = 0;

};


