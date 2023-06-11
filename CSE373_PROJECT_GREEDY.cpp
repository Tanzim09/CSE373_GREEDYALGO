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

const int MAX_N = 2000;
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

// Compute the TSP tour length using the Nearest Neighbor algorithm
int tsp_greedy(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<bool> visited(n, false);
    visited[0] = true;
    int current = 0;
    int tour_length = 0;

    for (int i = 0; i < n - 1; i++) {
        int next = -1;
        int min_dist = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[current][j] < min_dist) {
                min_dist = dist[current][j];
                next = j;
            }
        }
        tour_length += min_dist;
        visited[next] = true;
        current = next;
    }
    tour_length += dist[current][0]; // Return to the starting city

    return tour_length;
}

int main() {
    srand(time(NULL));
    ofstream fout("tsp_data_GREEDY.txt");
    fout << "n,time" << endl;
    for (int i = 0; i < 2000; i++) {
        int n = random_int(3, MAX_N); // NUMBER OF CITY LET SAY 5
        vector<vector<int>> dist = generate_tsp(n); // A n x n MATRIX IS RETURNED NAMED 'dist'.
        auto start_time = high_resolution_clock::now(); // CLOCK STARTS
        int tour_length = tsp_greedy(dist); // PROBLEM SOLVER
        auto end_time = high_resolution_clock::now();  // CLOCK ENDS
        auto duration = duration_cast<microseconds>(end_time - start_time).count(); // TIME
        fout << n << "," << duration << endl; // STORED IN TXT FILE
    }
    fout.close();
    return 0;
}





