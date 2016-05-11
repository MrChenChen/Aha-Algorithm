#pragma once
#include <list>
#include <functional>

template<typename T>
class MyList
{
private:

	typedef size_t __size_t;

	typedef std::function<bool(T, T)> __Fun_Less_Equal;


	struct _List_Element
	{
		T data;

		_List_Element *next = nullptr;

		_List_Element *previous = nullptr;

		_List_Element & operator=(T _val)
		{
			data = _val;

			return *this;
		}

		bool operator<(_List_Element & _mystruct)
		{
			return data < _mystruct.data;
		}

		bool operator>(_List_Element & _mystruct)
		{
			return data > _mystruct.data;
		}

		bool operator<=(_List_Element & _mystruct)
		{
			return data <= _mystruct.data;
		}

		bool operator>=(_List_Element & _mystruct)
		{
			return data >= _mystruct.data;
		}

		bool operator==(_List_Element & _mystruct)
		{
			return data == _mystruct.data;
		}


	};


	//主要用在排序 和 for each
	struct Iterator
	{

		_List_Element* m_data;

		__size_t m_index = 0;

		Iterator() = default;

		Iterator(_List_Element* p, __size_t _index) : m_data(p), m_index(_index)
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

		_List_Element* operator->()
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


	MyList(const MyList<T> & _list)
	{
		Clear();

		auto _size = _list.m_size;

		auto _begin = _list.m_mark->previous;

		for (size_t i = 0; i < _size; i++)
		{
			Add(_begin->data);
			_begin = _begin->next;
		}

	}


	MyList(const std::list<T> & _list)
	{
		Clear();

		for each (auto & item in _list)
		{
			Add(item);
		}
	}




	MyList(MyList<T> && _list)
		:m_size(_list.m_size)
	{
		Clear();
		m_mark = new _List_Element();
		m_mark->data = _list.m_mark->data;
		m_mark->previous = _list.m_mark->previous;
		m_mark->next = _list.m_mark->next;

		_list.m_size = 0;
		_list.m_mark->previous = nullptr;
		_list.m_mark->next = nullptr;
		_list.m_mark = nullptr;
	}



#pragma endregion 构造函数


#pragma region 重载运算符

	T & operator[](__size_t n)
	{
		auto s = m_mark->previous;

		for (__size_t i = 0; i < n; i++)
		{
			s = s->next;
		}

		return s->data;
	}


	MyList & operator+=(std::initializer_list<T> _list)
	{
		for each (auto & item in _list)
		{
			Add(item);
		}

		return *this;
	}


