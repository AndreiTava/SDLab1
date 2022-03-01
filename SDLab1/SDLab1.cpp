#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <random>

using namespace std;

typedef long long llong;

vector<llong> glo_aux(1000000);

void print_vect(vector<llong>& v)
{
    for (const llong & nr : v)
        cout << nr << " ";
    cout << endl;
}

vector<llong> generate_test(default_random_engine& gen ,const llong size, const llong max)
{
    vector<llong> v(size);
    auto dist = uniform_int_distribution<llong>(1,max);
    for (llong& nr : v)
        nr = dist(gen);
    return v;
}

bool is_sorted(vector<llong>& v)
{
    for (auto it = v.begin(); it != v.end() - 1; ++it)
        if (*it > *(it + 1))
            return false;
    return true;
}

class sorting_alg
{
public:
    static vector<llong> glo_aux;
    const string name;
    virtual const void sort(vector<llong>& v){};
};

class STL : sorting_alg
{
public:
    const string name = "STL Sort";
    const void sort(vector<llong>& v);
} stl;
class Merge : sorting_alg
{
private:

    const void rec_merge(vector<llong>::iterator left, vector<llong>::iterator right);
public:
    const string name = "Merge Sort";
    const void sort(vector<llong>& v);
} merge;
class Counting : sorting_alg
{
public:
    const string name = "Counting Sort";
    const void sort(vector<llong>& v);
} counting;
const void STL::sort(vector<llong>& v)
{
    std::sort(v.begin(), v.end());
}

void selection_sort(vector<llong>& v)
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

void bubble_sort(vector<llong>& v)
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

void insertion_sort(vector<llong>& v)
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

//void rec_merge_short(vector<llong>::iterator left, vector<llong>::iterator right)
//{
//    auto dist = distance(left,right);
//    auto middle = left;
//    advance(middle, dist / 2);
//    if (dist > 2)
//    {
//        rec_merge_short(left,middle);
//        rec_merge_short(middle,right);
//    }
//    inplace_merge(left,middle,right);
//}
const void Merge::rec_merge(vector<llong>::iterator left, vector<llong>::iterator right)
{

    auto dist = distance(left, right);
    if (dist > glo_aux.size())
        glo_aux.resize(dist);
    auto middle = left;
    advance(middle, dist / 2);
    if (dist > 2)
    {
        rec_merge(left, middle);
        rec_merge(middle, right);
    }
    auto itlft = left, itrht = middle, itaux = glo_aux.begin();
    while (itlft != middle && itrht!= right)
    {
        if (itrht != right && *itlft <= *itrht)
            *itaux++ = *itlft++;
 
        if (itlft != middle && *itrht <= *itlft)
            *itaux++ = *itrht++;
    }
    while (itlft != middle)
        *itaux++ = *itlft++;

    while (itrht != right)
        *itaux++ = *itrht++;

    for (auto itcpy = glo_aux.begin(); itcpy != itaux; ++itcpy)
        *left++ = *itcpy;
}
const void Merge::sort(vector<llong>& v)
{
    rec_merge(v.begin(), v.end());
}

//const void sort(vector<llong>& v)
//{
//    llong max = 0;
//    for (const llong& nr : v)
//        if (nr > max)
//            max = nr;
//
//    if (max > glo_aux.size())
//        glo_aux.resize(max);
//
//    for (const llong& nr : v)
//        ++glo_aux[nr];
//
//    auto it = v.begin();
//    for (llong i=1; i<=max; ++i)
//        while (glo_aux[i])
//        {
//            *it++ = i;
//            --glo_aux[i];
//        }
//}
const void Counting::sort(vector<llong>& v)
{
    map<llong, llong> aux;

    for (const llong& nr : v)
        ++aux[nr];

    auto it = v.begin();
    for (auto mit = aux.begin(); mit != aux.end(); ++mit)
        while (mit->second)
        {
            *it++ = mit->first;
            --(mit->second);
        }
};

using namespace std;

int main()
{
    vector<sorting_alg&> sorts;
    sorts.push_back(stl);

    llong n_tests;

    ifstream in("Tests.txt");

    in >> n_tests;
    vector<pair<llong,llong>> tests(n_tests);
    for (auto it = tests.begin(); it != tests.end(); ++it)
        in >> it->first>>it->second;

    random_device s_gen;

    auto gen = default_random_engine(s_gen());

    for (auto& test : tests)
    {
        vector<llong> v = generate_test(gen, test.first, test.second);
        cout << "Test size: " << test.first << " Max Value: " << test.second << endl;
        for(auto& sort : sorts)
        auto beg = chrono::high_resolution_clock::now();
        merge_sort(v);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> time = end - beg;

        cout << time.count() << "s Sorted: " << ((is_sorted(v) == 1) ? "yes\n" : "no\n");
    }

}

