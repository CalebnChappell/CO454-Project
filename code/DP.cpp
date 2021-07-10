#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>


#ifndef _DP_H_
#define _DP_H_

class DP {
    std::vector<int> weights;
    std::vector<int> dueDates;
    std::vector<int> processingTimes;
    int size;
    int W;
    int P;
    std::vector<std::vector<int> > table;
    std::vector<std::vector<std::string> > path;

    // The DP if we iterate on sum of processing times
    void DPProc(int j, int a);

    // The DP if we iterate on sum of processing times
    void DPWeight(int j, int a);

    public:
    // Constructor
    DP(const std::vector<int> weights, const std::vector<int> dueDates, const std::vector<int> processingTimes);

    // Returns value at specified position in table
    int TableValue(int j, int a);

    // Returns value at specified position in pth
    std::string PathValue(int j, int a);

    // Returns the smaller of P and W
    int IterationVariable();

    // Determines DP table
    void P_j(int j, int a);

    // Returns the optimal value
    int Opt();
};



// Method definitions

// Constructor
DP::DP(const std::vector<int> w, const std::vector<int> d, const std::vector<int> p) {
    weights = w;
    dueDates = d;
    processingTimes = p;
    size = p.size();
    W = 0;
    P = 0;

    // Determining the sum of weights
    for(std::vector<int>::iterator it = weights.begin(); it != weights.end(); ++it) {
        W += *it;
    }
    
    // Determining the sum of processing times
    for(std::vector<int>::iterator it = processingTimes.begin(); it != processingTimes.end(); ++it) {
        P += *it;
    }

    // Initializng our table to store DP values
    int table_size = std::min(P, W);

    std::vector<std::vector<int> > table_temp(size, std::vector<int>(table_size, 0));
    table = table_temp;

    std::vector<std::vector<std::string> > path_temp(size, std::vector<std::string>(table_size, ""));
    path = path_temp;
}

// Returns value at specified position in table
int DP::TableValue(int j, int a) {
    return table[j][a];
}


// Returns value at specified position in path
std::string DP::PathValue(int j, int a) {
    return path[j][a];
}


// Returns the smaller of P and W
int DP::IterationVariable() {
    // If the sum of the processing times is smaller iterate over it
    if (P <= W) {
        return P;
    }
    // If the sum of the processing times is not smaller
    return W;
}


// The DP if we iterate on sum of processing times
void DP::DPProc(int j, int a) {
    // Determining if values are in the table
    int t_1;
    int t_2;
    if (j == 0) {
        if (a >= 0) {
            t_2 = 0 + weights[j];
        }
        if ((a - processingTimes[j]) >= 0) {
            t_1 = 0;
        }
    } else {
        if (a < 0) {
            t_2 = std::numeric_limits<int>::max();
        } else {
            t_2 = table[j - 1][a] + weights[j];
        }
        if ((a - processingTimes[j]) < 0) {
            t_1 = std::numeric_limits<int>::max();
        } else {
            t_1 = table[j - 1][a - processingTimes[j]];
        }
    }

    // DP
    if (0 <= a && a <= dueDates[j]) {
        // Determining the min value
        if (t_1 <= t_2) {
            table[j][a] = t_1;
        } else {
            table[j][a] = t_2;
        }
    } else if (dueDates[j] < a <= P) {
        table[j][a] = table[j][dueDates[j]];
    }
}


// The DP if we iterate on sum of processing times
void DP::DPWeight(int j, int a) {
    // Determining if values are in the table
    int t_1;
    int t_2;
    if (j == 0) {
        if (a == 0) {
            t_1 = 0;
        } else {
            t_1 = std::numeric_limits<int>::max();
        }
        if ((a - weights[j]) == 0) {
            t_2 = 0 + processingTimes[j];
        } else {
            t_2 = std::numeric_limits<int>::max();
        }
    } else {
        t_1 = table[j - 1][a];
        t_2 = table[j - 1][a - weights[j]] + processingTimes[j];
    }

    // DP
    if (t_2 <= dueDates[j]) {
        // Determining the min value
        if (t_1 <= t_2) {
            table[j][a] = t_1;
        } else {
            table[j][a] = t_2;
        }
    } else {
        table[j][a] = t_1;
    }
}


// Determines DP table
void DP::P_j(int j, int a) {
    // Determining which DP algo to use
    if (P <= W) {
        // If we are iterating over the sum of processing times
        this->DPProc(j, a);
    } else {
        // If we are iterating over the sum of weights
        this->DPWeight(j, a);
    }
}

// Returns the optimal value
int DP::Opt() {
    int opt_val = -1;
    // Determining which DP algo was used
    if (P <= W) {
        // If we are iterating over the sum of processing times
        opt_val = this->TableValue(size - 1, dueDates[size - 1]);
    } else {
        // If we are iterating over the sum of weights
        for(std::vector<int>::iterator it = this->table[size - 1].begin(); it != this->table[size - 1].end(); ++it) {
            if ((opt_val < *it) && (*it < std::numeric_limits<int>::max())) {
                opt_val = *it;
            }
        }
    }
    
    return opt_val;
}

#endif

