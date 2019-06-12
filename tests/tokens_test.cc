#include "clangmm.h"
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string slurp (const std::string& path) {
    std::ostringstream buf;
    std::ifstream input (path.c_str());
    buf << input.rdbuf();
    return buf.str();
}

std::vector<std::string> read_lines(const std::string &path) {
    std::ifstream ifs(path);
    std::vector<std::string> result;
    std::string line;
    while (std::getline(ifs, line)) {
        result.emplace_back(line);
    }
    return result;
}

int main() {
    std::string tests_path = LIBCLANGMM_TESTS_PATH;
    std::string path(tests_path + "/case/main.cpp");
    std::vector<std::string> lines{read_lines(path)};

    auto index = std::make_shared<clangmm::Index>(0, 0);
    clangmm::TranslationUnit tu(index, path, {});

    auto tokens = tu.get_tokens(0, 113);
    size_t prev_line = 0;
    size_t prev_pos = 0;
    for (const auto &token : *tokens) {
        const auto& offset = token.get_source_location().get_offset();
        const auto line = offset.line - 1;
        if (line > prev_line) {
            std::cout << lines[prev_line].substr(prev_pos, std::string::npos) << std::endl;
            prev_pos = 0;
        }
        const auto start = offset.index - 1;
        const auto len = token.get_spelling().size();
        std::cout << lines[line].substr(prev_pos, start - prev_pos);
        std::cout << lines[line].substr(start, len);
        prev_pos = start + len;
        prev_line = line;
    }
    std::cout << std::endl;
}
