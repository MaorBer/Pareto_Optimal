#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define INT_MAX numeric_limits<int>::max()

using namespace std;

// Structure representing a 2D vector with two objectives
struct Vector {
    int f1; // First objective
    int f2; // Second objective

    Vector(int a, int b) : f1(a), f2(b) {}
};

// Merges two Pareto fronts, retaining only non-dominated points
vector<Vector> mergeParetoFronts(const vector<Vector>& left, const vector<Vector>& right) {
    vector<Vector> merged;
    int minF2 = INT_MAX;

    // Include all points from the left Pareto front
    for (const auto& point : left) {
        merged.push_back(point);
        minF2 = min(minF2, point.f2);
    }

    // Include points from the right front if not dominated by the left front
    for (const auto& point : right) {
        if (point.f2 < minF2) {
            merged.push_back(point);
            minF2 = min(minF2, point.f2);
        }
    }

    return merged;
}

// Recursively computes the Pareto front using divide-and-conquer
vector<Vector> computeParetoFront(vector<Vector>& vectors, int start, int end) {
    if (start == end) {
        return {vectors[start]}; // Single point is always Pareto optimal
    }

    // Divide the dataset into two halves
    int mid = (start + end) / 2;

    // Compute Pareto fronts for the left and right halves
    vector<Vector> leftFront = computeParetoFront(vectors, start, mid);
    vector<Vector> rightFront = computeParetoFront(vectors, mid + 1, end);

    // Merge the two fronts into a single Pareto front
    return mergeParetoFronts(leftFront, rightFront);
}

int main() {
    // Input dataset represented as 2D vectors
    vector<Vector> vectors = {
        {30, 4}, {20, 3}, {40, 1}, {25, 2}, {35, 5},
        {45, 6}, {15, 3}, {50, 7}, {50, 1}, {200, 3}
    };

    // Sort the vectors based on the first objective (f1)
    sort(vectors.begin(), vectors.end(), [](const Vector& a, const Vector& b) {
        return a.f1 < b.f1;
    });

    // Compute the Pareto front
    vector<Vector> paretoFront = computeParetoFront(vectors, 0, vectors.size() - 1);

    // Output the Pareto front
    cout << "Pareto Front:" << endl;
    for (const auto& vec : paretoFront) {
        cout << "(" << vec.f1 << ", " << vec.f2 << ")" << endl;
    }

    return 0;
}
