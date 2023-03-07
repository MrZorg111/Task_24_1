#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

struct data {
    std::string name = " ";
    int begin_job = 0;
    int end_job = 0;
};

int main() {
    std::vector<data> data_job;
    std::string command, job;
    int i = -1;

    do {
        std::cout << "Enter the command (begin/end/status/exit):";
        std::cin >> command;
        if (command == "begin") {
            i++;
            data_job.resize(i);
            if (data_job.empty()) {
                data_job.push_back(data());
                std::cout << "Enter the name of the task:";
                std::cin >> job;
                std::time_t t = std::time(nullptr);
                data_job[i].name = job;
                data_job[i].begin_job = t;
            }
            else {
                data_job.push_back(data());
                if (data_job[i - 1].end_job == 0) {
                    std::time_t t_end = std::time(nullptr);
                    data_job[i - 1].end_job = t_end;
                }
                std::cout << "Enter the name of the task:";
                std::cin >> job;
                std::time_t t_start = std::time(nullptr);
                data_job[i].name = job;
                data_job[i].begin_job = t_start;
            }
        }
        else if (command == "end" ) {
           std::time_t t_end = std::time(nullptr);
           data_job[i].end_job = t_end;
        }
        else if (command == "status" ) {
            if (data_job.empty()) {
                std::cout << "There are no completed and ongoing tasks!\n";
            }
            else {
                for (int l = 0; l < data_job.size(); l++) {
                    if (data_job[l].end_job != 0) {
                        std::time_t stat = std::difftime(data_job[l].end_job, data_job[l].begin_job);
                        std::tm local = *std::localtime(&stat);
                        std::cout << "To complete the task " << data_job[l].name << " spent "
                                  << std::put_time(&local, "%M:%S") << "\n";
                    }
                    else {
                        std::cout << "Current task:" << data_job[l].name << "\n";
                    }

                }
            }
        }
    }while (command != "exit");

    return 0;
}
