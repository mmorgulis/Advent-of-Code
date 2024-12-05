#include <iostream>
#include <fstream>
#include <vector>

int main () {
    int array[2];
    std::vector<int[2]> rules;
    std::vector<std::string> lists;
    std::string line;
    std::string::iterator it = line.begin();
    std::string substr1, substr2;
    std::ifstream ifs;
    ifs.open("input.txt");
    if (ifs.is_open()) {
        while (std::getline(ifs, line)) {
            if (line.empty())
                lists.push_back(line);
            for (auto c : line) {
                if (c == '|') {
                    substr1.append(line.begin(), it);
                    substr2.append(it+1, line.end());
                    array[0] = atoi(substr1.c_str());
                    array[1] = atoi(substr2.c_str());
                    //rules.push_back(array);
                }
                ++it;
            }
            it = line.begin();
            line.clear();
            substr1.clear();
            substr2.clear();
        }
    }



    return 0;
}