#include <algorithm>
#include <future>
#include <iostream>
#include <math.h>
#include <thread>
#include <vector>

const auto CORE_COUNT = std::thread::hardware_concurrency();

using namespace std;

vector<int> primes_in_range(int start, int end);
inline bool isPrime(int num);
inline int reverse(int num);
inline bool isEmirp(int num);
vector<int> find_emirps(vector<int> source_primes, bool multithreaded = true);
vector<int> primes_in_range(int start, int end);
vector<int> check_primes;

inline bool isPrime(int num)
{
    if (num == 1) {
        return false;
    }
    if (num < 4) {
        return true;
    }
    // If primes list is not passed to the function, generate them
    int num_sqrt = sqrt(num);
    if (check_primes.size() == 0 || check_primes.back() < num_sqrt) {
        check_primes = primes_in_range(0, num_sqrt);
    }
    for (int i = 0; i < check_primes.size(); i++) {
        // Stop when we reach the square root of number
        if (check_primes[i] > num_sqrt)
            break;
        if (num % check_primes[i] == 0)
            return false;
    }
    return true;
}

// Reverses a number, eg. 586 --> 685
inline int reverse(int num)
{
    int remainder = 0, reversed_number = 0;
    while (num != 0) {
        remainder = num % 10;
        reversed_number = reversed_number * 10 + remainder;
        num /= 10;
    }
    return reversed_number;
}

inline bool isEmirp(int num)
{
    return isPrime(reverse(num));
}

vector<int> primes_in_range(int start, int end)
{
    vector<int> primes;
    if (start <= 2) {
        vector<bool> sieve(end + 1, true);
        for (int i = 4; i < sieve.size(); i += 2) {
            sieve[i] = false;
        }
        for (int i = 9; i < sieve.size(); i += 6) {
            sieve[i] = false;
        }
        sieve[0] = sieve[1] = false;
        for (int i = 5; i <= sqrt(end); i += 2) {
            if (sieve[i]) {
                for (int j = pow<int, int>(i, 2); j < sieve.size(); j += i * 2) {
                    sieve[j] = false;
                }
            }
        }
        primes.insert(primes.end(), 2);
        for (int i = 3; i < sieve.size(); i += 2) {
            if (sieve[i]) {
                primes.insert(primes.end(), i);
            }
        }
    } else {
        int count = end - start + 1;
        vector<bool> sieve(count, true);
        for (int i = start % 2; i < sieve.size(); i += 2) {
            sieve[i] = false;
        }
        vector<int> primes_until_sqrt = primes_in_range(0, sqrt(end));
        for (int i = 1; i < primes_until_sqrt.size(); i++) {
            for (int j = ceil(static_cast<double>(start) / primes_until_sqrt[i]); j <= end / primes_until_sqrt[i]; j++) {
                sieve[(primes_until_sqrt[i] * j) - start] = false;
            }
        }
        for (int i = !(start % 2); i < sieve.size(); i += 2) {
            if (sieve[i]) {
                primes.insert(primes.end(), i + start);
            }
        }
        int x = sieve.size();
        int y = primes.size();
    }
    return primes;
}

vector<int> find_emirps(vector<int> source_primes, bool multithreaded)
{
    vector<int> emirps;
    // If the vector is worth multi-threading
    if (multithreaded && source_primes.size() > 100) {
        // Futures vector
        vector<future<vector<int>>> futures;
        // Segments of the primes. Each segment will be calculated by 1 thread
        vector<vector<int>> primes_ranges;
        int range_index = 0;
        // Number of elments in each segment, segments smaller than 100 are not worth it
        int division_size = max<int>(100, source_primes.size() / CORE_COUNT);
        // Create the prime numbers segment and start the threads
        for (int start_index = 0; start_index < source_primes.size(); start_index++) {
            // Each range starts from i to 1 less than the next segment
            int end_index = min<int>(source_primes.size() - 1, start_index + division_size - 1);
            vector<int> subdivision(source_primes.begin() + start_index, source_primes.begin() + end_index + 1);
            start_index = end_index;
            futures.insert(futures.end(), async(find_emirps, subdivision, false));
        }
        // Get thread results
        for (auto& f : futures) {
            auto result = f.get();
            emirps.insert(emirps.end(), result.begin(), result.end());
        }
        // Sort the array, since threads do not work by order
        sort(emirps.begin(), emirps.end());
        return emirps;
    }

    // Check for all emirps inside an array of primes
    for (int prime : source_primes) {
        if (isEmirp(prime)) {
            emirps.insert(emirps.end(), prime);
        }
    }
    return emirps;
}

int main(int argc, char* argv[])
{
    int N = 0;
     cout << "Enter N: ";
     cin >> N;
    //auto primes = primes_in_range(0, N);
    // for (auto prime : primes) {
    // cout << prime << endl;
    //}

    // Approximately how many primes we need to find to get N emirps
    int primesN = N * log10(N);

    // Approximately, we need to find primes less than this to get N emirps
    int limit = (log(primesN) + 1) * primesN;

    vector<int> primes = primes_in_range(0, limit);
    check_primes = primes;
    vector<int> emirps = find_emirps(primes);

    // If we still don't have enough emirps, generate from limit + 1 to 2 * limit
    // and then from 2 * limit to 3 * limit and so on until we have N emirps
    for (float i = 1; emirps.size() < N; i += 0.1) {
        primes = primes_in_range(limit * i + 1, limit * (i + 0.1));
        auto new_emirps = find_emirps(primes);
        emirps.insert(emirps.end(), new_emirps.begin(), new_emirps.end());
    }

    cout << N << "th emirp is: " << emirps[N - 1] << endl;
    return 0;
}
