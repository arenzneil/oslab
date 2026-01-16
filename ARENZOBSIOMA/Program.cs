using System;

class FCFS {
static void Main() {
int[] bt = new int[20];
int[] wt = new int[20];
int[] tat = new int[20];
int n;
float wtavg = 0.0f, tatavg = 0.0f;

Console.Write("\nEnter the number of processes: ");
n = int.Parse(Console.ReadLine());

for (int i = 0; i < n; i++) {
Console.Write("Enter Burst Time for Process {0}: ", i + 1);
bt[i] = int.Parse(Console.ReadLine());
}

wt[0] = 0;
tat[0] = bt[0];

for (int i = 1; i < n; i++) {
wt[i] = wt[i - 1] + bt[i - 1];
tat[i] = wt[i] + bt[i];
wtavg += wt[i];
tatavg += tat[i];
}

Console.WriteLine("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
for (int i = 0; i < n; i++) {
Console.WriteLine("P{0}\t\t{1}\t\t{2}\t\t{3}", i + 1, bt[i], wt[i], tat[i]);
}

Console.WriteLine("\nAverage Waiting Time: {0:F2}", wtavg / n);
Console.WriteLine("Average Turnaround Time: {0:F2}", tatavg / n);
}
}