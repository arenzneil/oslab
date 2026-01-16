#include <iostream>
#include <vector>
#include <algorithm> // Required for sort
#include <iomanip>   // Required for setprecision

using namespace std;

struct Process {
    int id;
    double burstTime;
    double waitingTime;
    double turnaroundTime;
};

// Comparator function to sort processes by burst time (SJF)
bool compareBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

int main() {
    // Input data
    vector<double> burstTimes = {50.54, 10.11, 33.34, 2.5, 101.1};
    int n = burstTimes.size();
    vector<Process> proc(n);

    // Initialize processes
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        proc[i].burstTime = burstTimes[i];
    }

    // Sort by Burst Time (SJF logic)
    sort(proc.begin(), proc.end(), compareBurstTime);

    // Calculate Waiting Time and Turnaround Time
    double totalWT = 0, totalTAT = 0;
    proc[0].waitingTime = 0; // First process doesn't wait

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            proc[i].waitingTime = proc[i-1].waitingTime + proc[i-1].burstTime;
        }
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
        
        totalWT += proc[i].waitingTime;
        totalTAT += proc[i].turnaroundTime;
    }

    // Output Results
    cout << fixed << setprecision(2);
    cout << "-------------------------------------------------------------\n";
    cout << "PID\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << proc[i].id << "\t" 
             << proc[i].burstTime << "\t\t" 
             << proc[i].waitingTime << "\t\t" 
             << proc[i].turnaroundTime << "\n";
    }
    cout << "-------------------------------------------------------------\n";
    cout << "Average Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    return 0;
}