	MyList<T> & operator=(const std::list<T> & _list)
	{
		Clear();

		for each (auto & item in _list)
		{
			Add(item);
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

		return *this;
	}


	MyList<T> & operator=(MyList<T> && _list) noexcept
	{
		if (&_list != this)
		{
			Clear();

			m_mark = _list.m_mark;

			m_size = _list.m_size;

			_list.m_mark->previous = nullptr;
			_list.m_mark->next = nullptr;
			_list.m_mark = nullptr;

		}

		return *this;
	}


	MyList & operator+=(const MyList & _list)
	{

		auto _size = _list.m_size;

		auto _iterator = _list.m_mark->previous;

		for (size_t i = 0; i < _size; i++)
		{
			Add(_iterator->data);
			_iterator = _iterator->next;
		}

		m_size += _size;

		return *this;
	}


	MyList & operator+=(MyList && _val)
	{
		m_mark->next->next = _val.m_mark->previous;
		_val.m_mark->previous = m_mark->next;
		m_mark->next = _val.m_mark->next;

		m_size += _val.m_size;

		_val.m_mark->next = nullptr;
		_val.m_mark->previous = nullptr;
		_val.m_mark = nullptr;

		return *this;
	}


#pragma endregion 重载运算符


	~MyList()
	{
		Clear();
	}


	void Add(const T & _i)
	{
		if (m_mark == nullptr)
		{
			m_mark = new _List_Element;

			auto temp = new _List_Element;

			temp->data = _i;

			m_mark->next = temp;

			m_mark->previous = temp;

			m_size++;
		}
		else if (m_size > 0)
		{

			auto temp = new _List_Element;

			temp->data = _i;

			m_mark->next->next = temp;

			temp->previous = m_mark->next;

			m_mark->next = temp;

			m_size++;

		}

	}


	void Insert(__size_t i, const T & _val)
	{
		if (i > m_size)
		{
			throw out_of_range("List GetItemAt Out Of Range");
			return;
		}
		else if (i == 0)
		{
			auto temp = new _List_Element();

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
			auto temp = new _List_Element();

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
		if (n > m_size)
		{
			throw out_of_range("Out of Range");

			return;
		}

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

			m_mark = nullptr;
		}

	}


	bool Empty()
	{
		return m_size == 0;
	}


	_List_Element & GetItemAt(__size_t n)
	{
		if (n >= m_size)
		{
			throw out_of_range("List GetItemAt Out Of Range");
			return;
		}

		auto s = m_mark->previous;

		for (__size_t i = 0; i < n; i++)
		{
			s = s->next;
		}

		return *s;
	}


	__size_t size() const noexcept
	{
		return m_size;
	}


	Iterator begin() const
	{
		return Iterator(m_mark->previous, 0);
	}


	Iterator last() const
	{
		return Iterator(m_mark->next, m_size - 1);
	}


	Iterator end() const
	{
		return Iterator(m_mark->previous, m_size);
	}


	long IndexOf(const T & _val)
	{
		int i = 0;

		for each (auto item in *this)
		{
			if (item == _val) return i;

			i++;
		}

		return -1;
	}


	bool Contain(const T & _val)
	{
		for each (auto item in *this)
		{
			if (item == _val) return true;
		}

		return false;
	}


	void Sort(bool ascendind = true)
	{
		m_less_equal = [&](T _t1, T _t2) {return _t1 <= _t2; };
		__Sort_Compare(begin(), Iterator(m_mark->next, m_size - 1), ascendind);
	}


	void Sort(__Fun_Less_Equal _fun_less_equal, bool ascendind = true)
	{
		if (m_size < 2) return;

		m_less_equal = _fun_less_equal;
		__Sort_Compare(begin(), Iterator(m_mark->next, m_size - 1), ascendind);
		m_less_equal = nullptr;
	}


	void Reverse()
	{
		if (m_size < 2) return;

		auto _begin = begin();
		auto _last = last();

		size_t _size = m_size / 2;

		for (size_t i = 0; i < _size; i++)
		{
			auto temp = _last.m_data->data;

			_last.m_data->data = _begin.m_data->data;

			_begin.m_data->data = temp;

			_begin++;

			_last--;
		}

	}


	std::list<T> ToStdList()
	{
		if (empty())
		{
			return list<T>();
		}

		list<T> temp;

		auto _begin = m_mark->previous;

		for (size_t i = 0; i < m_size; i++)
		{
			temp.push_back(_begin->data);
			_begin = _begin->next;
		}

		return temp;
	}


	T* ToArray()
	{
		auto arr = new T[m_size];

		size_t i = 0;

		for each (auto item in *this)
		{
			arr[i] = item;

			i++;
		}

		return arr;
	}


private:

	void __Sort_Compare(Iterator _begin, Iterator _end, bool ascendind = true)
	{

		if (_begin.m_index >= _end.m_index) return;   //Must Be First Row!!!

		auto base = _begin->data;

		Iterator i = _begin;

		Iterator j = _end;

		while (i.m_index != j.m_index)
		{
			if (ascendind)
			{
				while (m_less_equal(base, j->data) && i.m_index < j.m_index)
				{
					j--;
				}

				while (m_less_equal(i->data, base) && i.m_index < j.m_index)
				{
					i++;
				}
			}
			else if (i.m_index < j.m_index)
			{
				while (m_less_equal(j->data, base) && i.m_index < j.m_index)
				{
					j--;
				}

				while (m_less_equal(base, i->data) && i.m_index < j.m_index)
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

		__Sort_Compare(_begin, i, ascendind);

		__Sort_Compare(++i, _end, ascendind);

	}

	_List_Element *m_mark = nullptr;

	__size_t m_size = 0;

	__Fun_Less_Equal m_less_equal = nullptr;

};



template<typename T>
class MyVector
{
private:

	typedef size_t __size_t;

	typedef std::function<bool(T, T)> __Fun_Less_Equal;

	//主要用在排序 和 for each
	struct Iterator
	{
		T* m_data = nullptr;


		Iterator() = default;

		Iterator(T* p, __size_t _index)
		{
			m_data = p + _index;
		}

		Iterator & operator++()
		{
			++m_data;
			return *this;
		}

		Iterator & operator++(int)
		{
			++m_data;
			return *this;
		}

		Iterator & operator--()
		{
			--m_data;
			return *this;
		}

		Iterator & operator--(int)
		{
			--m_data;
			return *this;
		}

		bool operator!=(const Iterator & _val)
		{
			return m_data != _val.m_data;
		}

		bool operator==(const Iterator & _val)
		{
			return m_data == _val.m_data;
		}

		T operator*()
		{
			return *m_data;
		}

		Iterator operator=(const Iterator _val)
		{
			m_data = _val.m_data;
			return *this;
		}

		bool operator<(const Iterator _val)
		{
			return m_data < _val.m_data;
		}

		Iterator operator=(__size_t i)
		{
			m_data += i;
			return *this;
		}

	};

public:


#pragma region 构造函数

	MyVector()
	{
		T* temp = new T[4];

		m_capacity = 4;

		m_size = 0;

		m_data = temp;
	}


	MyVector(const std::initializer_list<T> & _list)
	{
		Clear();

		auto temp = new T[_list.size() * 2];

		m_data = temp;

		m_capacity = _list.size() * 2;

		for each (auto item in _list)
		{
			Add(item);
		}

	}


	MyVector(const MyVector<T> & _list)
	{
		Clear();

		auto temp = new T[_list.size() * 2];

		m_data = temp;

		m_capacity = _list.size() * 2;

		for each (auto item in _list)
		{
			Add(item);
		}

	}


	MyVector(MyVector<T> && _list)
	{
		Clear();

		m_size = _list.m_size;

		m_capacity = _list.m_capacity;

		m_data = _list.m_data;

		_list.m_data = nullptr;

		_list.m_size = 0;

		_list.m_capacity = 0;
	}


	~MyVector()
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
		}
	}


#pragma endregion 构造函数


#pragma region 重载运算符

	MyVector & operator=(const std::initializer_list<T> & _list)
	{
		Clear();

		auto temp = new T[_list.size() * 2];

		m_data = temp;

		m_capacity = _list.size() * 2;

		for each (auto item in _list)
		{
			Add(item);
		}

	}


	MyVector & operator=(const MyVector & _vector)
	{
		Clear();

		m_capacity = _vector.size() * 2;

		auto temp = new T[m_capacity];

		m_data = temp;

		for each (T item in _vector)
		{
			Add(item);
		}

		return *this;
	}


	MyVector & operator=(MyVector<T> && _list)
	{
		Clear();

		m_size = _list.m_size;

		m_capacity = _list.m_capacity;

		m_data = _list.m_data;

		_list.m_data = nullptr;

		_list.m_size = 0;

		_list.m_capacity = 0;
	}


	T & operator[](__size_t i)
	{
		return m_data[i];
	}


#pragma endregion 重载运算符


	void Add(const T & _val)
	{
		CheckSize();

		m_data[m_size] = _val;

		m_size++;

	}


	void Insert(__size_t i, const T & _val)
	{
		if (i >= m_size)
		{
			throw out_of_range("Out of Range");

			return;
		}

		CheckSize();

		for (size_t j = m_size; j > i; j--)
		{
			m_data[j] = m_data[j - 1];
		}

		m_data[i] = _val;

		m_size++;
	}


	void RemoveAt(__size_t n)
	{
		if (n >= m_size)
		{
			throw out_of_range("Out of Range");

			return;
		}

		for (size_t i = n; i < m_size - 1; i++)
		{
			m_data[i] = m_data[i + 1];
		}

		m_size--;
	}


	bool Contain(const T & _val)
	{
		for each (auto item in *this)
		{
			if (item == _val)
			{
				return true;
			}
		}

		return false;
	}


	long IndexOf(const T & _val)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			if (_val == *(m_data + i)) return i;
		}
		return -1;
	}


