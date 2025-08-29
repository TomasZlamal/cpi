#include "../src/loc_tool.h"
namespace cpi {
namespace loc {
bool isSubPath(const std::string &base, const std::string &destination) {
  std::string relative = std::filesystem::relative(destination, base);
  // Size check for a "." result.
  // If the path starts with "..", it's not a subdirectory.
  return relative.size() == 1 || relative[0] != '.' && relative[1] != '.';
}
} // namespace loc
using recursive_directory_iterator =
    std::filesystem::recursive_directory_iterator;
int get_project_loc(const toml::table &config) {
  // look for files in the root directory first,
  // then in then impl and header directories
  return [&]() {
    int total = 0;
    config::ImplementationValues impl_val =
        config::getImplValuesFromToml(config);

    // inside of current dir
    std::string path = "./";
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
      if (entry.path().string().find(impl_val.implementation_ext) !=
          std::string::npos) {
        std::ifstream file;
        file.open(entry.path().string());
        auto count = std::count_if(std::istreambuf_iterator<char>{file}, {},
                                   [](char c) { return c == '\n'; });
        total += count;
      }
      if (entry.path().string().find(impl_val.header_ext) !=
          std::string::npos) {
        std::ifstream file;
        file.open(entry.path().string());
        auto count = std::count_if(std::istreambuf_iterator<char>{file}, {},
                                   [](char c) { return c == '\n'; });
        total += count;
      }
    }

    // based on config, recursive
    std::vector<std::string> dirs;
    if (impl_val.header_dir == impl_val.implementation_dir) {
      dirs.push_back(impl_val.header_dir);
    } else {
      bool header_dir_is_inside_impl =
          loc::isSubPath(impl_val.implementation_dir, impl_val.header_dir);
      bool impl_dir_is_inside_header =
          loc::isSubPath(impl_val.header_dir, impl_val.implementation_dir);
      if (!header_dir_is_inside_impl)
        dirs.push_back(impl_val.header_dir);
      if (!impl_dir_is_inside_header)
        dirs.push_back(impl_val.implementation_dir);
    }
    for (const std::string &dir : dirs) {
      for (const auto &dirEntry : recursive_directory_iterator(dir)) {
        if (dirEntry.path().string().find(impl_val.implementation_ext) !=
            std::string::npos) {
          std::ifstream file;
          file.open(dirEntry.path().string());
          auto count = std::count_if(std::istreambuf_iterator<char>{file}, {},
                                     [](char c) { return c == '\n'; });
          total += count;
        }
        // std::cout << "Is impl file: " << dirEntry << std::endl;
        if (dirEntry.path().string().find(impl_val.header_ext) !=
            std::string::npos) {
          std::ifstream file;
          file.open(dirEntry.path().string());
          auto count = std::count_if(std::istreambuf_iterator<char>{file}, {},
                                     [](char c) { return c == '\n'; });
          total += count;
        }
        // std::cout << "Is header file: " << dirEntry << std::endl;
      }
    }

    return total;
  }();
}
} // namespace cpi
