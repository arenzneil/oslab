#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string>

void print_table_header() {
    std::cout << std::string(80, '=') << std::endl;
    std::cout << std::left << std::setw(15) << "Child Process"
        << std::setw(15) << "PID"
        << std::setw(20) << "Parent PID"
        << std::setw(30) << "Status" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
}

void print_table_row(const std::string& child_name, pid_t pid, const std::string& status) {
std::cout << std::left << std::setw(15) << child_name
<< std::setw(15) << pid
<< std::setw(20) << getppid()
<< std::setw(30) << status << std::endl;
}

void custom_wait(std::vector<pid_t>& child_pids) {
int status;
std::cout << "\n" << std::string(80, '-') << std::endl;
std::cout << std::left << std::setw(15) << "Child Process"
<< std::setw(15) << "PID"
<< std::setw(20) << "Exit/Signal"
<< std::setw(30) << "Exit Status" << std::endl;
std::cout << std::string(80, '-') << std::endl;

for (int i = 0; i < child_pids.size(); i++) {
pid_t pid = child_pids[i];
waitpid(pid, &status, 0);

std::string status_msg;
if (WIFEXITED(status)) {
status_msg = "Exited with status " + std::to_string(WEXITSTATUS(status));
} else if (WIFSIGNALED(status)) {
status_msg = "Terminated by signal " + std::to_string(WTERMSIG(status));
} else {
status_msg = "Did not terminate normally";
}

std::string child_name = "Child " + std::to_string(i + 1);
std::cout << std::left << std::setw(15) << child_name
<< std::setw(15) << pid
<< std::setw(20) << (WIFEXITED(status) ? "Exit" : "Signal")
<< std::setw(30) << status_msg << std::endl;
}
std::cout << std::string(80, '=') << std::endl;
}

int main() {
pid_t pid1, pid2, pid3;
std::vector<pid_t> child_pids;

print_table_header();

pid1 = fork();
if (pid1 == 0) {
print_table_row("Child 1", getpid(), "Running");
exit(0);
} else if (pid1 > 0) {
child_pids.push_back(pid1);
pid2 = fork();
if (pid2 == 0) {
print_table_row("Child 2", getpid(), "Running");
exit(0);
} else if (pid2 > 0) {
child_pids.push_back(pid2);

pid3 = fork();
if (pid3 == 0) {
print_table_row("Child 3", getpid(), "Running");
exit(0);
} else if (pid3 > 0) {
child_pids.push_back(pid3);
std::cout << std::string(80, '=') << std::endl;

custom_wait(child_pids);

std::cout << "\nParent: All child processes have finished." << std::endl;
} else {
std::cerr << "Fork failed!" << std::endl;
exit(1);
}
}
} else {
std::cerr << "Fork failed!" << std::endl;
exit(1);
}

return 0;
}