	void Clear()
	{
		m_capacity = 0;

		m_size = 0;

		if (m_data != nullptr)
		{
			delete[] m_data;

			m_data = nullptr;
		}

	}


	bool Empty()
	{
		return m_size == 0;
	}


	void Sort(bool ascendind = true)
	{
		m_less_equal = [&](T _t1, T _t2) {return _t1 <= _t2; };

		__Sort_Compare(begin(), --end(), ascendind);

	}


	void Sort(__Fun_Less_Equal _fun_less_equal, bool ascendind = true)
	{
		m_less_equal = _fun_less_equal;

		__Sort_Compare(begin(), --end(), ascendind);

		m_less_equal = nullptr;
	}


	__size_t size() const
	{
		return m_size;
	}

	__size_t capacity() const
	{
		return m_capacity;
	}

	Iterator begin() const
	{
		return Iterator(m_data, 0);
	}

	Iterator end() const
	{
		return Iterator(m_data, m_size);
	}

private:

	void CheckSize()
	{
		if (m_size == m_capacity)
		{
			auto temp = new T[m_size * 2];

			for (size_t i = 0; i < m_size; i++)
			{
				temp[i] = m_data[i];
			}

			delete[] m_data;

			m_data = temp;

			m_capacity = m_size * 2;
		}
	}

	void __Sort_Compare(Iterator _begin, Iterator _end, bool ascendind = true)
	{

		if (_begin.m_data >= _end.m_data) return;

		T base = *_begin.m_data;

		Iterator i = _begin;

		Iterator j = _end;

		while (i.m_data != j.m_data)
		{
			if (ascendind)
			{
				while (m_less_equal(base, *j.m_data) && i.m_data < j.m_data)
				{
					j--;
				}

				while (m_less_equal(*i.m_data, base) && i.m_data < j.m_data)
				{
					i++;
				}

			}
			else if (i.m_data < j.m_data)
			{
				while (m_less_equal(*j.m_data, base) && i.m_data < j.m_data)
				{
					j--;
				}

				while (m_less_equal(base, *i.m_data) && i.m_data < j.m_data)
				{
					i++;
				}

			}

			if (i < j)
			{
				swap(*i.m_data, *j.m_data);
			}

		}

		swap(*i.m_data, *_begin.m_data);

		__Sort_Compare(_begin, i, ascendind);

		__Sort_Compare(++i, _end, ascendind);

	}

private:

	T* m_data = nullptr;

	__size_t m_size = 0;

	__size_t m_capacity = 0;

	__Fun_Less_Equal m_less_equal = nullptr;

};
