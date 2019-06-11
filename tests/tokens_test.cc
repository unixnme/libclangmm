#include "clangmm.h"
#include <cassert>
#include <string>
#include <iostream>

int main() {
    std::string tests_path = LIBCLANGMM_TESTS_PATH;
    std::string path(tests_path + "/case/main.cpp");

    auto index = std::make_shared<clangmm::Index>(0, 0);

    clangmm::TranslationUnit tu(index, path, {});

    auto tokens = tu.get_tokens(0, 113);
    for (const auto &token : *tokens) {
        const auto& offset = token.get_source_location().get_offset();
        std::cout << token.get_spelling() << "\t" << offset.line << "\t" << offset.index << std::endl;
    }
}
