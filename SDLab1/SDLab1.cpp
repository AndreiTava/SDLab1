#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <random>

using namespace std;

typedef long long llong;

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

class Sorting_alg
{
public:
    string name;
    virtual const void sort(vector<llong>& v){};
};

class STL : public Sorting_alg
{
public:
    STL()
    {
       name = "STL Sort";
    }
    const void sort(vector<llong>& v) { std::sort(v.begin(), v.end()); };
} stls;

class Merge : public Sorting_alg
{
public:
    Merge()
    {
        name = "Merge Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} merges;

class Counting : public Sorting_alg
{
public:
    Counting()
    {
        name = "Counting Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} countings;

class CountingM : public Sorting_alg
{
public:
    CountingM()
    {
        name = "Counting Sort(Map)";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} countingsm;

template <llong base>
class LSDRadix : public Sorting_alg
{
public:
    LSDRadix()
    {
        name = "LSD Radix(B" + std::to_string(base) + ") Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};
LSDRadix<10> lsdradixs10;

class Bubble : public Sorting_alg
{
public:
    Bubble()
    {
        name = "Bubble Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} bubbles;

class Selection : public Sorting_alg
{
public:
    Selection()
    {
        name = "Selection Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} selections;

class Insertion : public Sorting_alg
{
public:
    Insertion()
    {
        name = "Insertion Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} insertions;

const void Selection::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    auto min = left;
    for (;left != right - 1; ++left)
    {
        min = left;
        for (auto it = left + 1; it != right; ++it)
            if (*it < *min)
                min=it;
        swap(*min, *left);
    }
}

const void Bubble::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (auto it = left; it != right - 1; ++it)
            if (*it > *(it + 1))
            {
                sorted = false;
                swap(*it, *(it + 1));
            }
    }

}

const void Insertion::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    for (auto it = left + 1; it != right; ++it)
    {
        auto rt = it;
        while (rt != left && *rt < *(rt - 1))
        {
            swap(*rt, *(rt - 1));
            --rt;
        }
    }
}

const void Merge::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    
    size_t dist = right - left;
    static vector<llong> aux(dist);
    if (aux.size() < dist)
        aux.resize(dist);
    auto middle = left;
    middle += dist / 2;
    if (dist > 2)
    {
        sort(left, middle);
        sort(middle, right);
    }
    auto itlft = left, itrht = middle, itaux = aux.begin();
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

    for (auto itcpy = aux.begin(); itcpy != itaux; ++itcpy)
        *left++ = *itcpy;
    if (itaux == aux.end())
        aux.clear();
}

const void Counting::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    llong max = 0;
    for (auto it = left; it != right; ++it)
        if (*it > max)
            max = *it;

    vector<llong> aux(max+1);

    for (auto it = left; it != right; ++it)
        ++aux[*it];

    for (llong i=1; i<=max; ++i)
        while (aux[i])
        {
            *left++ = i;
            --aux[i];
        }
}
const void CountingM::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    map<llong, llong> aux;

    for (auto it = left; it != right; ++it)
        ++aux[*it];

    for (auto mit = aux.begin(); mit != aux.end(); ++mit)
        while (mit->second)
        {
            *left++ = mit->first;
            --(mit->second);
        }
};

template <llong base>
const void LSDRadix<base>::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    vector<llong> buckets[base];
    llong den = 1;
    while (true)
    {
        for (auto it = left; it != right; ++it)
        {
            llong cif = ((*it) / den) % base;
            buckets[cif].push_back(*it);

        }

        if (buckets[0].size() == right - left)
            break;

        auto jt = left;
        for (auto& bucket : buckets)
        {
            for (auto& nr : bucket)
                *jt++ = nr;
            bucket.clear();
        }

        den *= base;
    }
}
using namespace std;

int main()
{
    vector<Sorting_alg*> sorts;
    sorts.push_back(&stls);
    sorts.push_back(&merges);
    sorts.push_back(&countings);
    sorts.push_back(&lsdradixs10);
    //sorts.push_back(&bubbles);
    //sorts.push_back(&insertions);
    //sorts.push_back(&selections);
    //sorts.push_back(&countingm);

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
        vector<llong> v_test = generate_test(gen, test.first, test.second);
        cout << "Test size: " << test.first << " Max Value: " << test.second << endl << endl;
        for (auto& sort : sorts)
        {
            auto v = v_test;
            //print_vect(v);
            auto beg = chrono::high_resolution_clock::now();
            sort->sort(v);
            auto end = chrono::high_resolution_clock::now();
            //print_vect(v);
            chrono::duration<double> time = end - beg;
            cout << sort->name << ": " << time.count() << "s Sorted: " << ((is_sorted(v) == 1) ? "yes\n" : "no\n")<<endl;
        }
        cout << endl;
    }
    return 0;

}

