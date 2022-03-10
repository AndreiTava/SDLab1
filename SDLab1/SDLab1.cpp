#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <array>
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

class Quick : public Sorting_alg
{
public:
    Quick()
    {
        name = "QuickSort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} quicks;

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
class LSDRadixO : public Sorting_alg
{
public:
    LSDRadixO()
    {
        name = "LSD Radix(B" + std::to_string(base) + ") Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};

template <llong base>
class LSDRadixN : public Sorting_alg
{
public:
    LSDRadixN()
    {
        name = "New LSD Radix(B" + std::to_string(base) + ") Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};

LSDRadixN<65536> newradixs;

template <llong power>
class LSDRadix : public Sorting_alg
{
public:
    LSDRadix()
    {
        name = "Explicit LSD Radix(B2^" + std::to_string(power) + ") Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};
LSDRadix<16> radixs16;


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

class Shell : public Sorting_alg
{
    vector<llong> gaps;

public:
    Shell(initializer_list<llong> gaps_seq)
    {
        name = "Shell Sort";
        gaps = gaps_seq;
    }
    Shell(vector<llong> gaps_seq)
    {
        name = "Shell Sort";
        gaps = gaps_seq;
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
}shells({1750, 701, 301, 132, 57, 23, 10, 4, 1});

template<llong nr_buck, llong threshold>
class Bucket : public Sorting_alg
{
    Sorting_alg* salg;
public:
    Bucket(Sorting_alg& alg)
    {
        salg = &alg;
        name = "Bucket Sort(" + to_string(nr_buck) + " buckets, " + salg->name + ")";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right, llong nrb=nr_buck);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};
Bucket<50,100> buckets(stls);

template <llong threshold>
class Intro : public Sorting_alg
{
public:
    Intro()
    {
        name = "IntroSort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};
Intro<100> intros;

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
        for(auto rt = it;rt != left && *rt < *(rt - 1); --rt)
            swap(*rt, *(rt - 1));
    }
}

const void Shell::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    for(auto& gap : gaps)
    {
        for (llong index = 0; index < gap; ++index)
        {
            for (auto it = left + index + gap; it < right; it += gap)
            {
                for (auto rt = it; rt >= left + gap && *rt < *(rt - gap); rt -= gap)
                    swap(*rt, *(rt - gap));
            }
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

const void Quick::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    auto dist = right - left;
	if(dist>2)
	{
        auto pivot = right - 1;
        auto ins_it = left;
        for(auto it = left; it!=right; ++it)
        {
            if (*it <= *pivot && it != pivot)
            {
                swap(*ins_it, *it);
                ++ins_it;
            }
        }
        swap(*ins_it, *pivot);

        sort(left, ins_it);
        sort(ins_it, right);
	}
};

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
const void LSDRadixO<base>::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    vector<vector<llong>> buckets(base);
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
template <llong base>
const void LSDRadixN<base>::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    vector<llong> buckets(base);
    vector<llong> sorted(right-left);
    llong max = 0;
    for (auto it = left; it != right; ++it)
        if (*it > max)
            max = *it;
    llong den = 1;
    while (max/den > 0)
    {
        for (auto it = left; it != right; ++it)
        {
            llong cif = ((*it) / den) % base;
            ++buckets[cif];
        }
        for (auto it = buckets.begin() + 1; it != buckets.end(); ++it)
            *it += *(it - 1);
        for (auto it = right - 1; it >left; --it)
        {
            llong cif = ((*it) / den) % base;
            sorted[buckets[cif] - 1] = *it;
            --buckets[cif];
        }

        llong cif = ((*left) / den) % base;
        sorted[buckets[cif] - 1] = *left;
        --buckets[cif];

        for (llong& nr : buckets)
            nr = 0;
        auto it = left;
        for (const llong& nr : sorted)
            *it++ = nr;

        den *= base;
    }
}
template <llong power>
const void LSDRadix<power>::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    llong base = 1 << power;
    vector<llong> buckets(base);
    vector<llong> sorted(right - left);
    llong max = 0;
    for (auto it = left; it != right; ++it)
        if (*it > max)
            max = *it;
    llong den = 0;
    while ((max >> den) > 0)
    {
        for (auto it = left; it != right; ++it)
        {
            llong cif = ((*it) >> den) & (base - 1);
            ++buckets[cif];
        }

        for (auto it = buckets.begin() + 1; it != buckets.end(); ++it)
            *it += *(it - 1);

        for (auto it = right - 1; it > left; --it)
        {
            llong cif = ((*it) >> den) & (base - 1);
            sorted[buckets[cif] - 1] = *(it);
            --buckets[cif];
        }
        llong cif = ((*left) >> den) & (base - 1);
        sorted[buckets[cif] - 1] = *left;
        --buckets[cif];

        for (llong& nr : buckets)
            nr = 0;
        auto it = left;
        for (const llong& nr : sorted)
            *it++ = nr;

        den +=power;
    }
}

template <llong nr_buck, llong threshold>
const void Bucket<nr_buck,threshold>::sort(vector<llong>::iterator left, vector<llong>::iterator right, llong nrb)
{
    vector<vector<llong>> buckets(nrb);
    llong max = 0;
    for (auto it = left; it != right; ++it)
        if (*it > max)
            max = *it;
    ++max;
	for (auto it = left; it != right; ++it)
	{
        llong buck = ((*it) * nr_buck) / max;
		buckets[buck].push_back(*it);
	}

    for (auto& bucket : buckets)
    {
        if (bucket.size() <= threshold)
            salg->sort(bucket);
        else
            sort(bucket.begin(), bucket.end());
    }

	auto jt = left;
	for (auto& bucket : buckets)
	{
		for (auto& nr : bucket)
			*jt++ = nr;
		bucket.clear();
	}
}

template <llong threshold>
const void Intro<threshold>::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    static llong max_depth;
}
using namespace std;

int main()
{
    vector<Sorting_alg*> sorts;
    sorts.push_back(&stls);
    sorts.push_back(&merges);
    sorts.push_back(&quicks);
    //sorts.push_back(&countings);
    //sorts.push_back(&radixs16);
    //sorts.push_back(&buckets);
    //sorts.push_back(&bubbles);
    //sorts.push_back(&insertions);
    //sorts.push_back(&selections);
    //sorts.push_back(&shells);

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
            cout << sort->name << ": " << time.count() << "ms Sorted: " << ((is_sorted(v) == 1) ? "yes\n" : "no\n")<<endl;
        }
        cout << endl;
    }
    return 0;

}

