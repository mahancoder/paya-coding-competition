#include <algorithm>
#include <future>
#include <iostream>
#include <math.h>
#include <numeric>
#include <thread>
#include <vector>

using namespace std;

const auto CORE_COUNT = std::thread::hardware_concurrency();

vector<int> primes_in_range(int start, int end, bool multithreaded = true, bool count = false);

// Returns all primes between start and end if count = false, else { count } of primes between start and end
vector<int> primes_in_range(int start, int end, bool multithreaded, bool count)
{
    vector<int> primes;
    // Do multi-threading if its worth it
    if (multithreaded && end - start > 1000) {
        int n = end - start + 1;
        vector<future<vector<int>>> futures;
        // Division size minimum is 100
        int division_size = max<int>(100, n / CORE_COUNT);
        // Start the different threads, calculating different divisions of primes
        for (int s = start; s <= end; s++) {
            int e = min<int>(s + division_size, end);
            if (s == start) {
                futures.insert(futures.end(), async(primes_in_range, s, e + 1, false, count));
            } else if (e == end) {

                futures.insert(futures.end(), async(primes_in_range, s - 1, e, false, count));
            } else {
                futures.insert(futures.end(), async(primes_in_range, s - 1, e + 1, false, count));
            }
            s = e;
        }
        if (count) {
            primes.insert(primes.end(), 0);
        }
        // Get the thread results and append them to the list of primes
        for (auto& f : futures) {
            auto result = f.get();
            if (count) {
                primes[0] += result[0];
            } else {
                primes.insert(primes.end(), result.begin(), result.end());
            }
        }
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
            if (count) {
                primes.insert(primes.end(), accumulate(sieve.begin(), sieve.end() - 1, (start == 2) ? -1 : 0));
            } else {
                if (start < 2) {
                    primes.insert(primes.end(), 2);
                }
                // Add all primes (skipping even numbers, and 2 is already added) to the primes vector
                for (int i = 3; i < sieve.size() - 1; i += 2) {
                    if (sieve[i]) {
                        primes.insert(primes.end(), i);
                    }
                }
            }
        } else {
            // Segmented sieve
            int n = end - start + 1;
            // The sieve array (offset by start, meaning sieve[0] is the start and sieve.back() is the end)
            vector<bool> sieve(n, true);
            // Remove even numbers
            for (int i = start % 2; i < sieve.size(); i += 2) {
                sieve[i] = false;
            }
            // Calculate primes before sqrt(end)
            vector<int> primes_until_sqrt = primes_in_range(0, sqrt(end) + 1);
            // For all the primes except 2 (even numbers are already removed)...
            for (int i = 1; i < primes_until_sqrt.size(); i++) {
                // Remove all the multiples of this prime
                for (int j = max<int>(ceil(static_cast<double>(start) / primes_until_sqrt[i]), primes_until_sqrt[i]); j <= end / primes_until_sqrt[i]; j++) {
                    sieve[(primes_until_sqrt[i] * j) - start] = false;
                }
            }
            if (count) {
                primes.insert(primes.end(), accumulate(sieve.begin() + 1, sieve.end() - 1, 0));
            } else {
                // Add all the primes (auto skipping evens)
                for (int i = (start % 2) + 1; i < sieve.size() - 1; i += 2) {
                    if (sieve[i]) {
                        primes.insert(primes.end(), i + start);
                    }
                }
            }
        }
    }
    return primes;
}
int main(int argc, char* argv[])
{
    int line_count;
    cout << "q ra vared konid: ";
    cin >> line_count;
    cout << endl;
    vector<int> counts(line_count);
    vector<vector<int>> start_end_pairs(line_count);
    // Ask for each line
    for (int i = 1; i <= line_count; i++) {
        start_end_pairs[i - 1] = vector<int>(2);
        cout << "Khat " << i << " ra vared konid: ";
        cin >> start_end_pairs[i - 1][0] >> start_end_pairs[i - 1][1];
        cout << endl;
    }
    // Calculate each line's primes
    for (auto pair : start_end_pairs) {
        cout << "Tedad adad aval bein " << pair[0] << " va " << pair[1] << ": " << primes_in_range(pair[0], pair[1], true, true)[0] << endl;
    }
    return 0;
}
