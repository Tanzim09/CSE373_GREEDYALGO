
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

// Define the struct City to store the coordinates of a city
struct City {
    int x;
    int y;
};

// Define the function to calculate the distance between two cities
double distance(City a, City b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

// Define the function to generate a random instance of TSP with n cities
vector<City> generateTSP(int n) {
    // Set up a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100); // assume the cities are within a 100x100 square

    // Generate n random cities
    vector<City> cities(n);
    for (int i = 0; i < n; i++) {
        cities[i].x = dist(gen);
        cities[i].y = dist(gen);
    }

    return cities;
}

// Define the function to solve TSP using brute force algorithm
double solveTSP(vector<City> cities) {
    // Initialize the variables
    int n = cities.size();
    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    double minDist = numeric_limits<double>::max();

    // Calculate the distance for every permutation of cities
    do {
        double dist = 0;
        for (int i = 0; i < n - 1; i++) {
            dist += distance(cities[perm[i]], cities[perm[i + 1]]);
        }
        dist += distance(cities[perm[n - 1]], cities[perm[0]]); // add the distance from the last city back to the first city
        minDist = min(minDist, dist);
    } while (next_permutation(perm.begin(), perm.end()));

    return minDist;
}

int main() {
    // Set up the file stream
    ofstream fout("output.txt");

    // Set up a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, 10); // assume there are at least 2 cities and at most 10 cities

    // Repeat the process for 100 times with a random number of cities
    for (int i = 0; i < 100; i++) {
        int n = dist(gen);
        vector<City> cities = generateTSP(n);

        // Solve TSP using brute force algorithm and measure the time taken
        auto start = chrono::steady_clock::now();
        double minDist = solveTSP(cities);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;

        // Save the data to file
        fout << n << " " << chrono::duration<double, milli>(diff).count() << endl;
    }

    fout.close();

    return 0;
}









