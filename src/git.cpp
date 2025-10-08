#include "./commands/branch.hpp"
#include "./commands/checkout.hpp"
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

std::optional<std::filesystem::path> find_git_dir() {
  std::filesystem::path current_path = std::filesystem::current_path();
  while (current_path.has_parent_path()) {
    std::filesystem::path git_path = current_path / ".mygit";
    if (std::filesystem::is_directory(git_path)) {
      return std::filesystem::relative(git_path);
    }
    current_path = current_path.parent_path();
  }
  return std::nullopt;
}

int main(int argc, char *argv[]) {
  auto git_dir_optional = find_git_dir();
  if (!git_dir_optional) {
    std::cerr << "fatal: not a git repository (or any of the parent "
                 "directories): .git"
              << std::endl;
    return 1;
  }
  const std::filesystem::path GIT_DIRPATH = *git_dir_optional;

  if (argc == 1) {
    std::cout << "Usage: mygit <command> [<args>]" << std::endl;
    return 0;
  }

  std::string command = argv[1];

  if (command == "branch") {
    Branch::branch(argc, argv, GIT_DIRPATH.string());
  } else if (command == "checkout") {
    Checkout::checkout(argc, argv, GIT_DIRPATH);
  } else {
    std::cerr << "mygit: '" << command << "' is not a mygit command."
              << std::endl;
    return 1;
  }

  return 0;
}
