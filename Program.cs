using System;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        // 1. Print the current Process ID
        int currentPid = Process.GetCurrentProcess().Id;
        Console.WriteLine($"Process ID is: {currentPid}");

        // 2. Set up the child process (whoami)
        ProcessStartInfo startInfo = new ProcessStartInfo
        {
            FileName = "whoami",
            RedirectStandardOutput = true, // We want to capture what it prints
            UseShellExecute = false,
            CreateNoWindow = true
        };

        try
        {
            // 3. Start the process
            using (Process childProcess = Process.Start(startInfo))
            {
                // 4. Read the output from the child process
                string output = childProcess.StandardOutput.ReadToEnd();
                
                // 5. Wait for the child to finish (similar to wait() in C)
                childProcess.WaitForExit();

                // 6. Print the result
                Console.Write(output);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}