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

vector<llong> generate_test(default_random_engine& gen ,const llong  size, const llong  max)
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

void std_sort(vector<llong>& v)
{
    sort(v.begin(), v.end());
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
void rec_merge(vector<llong>::iterator left, vector<llong>::iterator right)
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
void merge_sort(vector<llong>& v)
{
    rec_merge(v.begin(), v.end());
}

void counting_sort(vector<llong>& v)
{
    llong max = 0;
    for (const llong& nr : v)
        if (nr > max)
            max = nr;

    if (max > glo_aux.size())
        glo_aux.resize(max);

    for (const llong& nr : v)
        ++glo_aux[nr];

    auto it = v.begin();
    for (llong i=1; i<=max; ++i)
        while (glo_aux[i])
        {
            *it++ = i;
            --glo_aux[i];
        }
}
void counting_map_sort(vector<llong>& v)
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
        cout << "size= " << test.first << " max=" << test.second << endl;

        vector<llong> v = generate_test(gen, test.first, test.second);
        auto beg = chrono::high_resolution_clock::now();
        counting_map_sort(v);
        auto end = chrono::high_resolution_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - beg);

        cout << time.count() << " microsecs  sorted: " << ((is_sorted(v) == 1) ? "yes" : "no")<< endl;
    }

}

