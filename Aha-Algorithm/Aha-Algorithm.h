#pragma once




template<typename T>
class MyList
{
public:


	class Iterator
	{

	public:

		size_t index = 0;

		MyList<T> & outer;

		Iterator() = default;

		Iterator(MyList<T> & o, int i) : outer(o), index(i) {}

		void operator++()
		{
			index++;
		}

		T operator*() const
		{
			return outer.operator[](index);
		}

		bool operator!=(Iterator i)
		{
			return i.index != index;
		}

	};



	struct MyStruct
	{
		T data;

		MyStruct *next = nullptr;

		MyStruct *previous = nullptr;

	};

public:

	MyList() = default;


	MyList(std::initializer_list<T> _Ilist)
	{
		Clear();

		for each (const T & item in _Ilist)
		{
			Add(item);
		}

	}


	MyList(MyList<T> && _list)
		:m_mark(_list.m_mark), m_size(_list.m_size)
	{
		_list.m_size = 0;
		_list = _list.m_mark->previous = _list.m_mark->next = nullptr;
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


	T operator[](unsigned n)
	{
		auto s = m_mark->previous;

		for (size_t i = 0; i < n; i++)
		{
			s = s->next;
		}

		return s->data;
	}


	void Insert(size_t i, const T & _val)
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


	Iterator begin()
	{
		Iterator temp(*this, 0);
		return temp;
	}

	Iterator end()
	{
		Iterator temp(*this, size());
		return temp;
	}

private:

	MyStruct *m_mark = nullptr;

	size_t m_size = 0;



};
