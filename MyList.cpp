//File Name: MyList.cpp
//Author: Su Chang (Class No.F1403022; Student No.5140309522)
//This file defines a class called "MyList" whose function is similar to a list in Python.
//Negative indexes are acceptable as long as used in the correct way just like that in Python.

#include<iostream>

using namespace std;

class out_of_range{};
class pop_empty{};

template<class T> class MyList;
template<class T> ostream &operator << (ostream &os, const MyList<T> &obj);

template<class T>
class MyList
{
private:
	T *a;
	int size, length;
	void double_space();	//double the space whenever it is not large enough
public:
	MyList(){
		size = 100;
		length = 0;
		a = new T [size];
	}
	MyList(int num, const T &item);	//put "item" into MyList "num" times
	MyList(const MyList &l);	//copy another MyList
	MyList(T *arr, int len);	//build MyList with the first "len" elements of "arr"
	void push(const T &item);	//add "item" to the end of MyList
	T pop();	//delete the last element of MyList and return it
	void insert(int index, const T &item);	//insert "item" into MyList at the location shown by "index"
	void clean();	//clear up MyList
	int get_size();	//return the number of elements in MyList
	void erase(int start, int end);	//delete the elements between the location indicated by "start" and "end"(both ends included)
	T get_item(int index);	//return the element whose location is "index"
	MyList get_item(int start, int end);	//return a new list of elements between the location referred to by "start" and "end" in MyList(both ends included)
	int count(const T &item);	//return the number of elements in MyList which are just the same as "item"
	void remove(const T &item);	//delete the first element the same as "item" found in MyList
	MyList &operator = (const MyList &l);	//assign MyList
	MyList &operator += (const T &item);	//push a new item to the end of MyList(equivalent to the "push" function above)
	MyList &operator += (const MyList &l);	//stitch another list to MyList at the end
	T &operator [](int index);	//return the element whose location is "index"(equivalent to the first "get_item" funcation above)
	friend ostream & operator<<<T>(ostream &os, const MyList<T> &obj);	//print MyList in the way that Python does this job
	void sort(bool less=true);	//sort MyList(less = true: ascending; otherwise: descending)
	void reverse();	//reverses all the elements in MyList
	~MyList(){delete [] a;}
	
	friend MyList operator + (const MyList &l1, const MyList &l2)
	{
		int *a, length = l1.length + l2.length;
		a = new T [length];
		for (int i = 0; i < l1.length; ++i)
			a[i] = l1.a[i];
		for (int i = 0; i < l2.length; ++i)
			a[l1.length + i] = l2.a[i];
		MyList<T> b(a, length);
		delete [] a;
		return b;
	}
	
	friend MyList operator + (const MyList &l1, const T &item)
	{
		MyList<T> l2(l1);
		l2.push(item);
		return l2;
	}
};

template<class T>
void MyList<T>::double_space()
{
	T *b = a;
	size *= 2;
	a = new T [size];
	for (int i = 0; i < size; ++i)
		a[i] = b[i];
	delete [] b;
}

template<class T>
MyList<T>::MyList(int num, const T &item)
{
	size = num;
	length = num;
	a = new T [num];
	for (int i = 0; i < num; ++i)
		a[i] = item;
}

template<class T>
MyList<T>::MyList(const MyList &l)
{
	size = l.size;
	length = l.length;
	a = new T [size];
	for (int i = 0; i < length; ++i)
		a[i] = l.a[i];
}

template<class T>
MyList<T>::MyList(T *arr, int len)
{
	size = len;
	length = len;
	a = new T [len];
	for (int i = 0; i < length; ++i)
		a[i] = arr[i];
}

template<class T>
void MyList<T>::push(const T &item)
{
	if (size == length)
		double_space();
	a[length] = item;
	++length;
}

template<class T>
T MyList<T>::pop()
{
	try{
		if (!length)
			throw pop_empty();
		else{
			--length;
			return a[length];
		}
	}
	catch(pop_empty){
		cout << "Error! You're attempting to pop an empty list." << endl;
	}
}

template<class T>
void MyList<T>::insert(int index, const T &item)
{	if (size == length)
		double_space();
	try{
		if (index < 0)
			index += length;
		if (index < 0 || index > length)
			throw out_of_range();
		for (int i = length-1; i >= index; --i)
			a[i+1] = a[i];
		a[index] = item;
		++length;
	}
	catch(out_of_range){
		cout << "Error! The index is out of range." << endl;
	}
}

