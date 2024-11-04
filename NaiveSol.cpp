#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;


struct Job {
    int processingTime;
    int rejectionCost;

    Job(int p, int r) : processingTime(p), rejectionCost(r) {}
};


int findMinimumProcessingTime(const vector<Job>& jobs, int U) {
    int n = jobs.size();
    int minProcessingTime = numeric_limits<int>::max();

    // Iterate over all subsets using bit manipulation (2^n subsets) 
    // for example if there are 3 Jobs it will check all possible subsets
    for (int subset = 0; subset < (1 << n); ++subset) {
        int totalProcessingTime = 0;
        int totalRejectionCost = 0;

        // Calculate total processing time and rejection cost for the current subset
        for (int j = 0; j < n; ++j) {
            if (subset & (1 << j)) {
                // Include job j
                totalProcessingTime += jobs[j].processingTime;
            } else {
                // Exclude job j, add its rejection cost
                totalRejectionCost += jobs[j].rejectionCost;
            }
        }

        // rejection cost check
        if (totalRejectionCost <= U) {
            //check if lower and update
            minProcessingTime = min(minProcessingTime, totalProcessingTime);
        }
    }

    return minProcessingTime;
}

int main() {
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

    int result = findMinimumProcessingTime(jobs, U);
    cout << "Minimum Processing Time: " << result << endl;

    return 0;
}
