#include <iostream>
#include <iomanip>
using namespace std;

int main() {
const int n = 5;
float burstTime[n] = {50.54, 10.11, 33.34, 2.5, 101.1};
float remainingTime[n];
float waitingTime[n] = {0};
float turnaroundTime[n];

int timeQuantum = 20;
int time = 0;
bool done;

for (int i = 0; i < n; i++) {
remainingTime[i] = burstTime[i];
}

do {
done = true;
for (int i = 0; i < n; i++) {
if (remainingTime[i] > 0) {
done = false;

if (remainingTime[i] > timeQuantum) {
time += timeQuantum;
remainingTime[i] -= timeQuantum;
} else {
time += remainingTime[i];
waitingTime[i] = time - burstTime[i];
remainingTime[i] = 0;
}
}
}
} while (!done);

for (int i = 0; i < n; i++) {
turnaroundTime[i] = burstTime[i] + waitingTime[i];
}

float avgWT = 0, avgTAT = 0;

cout << "\n" << string(70, '=') << endl;
cout << left << setw(12) << "PROCESS"
<< setw(15) << "BURST TIME"
<< setw(18) << "WAITING TIME"
<< setw(18) << "TURNAROUND TIME" << endl;
cout << string(70, '=') << endl;

// Print table rows
for (int i = 0; i < n; i++) {
cout << left << setw(12) << ("P" + to_string(i + 1))
<< setw(15) << fixed << setprecision(2) << burstTime[i]
<< setw(18) << fixed << setprecision(2) << waitingTime[i]
<< setw(18) << fixed << setprecision(2) << turnaroundTime[i] << endl;

avgWT += waitingTime[i];
avgTAT += turnaroundTime[i];
}

cout << string(70, '=') << endl;
cout << fixed << setprecision(2);
cout << "\nAverage Waiting Time: " << avgWT / n << endl;
cout << "Average Turnaround Time: " << avgTAT / n << endl;
cout << string(70, '=') << endl;

return 0;
}