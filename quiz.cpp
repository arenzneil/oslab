#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void findAverageTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // 1. Calculate Waiting Time
    // Waiting time for the first process is always 0
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    // 2. Calculate Turnaround Time
    // TAT = Burst Time + Waiting Time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    // Display results in a table
    cout << "--------------------------------------------------------------\n";
    cout << "Process   Burst Time   Waiting Time   Turnaround Time\n";
    cout << "----------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << "  P" << (i + 1) << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    // Calculate and display averages
    cout << "----------------------------------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << (float)total_wt / (float)n << endl;
    cout << "Average Turnaround Time: " << (float)total_tat / (float)n << endl;
}

int main() {
    // Process IDs
    int processes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(processes) / sizeof(processes[0]);

    // Burst times provided
    int burst_time[] = {3, 5, 4, 3, 2, 1, 0, 7, 8, 1};

    findAverageTime(processes, n, burst_time);

    return 0;
}