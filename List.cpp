#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <algorithm>

template <class T>
class List
{
    private:
        T* data;
        size_t size;
        size_t reserve;
        bool sorted;
    public:
        List();
        List(size_t initial);
        ~List();
        void add(const T& element);
        void add(const T& element, size_t position);
        T remove(size_t position);
        const T& get(size_t position) const;
        void set(size_t position, const T& element);
        size_t len() const;
        void display() const;
        void sort();
        int find(const T& target) const;
    private:
        static constexpr double COEFFICIENT = 1.5;
};

template <class T>
List<T>::List() : size(0), reserve(10), data(new T[10]), sorted(false) {}

template <class T>
List<T>::List(size_t initial) : size(0), reserve(initial), data(new T[initial]), sorted(false) {}

template <class T>
List<T>::~List()
{
    delete[] this->data;
}

template <class T>
void List<T>::add(const T& element)
{
    if(this->size == this->reserve)
    {
        T* temp = this->data;
        this->reserve *= this->COEFFICIENT;

        try
        {
            this->data = new T[this->reserve];
        } 
        catch(const std::bad_alloc& e)
        {
            delete[] temp;
            throw e;
        }

        std::copy(temp, temp + this->size, this->data);
        delete[] temp;
    }

    this->data[this->size++] = element;
    this->sorted = false;
}

template <class T>
void List<T>::add(const T& element, size_t position)
{
    if(position > this->size || position < 0)
    {
        throw std::out_of_range("Invalid position");
    }

    if(this->size < this->reserve)
    {
        for(size_t i = this->size; i > position; i--)
        {
            this->data[i] = this->data[i - 1];
        }

        this->data[position] = element;
        this->size++;
    } 
    else
    {
        T* temp = this->data;
        this->reserve *= this->COEFFICIENT;

        try
        {
            this->data = new T[this->reserve];
        } 
        catch(const std::bad_alloc& e)
        {
            delete[] temp;
            throw e;
        }

        this->size++;

        std::copy(temp, temp + position, this->data);
        this->data[position] = element;
        std::copy(temp + position + 1, temp + this->size, this->data);

        delete[] temp;
    }

    this->sorted = false;
}

template <class T>
T List<T>::remove(size_t position)
{
    if(position >= this->size)
    {
        throw std::out_of_range("Invalid position");
    }
    if(this->size == 0)
    {
        throw std::length_error("The list is empty");
    }

    T value = this->data[position];
    this->size--;

    for(size_t i = position; i < this->size; i++)
    {
        this->data[i] = this->data[i + 1];
    }

    this->sorted = false;

    return value;
}

template <class T>
const T& List<T>::get(size_t position) const
{
    if(position >= this->size)
    {
        throw std::out_of_range("Invalid position");
    }

    return this->data[position];
}

template <class T>
void List<T>::set(size_t position, const T& element)
{
    if(position >= this->size)
    {
        throw std::out_of_range("Invalid position");
    }

    this->data[position] = element;

    this->sorted = false;
}

template <class T>
size_t List<T>::len() const
{
    return this->size;
}

template <class T>
void List<T>::display() const
{
    std::cout << '[';

    for(size_t i = 0; i < this->size; ++i)
    {
        std::cout << this->data[i];

        if (i < this->size - 1)
        {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}

template <class T>
void List<T>::sort()
{
    if(this->size < 2)
    {
        return;
    }

    int low = 0;
    int high = this->size - 1;

    int stack[high - low + 1];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while(top >= 0)
    {
        high = stack[top--];
        low = stack[top--];

        int pivot = this->data[high];
        int i = low - 1;

        for(int j = low; j < high; ++j)
        {
            if(this->data[j] <= pivot)
            {
                ++i;
                std::swap(this->data[i], this->data[j]);
            }
        }

        std::swap(this->data[i + 1], this->data[high]);

        int pivotIndex = i + 1;

        if(pivotIndex - 1 > low)
        {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        if(pivotIndex + 1 < high)
        {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }

    this->sorted = true;
}

template <class T>
int List<T>::find(const T& target) const
{
    if(this->sorted)
    {
        int low = 0;
        int high = this->size - 1;

        while(low <= high)
        {
            int mid = low + (high - low) / 2;

            if(this->data[mid] == target)
            {
                return mid;
            } 
            else if(this->data[mid] < target)
            {
                low = mid + 1;
            } 
            else
            {
                high = mid - 1;
            }
        }
    } 
    else
    {
        for(int i = 0; i < this->size; ++i)
        {
            if(this->data[i] == target)
            {
                return i;
            }
        }
    }

    return -1;
}
