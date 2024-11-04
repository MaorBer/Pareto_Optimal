#include <iostream>
#include <vector>
#include <fstream>  // Include this for ifstream
#include <limits>
using namespace std;



// Define a structure for the job
struct Job {
    int processingTime;
    int rejectionCost;

    Job(int p, int r) : processingTime(p), rejectionCost(r) {}
};

// Function to find the minimum processing time under the rejection cost constraint using DP
int findMinimumProcessingTimeDP(const vector<Job>& jobs, int U) {
    int n = jobs.size();

    // DP table where dp[i][c] represents the minimum processing time achievable with the first i jobs and rejection cost c
    vector<vector<int>> dp(n + 1, vector<int>(U + 1, numeric_limits<int>::max()));

    // Initialize dp[0][0] to 0 (no jobs, zero processing time, zero rejection cost)
    dp[0][0] = 0;

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        int p_i = jobs[i - 1].processingTime;
        int r_i = jobs[i - 1].rejectionCost;

        for (int c = 0; c <= U; ++c) {
            // Case 1: Include the job, keep the same rejection cost
            if (dp[i - 1][c] != numeric_limits<int>::max()) {
                dp[i][c] = min(dp[i][c], dp[i - 1][c] + p_i);
            }
            
            // Case 2: Exclude the job, add to rejection cost if within bounds
            if (c >= r_i && dp[i - 1][c - r_i] != numeric_limits<int>::max()) {
                dp[i][c] = min(dp[i][c], dp[i - 1][c - r_i]);
            }
        }
    }

    // Find the minimum processing time for rejection costs <= U
    int minProcessingTime = numeric_limits<int>::max();
    for (int c = 0; c <= U; ++c) {
        minProcessingTime = min(minProcessingTime, dp[n][c]);
    }

    return minProcessingTime == numeric_limits<int>::max() ? -1 : minProcessingTime;
}

int main() {
    // Define jobs with processing times and rejection costs
         ifstream inputFile("jobs.txt");
    vector<Job> jobs;
    int U;
    
    int p, r;
    while (inputFile >> p >> r) {
        jobs.push_back(Job(p, r));
    }

    inputFile.close();

    cout << "Enter the rejection cost limit (U): ";
    cin >> U;

    // Find and print the minimum processing time that meets the rejection cost constraint
    int result = findMinimumProcessingTimeDP(jobs, U);
    if (result != -1) {
        cout << "Minimum Processing Time: " << result << endl;
    } else {
        cout << "No feasible solution within the rejection cost constraint." << endl;
    }

    return 0;
}
