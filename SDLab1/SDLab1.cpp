#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <utility>
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

void rec_merge(vector<int>::iterator left, vector<int>::iterator right)
{
    auto dist = distance(left,right);
    auto middle = left;
    advance(middle, dist / 2);
    if (dist > 2)
    {
        rec_merge(left,middle);
        rec_merge(middle,right);
    }
    inplace_merge(left,middle, right);
}

void merge_sort(vector<int>& v)
{
    rec_merge(v.begin(), v.end());
}

int main()
{

    int n_tests;

    ifstream in("Tests.txt");

    in >> n_tests;
    vector<pair<int,int>> tests(n_tests);
    for (auto it = tests.begin(); it != tests.end(); ++it)
        in >> (*it).first>>(*it).second;

    random_device s_gen;

    auto gen = default_random_engine(s_gen());

    for (auto test : tests)
    {
        cout << "size= " << test.first << " max=" << test.second << endl;

        vector<int> v = generate_test(gen, test.first, test.second);

        auto beg = chrono::high_resolution_clock::now();

        merge_sort(v);

        auto end = chrono::high_resolution_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - beg);

        string result = (is_sorted(v) == 1) ? "yes" : "no";

        cout << time.count() << " microsecs  sorted: " << result << endl;
    }

}

