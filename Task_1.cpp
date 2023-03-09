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

    do {
        std::cout << "Enter the command (begin/end/status/exit):";
        std::cin >> command;
        if (command == "begin") {
            if (data_job.empty()) {
                data d;     // Очень хороший способ заполнять вектор, жаль что я сам не сообразил.
                std::cout << "Enter the name of the task:";
                std::cin >> job;
                std::time_t t = std::time(nullptr);
                d.name = job;
                d.begin_job = t;
                data_job.push_back(d);
            }
            else {
                if (data_job.back().end_job == 0) { // .back() и этот способ тоже обязательно запомню)
                    std::time_t t_end = std::time(nullptr);
                    data_job.back().end_job = t_end;
                }
                data_job.push_back(data());
                std::cout << "Enter the name of the task:";
                std::cin >> job;
                std::time_t t_start = std::time(nullptr);
                data_job.back().name = job;
                data_job.back().begin_job = t_start;
            }
        }
        else if (command == "end" ) {
           std::time_t t_end = std::time(nullptr);
           data_job.back().end_job = t_end;
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
