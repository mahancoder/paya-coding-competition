#include <algorithm>
#include <future>
#include <iostream>
#include <math.h>
#include <thread>
#include <vector>

using namespace std;

const auto CORE_COUNT = std::thread::hardware_concurrency();

inline bool isPrime(int num);
inline int reverse(int num);
inline bool isEmirp(int num);
vector<int> find_emirps(vector<int>& source_primes, bool multithreaded = true);
vector<int> primes_in_range(int start, int end, bool multithreaded = true);

// A global vector of primes, so that we don't have to regenerate primes every time we use some functions
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
            // Add 2 as a prime (so we can still all evens in the next loop)
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
                for (int j = ceil(static_cast<double>(start) / primes_until_sqrt[i]); j <= end / primes_until_sqrt[i]; j++) {
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

vector<int> find_emirps(vector<int>& source_primes, bool multithreaded)
{
    vector<int> emirps;
    // If the vector is worth multi-threading
    if (multithreaded && source_primes.size() > 100) {
        // Futures vector
        vector<future<vector<int>>> futures;
        // Keep a reference of subdivision vectors on the heap
        vector<vector<int>*> subdivisions;
        // Number of elments in each segment, segments smaller than 100 are not worth it
        int division_size = max<int>(100, source_primes.size() / CORE_COUNT);
        // Create the prime numbers segment and start the threads
        for (int start_index = 0; start_index < source_primes.size(); start_index++) {
            // Each range starts from i to 1 less than the next segment
            int end_index = min<int>(source_primes.size() - 1, start_index + division_size - 1);
            vector<int>* subdivision = new vector<int>(source_primes.begin() + start_index, source_primes.begin() + end_index + 1);
            subdivisions.insert(subdivisions.end(), subdivision);
            start_index = end_index;
            futures.insert(futures.end(), async(find_emirps, ref(*subdivision), false));
        }
        // Get thread results
        for (auto& f : futures) {
            auto result = f.get();
            emirps.insert(emirps.end(), result.begin(), result.end());
        }
        // Delete subdivision vectors from the heap
        for (auto sub : subdivisions) {
            delete sub;
        }
        // Sort the array, since threads do not work by order
        sort(emirps.begin(), emirps.end());
    } else {

        // Check for all emirps inside an array of primes
        for (int prime : source_primes) {
            if (isEmirp(prime)) {
                emirps.insert(emirps.end(), prime);
            }
        }
    }
    return emirps;
}

int main(int argc, char* argv[])
{

    int N = 0;
    cout << "N ra vared konid: ";
    cin >> N;

    // Value gaurds
    if (N < 1) {
        cout << "N na motabar!" << endl;
        return -1;
    }
    if (N == 1 || N == 2 || N == 3) {
        cout << N << "-omin adad double aval " << (N < 3 ? N + 1 : 5) << " mibashad" << endl;
        return 0;
    }

    // Approximately how many primes we need to find to get N emirps
    int primesN = N * log10(N);

    // Approximately, we need to find primes less than this to get N emirps
    int limit = (log(primesN) + 1) * primesN;

    // Generate primes upto limit
    vector<int> primes = primes_in_range(0, limit);
    // Set the global primes
    check_primes = primes;
    // Find the emirps inside primes
    vector<int> emirps = find_emirps(primes);

    // If we still don't have enough emirps, generate from limit + 1 to 2 * limit
    // and then from 2 * limit to 3 * limit and so on until we have N emirps
    for (float i = 1; emirps.size() < N; i += 0.1) {
        primes = primes_in_range(limit * i + 1, limit * (i + 0.1));
        auto new_emirps = find_emirps(primes);
        emirps.insert(emirps.end(), new_emirps.begin(), new_emirps.end());
    }

    cout << N << "-omin adad double aval " << emirps[N - 1] << " mibashad" << endl;
    return 0;
}
