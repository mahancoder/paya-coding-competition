#include <algorithm>
#include <future>
#include <iostream>
#include <math.h>
#include <numeric>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

const auto CORE_COUNT = thread::hardware_concurrency();

vector<int> primes_in_range(int start, int end, bool multithreaded = true);

// {num: exponent}
unordered_map<int, int> prime_factors(int n)
{
    unordered_map<int, int> map;
    int factor = 2;
    while (n > 1) {
        if (n % factor == 0) {
            if (map.find(factor) != map.end())
                map[factor]++;
            else
                map[factor] = 1;
            n /= factor;
        } else
            factor++;
    }
    return map;
}

// Find all the primes from start to end (containing both start and end if they are prime)
vector<int> primes_in_range(int start, int end, bool multithreaded)
{
    vector<int> primes;
    // Do multi-threading if its worth it
    if (multithreaded && end - start > 1000) {
        int count = end - start + 1;
        vector<future<vector<int>>> futures;
        // Division size minimum is 100
        int division_size = max<int>(100, count / CORE_COUNT);
        // Start the different threads, calculating different divisions of primes
        for (int s = start; s <= end; s++) {
            int e = min<int>(s + division_size, end);
            futures.insert(futures.end(), async(primes_in_range, s, e, false));
            s = e;
        }
        // Get the thread results and append them to the list of primes
        for (auto& f : futures) {
            auto result = f.get();
            primes.insert(primes.end(), result.begin(), result.end());
        }
        // Sort the primes because threads don't respect order
        sort(primes.begin(), primes.end());

    } else {
        // If we are doing classical sieve (starting from 0)
        if (start <= 2) {
            // The sieve bool array
            vector<bool> sieve(end + 1, true);
            // Remove even numbers except 2
            for (int i = 4; i < sieve.size(); i += 2) {
                sieve[i] = false;
            }
            // Remove multiples of 3 except 3 itself
            for (int i = 9; i < sieve.size(); i += 6) {
                sieve[i] = false;
            }
            // 0 and 1 are not prime
            sieve[0] = sieve[1] = false;
            // For each odd number less than sqrt(end) starting from 5 (2 and 3 are already done)...
            for (int i = 5; i <= sqrt(end); i += 2) {
                // If i is prime
                if (sieve[i]) {
                    // Start from i^2 and remove all multiples of i (auto skipping even numbers)
                    for (int j = pow<int, int>(i, 2); j < sieve.size(); j += i * 2) {
                        sieve[j] = false;
                    }
                }
            }
            // Add 2 as a prime (so we can skip all evens in the next loop)
            primes.insert(primes.end(), 2);
            // Add all primes (skipping even numbers, and 2 is already added) to the primes vector
            for (int i = 3; i < sieve.size(); i += 2) {
                if (sieve[i]) {
                    primes.insert(primes.end(), i);
                }
            }
        } else {
            // Segmented sieve
            int count = end - start + 1;
            // The sieve array (offset by start, meaning sieve[0] is the start and sieve.back() is the end)
            vector<bool> sieve(count, true);
            // Remove even numbers
            for (int i = start % 2; i < sieve.size(); i += 2) {
                sieve[i] = false;
            }
            // Calculate primes before sqrt(end)
            vector<int> primes_until_sqrt = primes_in_range(0, sqrt(end));
            // For all the primes except 2 (even numbers are already removed)...
            for (int i = 1; i < primes_until_sqrt.size(); i++) {
                // Remove all the multiples of this prime
                for (int j = max<int>(ceil(static_cast<double>(start) / primes_until_sqrt[i]), primes_until_sqrt[i]);
                     j <= end / primes_until_sqrt[i]; j++) {
                    sieve[(primes_until_sqrt[i] * j) - start] = false;
                }
            }
            // Add all the primes (auto skipping evens)
            for (int i = !(start % 2); i < sieve.size(); i += 2) {
                if (sieve[i]) {
                    primes.insert(primes.end(), i + start);
                }
            }
        }
    }
    // Primes array now has all the primes from start and end
    return primes;
}

int no_expo(int n)
{
    vector<int> nums;
    vector<int> primes = primes_in_range(0, (log(n) + 1) * n);
    int smallest_prime = primes[0];
    int next_smallest = primes[1];
    for (int i = 0; i < primes.size(); i++) {
        if (primes[i] * primes[i + 1] > primes.back())
            break;
        for (int j = i + 1; j < primes.size(); j++) {
            if (primes[i] * primes[j] < primes.back()) {
                nums.insert(nums.end(), primes[i] * primes[j]);
            } else
                break;
        }
    }
    nums.insert(nums.end(), primes.begin(), primes.end());
    sort(nums.begin(), nums.end());
    return nums[n - 1];
}

int lot_expo(int n)
{
    int lot_count = 1;
    int no_count = 0;
    for (int i = 2; i < n; i++)
    {
        bool lot = true;
        bool no = true;
        for(auto d : prime_factors(i))
        {
            if (d.second < 2)
            {
                lot = false;
            }
            if (d.second > 1)
            {
                no = false;
            }
        }
        lot_count += lot;
        no_count += no;
    }
    cout << lot_count << " lots and " << no_count << " no" << endl;
}

int main(int argc, char* argv[])
{
    int n;
    cout << "n ra vared konid: ";
    cin >> n;
    cout << endl;
    cout << n << "-omin adad bi tavan " << no_expo(n) << " mibashad" << endl;
    cout << n << "-omin adad por tavan " << lot_expo(n) << " mibashad" << endl;
    return 0;
}
