#ifndef TRANSLATIONUNIT_H_
#define TRANSLATIONUNIT_H_
#include "code_complete_results.h"
#include "cursor.h"
#include "diagnostic.h"
#include "index.h"
#include "tokens.h"
#include <clang-c/Index.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace clangmm {
  class TranslationUnit {
    std::shared_ptr<Index> index;

  public:
    TranslationUnit(std::shared_ptr<Index> index_, const std::string &file_path,
                    const std::vector<std::string> &command_line_args,
                    const std::string *buffer = nullptr,
                    int flags = DefaultFlags());
    ~TranslationUnit();

    int reparse(const std::string &buffer, int flags = DefaultFlags());

    static int DefaultFlags();

    CodeCompleteResults get_code_completions(const std::string &buffer,
                                             unsigned line_number, unsigned column);

    std::vector<Diagnostic> get_diagnostics();

    std::unique_ptr<Tokens> get_tokens();
    std::unique_ptr<Tokens> get_tokens(const std::string &path, unsigned start_offset, unsigned end_offset);
    std::unique_ptr<Tokens> get_tokens(unsigned start_offset, unsigned end_offset);
    std::unique_ptr<Tokens> get_tokens(unsigned start_line, unsigned start_column,
                                       unsigned end_line, unsigned end_column);

    Cursor get_cursor(const std::string &path, unsigned offset);
    Cursor get_cursor(const std::string &path, unsigned line, unsigned column);
    Cursor get_cursor(const SourceLocation &location);

    CXTranslationUnit cx_tu;
  };
} // namespace clangmm
#endif // TRANSLATIONUNIT_H_
