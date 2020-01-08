/**********************************************************************************************************************
* virtual_iter:
* Iterator types for opaque sequence collections.
* Released under the terms of the MIT License:
* https://opensource.org/licenses/MIT
**********************************************************************************************************************/



#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <stdio.h>

#include "virtual_std_iter.h"

typedef std::chrono::high_resolution_clock::time_point hres_t;
typedef std::chrono::duration<size_t, std::ratio<1, 1000000> > duration_t; // micro-seconds.

int main()
{
    auto vec = std::vector<int> (10000000, 1);

    size_t result = 0;

    auto viItr = vec.begin ();
    auto viEndItr = vec.end ();
    hres_t viStart = std::chrono::high_resolution_clock::now ();

    for (; viItr != viEndItr; ++viItr)
    {
        result += *viItr;
    }

    hres_t viEnd = std::chrono::high_resolution_clock::now ();
    duration_t timespan = std::chrono::duration_cast<duration_t> (viEnd - viStart);
    std::cout << "result: " << result << std::endl;
    std::cout << "vector iterator timing: " << timespan.count () << std::endl;

    auto impl = virtual_iter::std_fwd_iter_impl<std::vector<int>::const_iterator, 48>();

    virtual_iter::fwd_iter<int, 48> itr (impl, vec.begin ());
    virtual_iter::fwd_iter<int, 48> endItr (impl, vec.end ());

    result = 0;
    hres_t fwdIterStart = std::chrono::high_resolution_clock::now ();

    /*
    while (itr != endItr)
    {
        result += *itr;
        ++itr;
    }
    */
    /*
    int v = 0;
    while(itr.iterate(v, endItr))
    {
        result += v;
    }
    */

    /*
    int results[2000];
    size_t numResults = 0;
    while ((numResults = itr.copy(results, 1999, endItr)) != 0)
    {
        result = std::accumulate(&results[0], &results[0 + numResults], result);
    }
    */

    // This is slower than copying out the results and doing the accumulate as a separate loop.
    // This is still running in half the time of an application of the standard iteration idiom.
    std::function<bool(const int&)> f = [&result](const int& a) {
        result += a;
        return true;
    };
    itr.visit (endItr, f);

    hres_t fwdIterEnd = std::chrono::high_resolution_clock::now ();
    timespan = std::chrono::duration_cast<duration_t> (fwdIterEnd - fwdIterStart);
    std::cout << "snapshot::iter timing: " << timespan.count () << std::endl;
    std::cout << "result: " << result << std::endl;

    return 0;
}

