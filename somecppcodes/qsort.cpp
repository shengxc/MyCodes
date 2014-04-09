#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
template<typename T>
class compare
{
public:
    bool operator()(T a,T b) const
    {
        return a > b;
    }
};

template<typename T>
void printarr(T* arr,int s,int e)
{
    cout << "[";
    for(int i = s;i <= e;++ i)
        cout << arr[i] << " ";
    cout << "]";
}
template<typename T>
inline void swap(T* arr,int a,int b)
{
    T tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

template<typename T>
int partition(T* arr,int start,int end,compare<T> c)
{
    int idx = start + rand() % (end - start);
    swap(arr,idx,end);
    int small = start - 1;
    for (int i = start;i < end;++ i)
    {
        if(c(arr[i],arr[end]))
        {
            ++ small;
            swap(arr,small,i);
        }
    }
    swap(arr,small + 1,end);
    return small + 1;
}

template<typename T>
void quicksort(T* arr,int start,int end,compare<T> c)
{
    if(start >= end)
        return;
    int idx = partition(arr,start,end,c);
    quicksort(arr,start,idx - 1,c);
    quicksort(arr,idx + 1,end,c);
}

template<typename T>
void qsort(T* arr,int n,compare<T> c)
{
    if(n <= 0)
        return;
    quicksort(arr,0,n - 1,c);
}
int main()
{
    compare<int> comp;
    srand(time(NULL));
    int len = rand() % 10;
    int* arr = new int[len];
    for(int i = 0;i < len;++ i)
        arr[i] = rand() % 100;
    cout << "org\n";
    printarr(arr,0,len - 1);
    cout << "\n";
    qsort(arr,len,comp);
    cout << "sorted\n";
    printarr(arr,0,len - 1);
    cout << "\n";
    delete[] arr;
}
