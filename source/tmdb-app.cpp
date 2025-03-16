#include "TMDB.hpp"

int main(int args, char* argc[]) {
    try {
       fmt::print("{}", strcmp(argc[1], "--type") == 0 ? GetResponse(argc[2]) : "look README file.");
    }
    catch(exception& msg) {
        cerr << msg.what();
    }
}