#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <array>
#include <time.h>
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

vector<llong> generate_test(default_random_engine& gen, const string type ,const llong size, const llong max)
{

    vector<llong> v(size);
    auto dist = uniform_int_distribution<llong>(1,max);
	for (llong& nr : v)
		nr = dist(gen);
    if (type == "Ascending")
        sort(v.begin(), v.end());
    else if (type == "Descending")
        sort(v.rbegin(), v.rend());
    return v;
}

bool is_sorted(vector<llong>& v)
{
    for (auto it = v.begin(); it != v.end() - 1; ++it)
        if (*it > *(it + 1))
            return false;
    return true;
}

vector<llong> generate_ciura(llong max)
{
    vector<llong> seq =  {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    llong next_term = int(2.5 *seq.back());
    while (next_term < max)
    {
        seq.push_back(next_term);
        next_term = int(2.5 * seq.back());
    }
    return seq;
}
vector<llong> generate_tokuda(llong max)
{
    vector<llong> seq = { 1 };
    llong next_term = int(ceil(2.5 * seq.back() + 1));
    while (next_term < max)
    {
        seq.push_back(next_term);
        next_term = int(ceil(2.5 * seq.back() + 1));
    }
    return seq;
}
vector<llong> generate_knuth(llong max)
{
    vector<llong> seq = { 1 };
    llong next_term = 3*seq.back() + 1;
    while (next_term < ceil(max/3))
    {
        seq.push_back(next_term);
        next_term = 3 * seq.back() + 1;
    }
    return seq;
}
class Sorting_alg
{
public:
    string name;
    virtual const void sort(vector<llong>& v){};
    virtual const void sort(vector<llong>::iterator left, vector<llong>::iterator right){};
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
    const vector<llong>::iterator getPivot(vector<llong>::iterator left, vector<llong>::iterator right)
    {
	    switch(piv_type)
	    {
	    case 4:
	        {
            auto mid = left + (right - left) / 2;
            if (*left > *mid)
                swap(*left, *mid);
            if (*left > *(right - 1))
                swap(*left, *(right - 1));
            if (*(right - 1) > *mid)
                swap(*mid, *(right - 1));
            return right-1;
	        }
	    case 3:
        {
            srand(time(nullptr));
            return left + rand() % (right - left);
        }
	    case 2:
        {
            return left + (right - left) / 2;
        }
	    case 1:
        {
            return right - 1;
        }
        case 0:
        {
            return left;
        }
	    default:
        {
            return left;
        }
	    }
    };
    int piv_type;
public:
    Quick(int type,string piv)
    {
        piv_type = type;
        name = "Quick Sort(P:" + piv + ")";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
} quicks3(4,"Med3");
Quick quicksf(0, "First");
Quick quicksl(1, "Last");
Quick quicksm(2, "Mid");
Quick quicksr(3, "Random");

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
        name = "LSD Radix(B:" + std::to_string(base) + ") Sort";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};

LSDRadixN<65536> radixsb;

template <llong power>
class LSDRadix : public Sorting_alg
{
public:
    LSDRadix()
    {
        name = "Binary LSD Radix(B:2^" + std::to_string(power) + ") Sort";
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
    Shell(vector<llong> gaps_seq,string seq_name)
    {
        name = "Shell Sort ("+seq_name+")";
        gaps = gaps_seq;
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};
Shell shellsec(generate_ciura(100000000), "Extended Ciura");
Shell shellst(generate_tokuda(100000000), "Tokuda");
Shell shellsk(generate_knuth(100000000), "Knuth");

template<llong nr_buck>
class Bucket : public Sorting_alg
{
    Sorting_alg* salg;
public:
    Bucket(Sorting_alg& alg)
    {
        salg = &alg;
        name = "Bucket Sort(" + to_string(nr_buck) + " buckets, " + salg->name + ")";
    }
    const void sort(vector<llong>::iterator left, vector<llong>::iterator right);
    const void sort(vector<llong>& v) { sort(v.begin(), v.end()); };
};
Bucket<1000000> bucketsi(insertions);
Bucket<1000000> bucketss(stls);
Bucket<1000000> bucketsm(merges);
Bucket<1000000> bucketsq(quicks3);
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
    auto dist = right - left;
    for(auto gap = gaps.rbegin(); gap != gaps.rend(); ++gap)
    {
        if (*gap < dist)
        {
            for (llong index = 0; index < *gap; ++index)
            {
                for (auto it = left + index + *gap; it < right; it += *gap)
                {
                    for (auto rt = it; rt >= left + *gap && *rt < *(rt - *gap); rt -= *gap)
                        swap(*rt, *(rt - *gap));
                }
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
    if (dist >= 2)
    {
        auto pivot = getPivot(left, right);
        swap(*pivot, *(right - 1));
        pivot = right - 1;
        auto ins_it = left;
        for(auto it = left; it!=right - 1; ++it)
        {
            if (*it <= *pivot)
            {
                swap(*ins_it, *it);
                ++ins_it;
            }
        }
        swap(*ins_it, *pivot);

        sort(left, ins_it);
        sort( ins_it + 1, right);
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

template <llong nr_buck>
const void Bucket<nr_buck>::sort(vector<llong>::iterator left, vector<llong>::iterator right)
{
    vector<vector<llong>> buckets(nr_buck);
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
        if(!bucket.empty())
    		salg->sort(bucket);
    }

	auto jt = left;
	for (auto& bucket : buckets)
		for (auto& nr : bucket)
			*jt++ = nr;
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
    //sorts.push_back(&stls);
    //sorts.push_back(&merges);
    //sorts.push_back(&quicks3);
    //sorts.push_back(&quicksr);
    //sorts.push_back(&quicksm);
    //sorts.push_back(&quicksf);
    //sorts.push_back(&quicksl);
    //sorts.push_back(&countings);
    //sorts.push_back(&radixs16);
    //sorts.push_back(&radixsb);
    //sorts.push_back(&bucketsi);
    //sorts.push_back(&bucketss);
    //sorts.push_back(&bucketsm);
    //sorts.push_back(&bucketsq);
    //sorts.push_back(&shells2);
    sorts.push_back(&shellsec);
    sorts.push_back(&shellst);
    sorts.push_back(&shellsk);
    //sorts.push_back(&bubbles);
    //sorts.push_back(&insertions);
    //sorts.push_back(&selections);

    llong n_tests;

    ifstream in("Tests.txt");

    in >> n_tests;
    vector<tuple<string,llong,llong>> tests(n_tests);
    for (auto it = tests.begin(); it != tests.end(); ++it)
    {
        string type;
        llong size;
        llong max;
        in >> type >> size >> max;
        *it = tie(type, size, max);

    }

    in.close();

    ofstream out("Results.txt");
    random_device s_gen;

    auto gen = default_random_engine(s_gen());

    for (auto& test : tests)
    {
        string type = get<0>(test);
        llong size = get<1>(test);
        llong max = get<2>(test);
        vector<llong> v_test = generate_test(gen,type, size, max);
        out <<"Test type: "<<type << ", Test size: " << size << ", Max Value: " << max << endl << endl;
        for (auto& sort : sorts)
        {
            auto v = v_test;
            //print_vect(v);
            auto beg = chrono::high_resolution_clock::now();
            sort->sort(v);
            auto end = chrono::high_resolution_clock::now();
            //print_vect(v);
            chrono::duration<double> time = end - beg;
            out << sort->name << ": " << time.count() << "s Sorted: " << ((is_sorted(v) == 1) ? "yes\n" : "no\n")<<endl;
        }
        out << endl;
    }
    return 0;

}

