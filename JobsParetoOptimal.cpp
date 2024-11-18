#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#define INT_MAX numeric_limits<int>::max();

using namespace std;

// Define a structure for a job (point) with two objectives
struct Job {
    int f1; // Processing time
    int f2; // Rejection cost

    Job(int p, int r) : f1(p), f2(r) {}
};

// Function to merge two Pareto fronts
vector<Job> mergeParetoFronts(const vector<Job>& left, const vector<Job>& right) {
    vector<Job> merged;
    int minF2 = INT_MAX;

    // Add all points from the left Pareto front
    for (const auto& job : left) {
        merged.push_back(job);
        minF2 = min(minF2, job.f2); // Track the minimum f2 in the left front
    }

    // Add points from the right Pareto front if they are not dominated
    for (const auto& job : right) {
        if (job.f2 < minF2) {
            merged.push_back(job);
            minF2 = min(minF2, job.f2); // Update the minimum f2
        }
    }

    return merged;
}

// Recursive function to compute the Pareto front
vector<Job> computeParetoFront(vector<Job>& jobs, int start, int end) {
    // Base case: Single job is always non-dominated
    if (start == end) {
        return {jobs[start]};
    }

    // Divide the jobs into two halves
    int mid = (start + end) / 2;

    // Recursively compute Pareto fronts for left and right halves
    vector<Job> leftFront = computeParetoFront(jobs, start, mid);
    vector<Job> rightFront = computeParetoFront(jobs, mid + 1, end);

    // Merge the two Pareto fronts
    return mergeParetoFronts(leftFront, rightFront);
}

int main() {
    // Input: List of jobs with their processing times and rejection costs
    vector<Job> jobs = {
        {30, 4}, {20, 3}, {40, 1}, {25, 2}, {35, 5},
        {45, 6}, {15, 3}, {50, 7}, {50, 1}, {200, 3}
    };

    // Step 1: Sort jobs by the first objective (processing time)
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.f1 < b.f1; // Ascending order by f1
    });

    // Step 2: Compute the Pareto front using the b=2 algorithm
    vector<Job> paretoFront = computeParetoFront(jobs, 0, jobs.size() - 1);

    // Output the Pareto front
    cout << "Pareto Front:" << endl;
    for (const auto& job : paretoFront) {
        cout << "(" << job.f1 << ", " << job.f2 << ")" << endl;
    }

    return 0;
}
