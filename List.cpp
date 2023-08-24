#include <cstddef>
#include <stdexcept>

#define COEFICIENT 1.5

template <class T>
class List
{
	private:
		T* data;
		int size;
		int reserve;
	public:
		List(int);
		~List();
		void add(int, T);
		T remove(int);
		T get(int);
		void set(int, T);
		int len();
};

template <class T>
List<T>::List(int initial)
{
	this->size = 0;
	this->reserve = initial;
	this->data = new T[initial];
}

template <class T>
List<T>::~List()
{
	delete this->data;
}

template <class T>
void List<T>::add(int position, T element)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	
	if(this->size < this->reserve)
	{
		for(int i = this->size; i > position; i--)
		{
			this->data[i] = this->data[i - 1];
		}
		
		this->data[position] =  element;
		this->size++;
	}
	else
	{
		T *temp = this->data;
		this->reserve *= COEFICIENT;
		this->data = new T[this->reserve];
		this->size++;
		
		for(int i = 0; i < position; i++)
		{
			this->data[i] = temp[i];
		}
		
		this->data[position] = element;
		
		for(int i = position + 1; i < this->size; i++)
		{
			this->data[i] = temp[i - 1];
		}
		
		delete temp;
	}
}

template <class T>
T List<T>::remove(int position)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	if(this->size == 0)
	{
		throw std::length_error("The list is empty");
	}
	
	T value = this->data[position];
	
	this->size--;
	
	for(int i = position; i < this->size; i++)
	{
		this->data[i] = this->data[i + 1];
	}
	
	return value;
}

template <class T>
T List<T>::get(int position)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	
	return this->data[position];
}

template <class T>
void List<T>::set(int position, T element)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	
	this->data[position] = element;
}

template <class T>
int List<T>::len()
{
	return this->size;
}
