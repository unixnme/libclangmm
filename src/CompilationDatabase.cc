#include "CompilationDatabase.h"
#include <exception>

clang::CompilationDatabase::
CompilationDatabase(const std::string &project_path) {
  CXCompilationDatabase_Error error;
  db_ = clang_CompilationDatabase_fromDirectory(project_path.c_str(), &error);
  if(error) {
    //TODO: compile_commands.json is missing, create it?
  }
}

clang::CompilationDatabase::
~CompilationDatabase() {
  clang_CompilationDatabase_dispose(db_);
}
