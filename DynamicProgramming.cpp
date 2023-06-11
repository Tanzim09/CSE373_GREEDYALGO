#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>

using namespace std;
using namespace std::chrono;

const int MAX_N = 20;
const int MAX_DIST = 1000;

// Generate a random number between min and max
int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Generate a random TSP problem with n cities
// Creating a 2D vector dist of size n x n and initializes all entries to 0.(5x5)
vector<vector<int>> generate_tsp(int n) {
    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int d = random_int(1, MAX_DIST); // DISTANCE BETWEEN EACH INDEX 1-1000
            dist[i][j] = dist[j][i] = d;    // (1-3) = (3-1)
        }
    }
    return dist; // RETURN A N X N 2D MATRIX NAMED 'dist'.
}

// Compute the optimal TSP tour using dynamic programming
int tsp_dp(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                for (int j = 0; j < n; j++) {
                    if (i != j && (mask & (1 << j))) {
                        dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + dist[j][i]);
                    }
                }
            }
        }
    }
    return dp[(1 << n) - 1][0];
}

int main() {
    srand(time(NULL));
    ofstream fout("tsp_data_DP.txt");
    fout << "n,time" << endl;
    for (int i = 0; i < 2000; i++) {
        int n = random_int(3, MAX_N); // NUMBER OF CITY LET SAY 5
        vector<vector<int>> dist = generate_tsp(n); // A n x n MATRIX IS RETURNED NAMED 'dist'.
        auto start_time = high_resolution_clock::now(); // CLOCK STARTS
        int tour_length = tsp_dp(dist); // PROBLEM SOLVER
        auto end_time = high_resolution_clock::now();  // CLOCK ENDS
        auto duration = duration_cast<microseconds>(end_time - start_time).count(); // TIME
        fout << n << "," << duration << endl; // STORED IN TXT FILE
    }
    fout.close();
    return 0;
}
