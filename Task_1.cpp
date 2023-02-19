#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>


int main() {
    std::string command, job = " ";
    std::time_t t;
    std::map<std::string, int> start;
    std::map<std::string, int> finish;
    do {
        std::cout << "Enter the command: ";
        std::cin >> command;
        if (command == "begin") {
            if (job == " ") {

                std::cout << "Enter the name of the task:";
                std::cin >> job;
                t = std::time(nullptr);
                start.insert(std::pair<std::string, int> (job, t));
            }
            else {
                std::time_t tf = std::time(nullptr);
                finish.insert(std::pair<std::string, int> (job, (int)difftime(tf, t)));
                std::cout << "Enter the name of the task:";
                std::cin >> job;
                std::time_t ts = std::time(nullptr);
                start.insert(std::pair<std::string, int> (job, ts));
            }
        }
        else if (command == "end") {
            if (job != " ") {
                std::time_t tfin = std::time(nullptr);
                finish.insert(std::pair<std::string, int> (job, (int)difftime(tfin, t)));
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
            for (std::map<std::string, int> :: iterator fin_j = finish.begin(); fin_j != finish.end(); fin_j++) {
                t = fin_j -> second;
                std::tm local = *localtime(&t);
                std::cout << "To complete the task " << fin_j -> first << " it was spent " << std::put_time(&local, "%M:%S") << "\n";
            }
        }
        else if (command != "exit") {
            std::cout << "Invalid code\n";
        }
    }while (command != "exit");
    return 0;
}