template<class T>
void MyList<T>::clean()
{
	length = 0;
	size = 0;
}

template<class T>
int MyList<T>::get_size()
{
	return length;
}

template<class T>
void MyList<T>::erase(int start, int end)
{
	try{
		if (start < 0)
			start += length;
		if (end < 0)
			end += length;
		if (start < 0 || start > length || end < 0 || end > length)
			throw out_of_range();
		for (int i = start; i < length - (end - start + 1); ++i)
			a[i] = a[i+(end-start+1)];
		length -= end - start + 1;
	}
	catch(out_of_range){
		cout << "Error! The index is out of range." << endl;
	}
}

template<class T>
T MyList<T>::get_item(int index)
{
	try{
		if (index < 0)
			index += length;
		if (index < 0 || index >= length)
			throw out_of_range();
		return a[index];
	}
	catch(out_of_range){
		cout << "Error! The index is out of range." << endl;
	}
}

template<class T>
MyList<T> MyList<T>::get_item(int start, int end)
{
	try{
		if (start < 0)
			start += length;
		if (end < 0)
			end += length;
		if (start < 0 || start > length || end < 0 || end > length)
			throw out_of_range();
		if (start > end){
			MyList<T> b;
			return b;
		}
		else{
			MyList<T> b(a + start, end - start + 1);
			return b;
		}
	}
	catch(out_of_range){
		cout << "Error! The index is out of range." << endl;
	}
}

template<class T>
int MyList<T>::count(const T &item)
{
	int cnt = 0;
	for (int i = 0; i < length; ++i){
		if (a[i] == item)
			++cnt;
	}
	return cnt;
}

template<class T>
void MyList<T>::remove(const T &item)
{
	int i;
	for (i = 0; i < length; ++i){
		if (a[i] == item){
			erase(i, i);
			break;
		}
	}
}

template<class T>
MyList<T> &MyList<T>::operator = (const MyList<T> &l)
{
	if (this == &l)
		return *this;
	delete [] a;
	size = l.size;
	length = l.length;
	a = new T [size];
	for (int i = 0; i < length; ++i)
		a[i] = l.a[i];
	return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const T &item)
{
	push(item);
	return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const MyList &l)
{
	length += l.length;
	while (length > size)
		double_space();
	for (int i = 0; i < l.length; ++i)
		a[length - l.length + i] = l.a[i];
	return *this;
}


template<class T>
T &MyList<T>::operator [](int index)
{
	try{
		if (index < 0)
			index += length;
		if (index < 0 || index >= length)
			throw out_of_range();
		return a[index];
	}
	catch(out_of_range){
		cout << "Error! The index is out of range." << endl;
	}
}

template<class T>
int divide(T *a, int low, int high)
{
	int k = a[low];
	do{
		while (low < high && a[high] >= k)
			--high;
		if (low < high){
			a[low] = a[high];
			++low;
		}
		while (low < high && a[low] <= k)
			++low;
		if (low < high){
			a[high] = a[low];
			--high;
		}
	}
	while (low != high);
	a[low] = k;
	return low;
}

template<class T>
ostream &operator <<(ostream &os, const MyList<T> &obj)
{
	os << "[";
	if (obj.length){
		for (int i = 0; i < obj.length - 1; ++i)
			os << obj.a[i] << ", ";
		os << obj.a[obj.length - 1];
	}
	os << "]";
	return os;
}

template<class T>
void quicksort_ascending(T *a, int low, int high)
{
	int mid;
	if (low >= high)
		return;
	mid = divide(a, low, high);
	quicksort_ascending(a, low, mid - 1);
	quicksort_ascending(a, mid + 1, high);
}

template<class T>
void MyList<T>::sort(bool less)
{
	if (length > 1){
		quicksort_ascending(a, 0, length - 1);
		if (!less)
			reverse();
	}
}

template<class T>
void MyList<T>::reverse()
{
	T c;
	for (int i = 0; i < length / 2; ++i){
		c = a[i];
		a[i] = a[length - i - 1];
		a[length - i - 1] = c;
	}
}

int main()
{
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);// a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] (start > end)
	b = a.get_item(3, -1); // b = [1, 0, 12]
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12]
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]
	b.insert(3, 116); // b = [15, 4, 1, 116, 0, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 1, 116, 0, 12, 15, 4, 0, 12]
	cout <<b << endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	return 0;
}
