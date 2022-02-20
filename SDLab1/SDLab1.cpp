#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void print_vect(vector<int>& v)
{
    for (const int& nr : v)
        cout << nr << " ";
    cout << endl;
}

vector<int> generate_test(default_random_engine& gen ,const int size, const int max)
{
    vector<int> v(size);
    auto dist = uniform_int_distribution<int>(1,max);
    for (int& nr : v)
        nr = dist(gen);
    return v;
}

bool is_sorted(vector<int>& v)
{
    for (auto it = v.begin(); it != v.end() - 1; ++it)
        if (*it > *(it + 1))
            return false;
    return true;
}

void std_sort(vector<int>& v)
{
    sort(v.begin(), v.end());
}

void selection_sort(vector<int>& v)
{
    auto min = v.begin();
    for (auto it = v.begin(); it != v.end() - 1; ++it)
    {
        min = it;
        for (auto jt = it + 1; jt != v.end(); ++jt)
            if (*jt > *min)
                min=jt;
        swap(*min, *it);
    }
}

void bubble_sort(vector<int>& v)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (auto it = v.begin(); it != v.end() - 1; ++it)
            if (*it > *(it + 1))
            {
                sorted = false;
                swap(*it, *(it + 1));
            }
    }

}

void insertion_sort(vector<int>& v)
{
    for (auto it = v.begin() + 1; it != v.end(); ++it)
    {
        auto rt = it;
        while (rt != v.begin() && *rt < *(rt - 1))
        {
            swap(*rt, *(rt - 1));
            --rt;
        }
    }
}






int main()
{

    random_device s_gen;

    auto gen = default_random_engine(s_gen());

    vector<int> v = generate_test(gen,1000, 999);

    auto beg = chrono::high_resolution_clock::now();

    insertion_sort(v);

    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(end - beg);

    cout << time.count()<<" mcs , sorted: "<<is_sorted(v) << endl;

}

