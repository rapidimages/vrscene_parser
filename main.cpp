#include <iostream>
#include <fstream>
#include <chrono>
#include "vrscene_parser.h"


using namespace std::chrono;
static auto current_time() {
    return duration_cast<microseconds>(system_clock::now().time_since_epoch());
}

int main(int, char** argv) {
    auto file_start = current_time();
    std::ifstream ifs (argv[1], std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();
    auto file_dur = current_time() - file_start;
    auto parse_start = current_time();

    if(auto scene = vrp::parse_vrscene(str); scene) {
        auto vrscene = *scene;
        auto parse_dur = current_time() - parse_start;

        std::cout << "SUCCESS " << std::endl;
        std::cout << "File reading: " << (file_dur.count() / 1000.0f) << " ms\n";
        std::cout << "Parsing: " << (parse_dur.count() / 1000.0f) << " ms\n";

        for(auto&& c : vrscene.comments) {
            std::cout << c;
        }

        for(auto&& i : vrscene.includes) {
            std::cout << i;
        }

        auto i = 0;
        for(auto&& p : vrscene.plugins) {
            if(i++ >= 10) break;
            std::cout << p << std::endl;
        }
    }
    return 0;
}
