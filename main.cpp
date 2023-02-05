#include <iostream>
#include <string>
#include <map>
#include <ctime>

void time(int num, int& sec, int& min, int& hour) {
    if (num < 60) {
        sec = num, min = 0; hour = 0;
        num = -1;
    }
    for (int i = 0; num != -1; i++) {
        if (num >= 60) {
            min++;
            num -= 60;
            sec = num;
        }
        else if (min >= 60) {
            hour++;
            min -= 60;
        }
        else {
            num = -1;
        }
    }
}

int main() {
    int m = 0, h = 0, s = 0;
    std::string command, job = " ";
    std::map<std::string, int> start;
    std::map<std::string, int> finish;
    int count = 0;
    do {
        std::cout << "Enter the command: ";
        std::cin >> command;
        if (command == "begin") {
            if (job == " ") {

                std::cout << "Enter the name of the task:";
                std::cin >> job;
                std::time_t t = std::time(nullptr);
                start.insert(std::pair<std::string, int> ((std::to_string(count + 1) + ") " + job), t));
            }
            else {
                std::time_t tf = std::time(nullptr);
                finish.insert(std::pair<std::string, int> ((std::to_string(count) + ") " + job), tf));
                std::cout << "Enter the name of the task:";
                std::cin >> job;
                std::time_t ts = std::time(nullptr);
                start.insert(std::pair<std::string, int> ((std::to_string(count + 1) + ") " + job), ts));
            }
            count++;
        }
        else if (command == "end") {
            if (job != " ") {
                std::time_t tfin = std::time(nullptr);
                finish.insert(std::pair<std::string, int> ((std::to_string(count) + ") " + job), tfin));
                job = " ";
            }
        }
        else if (command == "status") {
            if (job != " ") {
                std::cout << "Task in execution: " << job << "\n";
            }
            else {
                std::cout << "There are no completed tasks!\n";
            }
            std::string name_task, t_f;
            for (std::map<std::string, int> :: iterator fin_j = finish.begin(); fin_j != finish.end(); fin_j++) {
                name_task = fin_j -> first;
                std::map<std::string, int> :: iterator start_j = start.find(name_task);
                int different = difftime(fin_j -> second, start_j -> second);
                time(different, s, m, h);
                std::cout << "The task is completed: " << fin_j -> first << " spent on execution: hour " << h << ", minutes " << m << ", second " << s << "\n";
                h = 0, m = 0, s = 0;
            }
        }
        else if (command != "exit") {
            std::cout << "Invalid code\n";
        }
    }while (command != "exit");
    return 0;
}
