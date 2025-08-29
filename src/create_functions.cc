#include "create_functions.h"
namespace cpi {
int split_fn_execute(int (*fn)(std::string_view, const toml::table &), int argc,
                     char **argv, std::string_view fn_name) {
  if (argc < 3) {
    std::cout << RANG_EXPR(rang::fg::red) << "'" << fn_name
              << "' needs atleast 1 argument.\n";
    return 1;
  }

  using namespace std::literals;
  try {
    auto config = toml::parse_file("cpi/cpi.toml");
    int failed = fn(argv[2], config);
    // int failed = cpi::csplit(argv[2], config);
    if (failed) {
      std::cout << RANG_EXPR(rang::fg::red) << "'" << fn_name << "' failed.\n";
      return 1;
    }

    std::cout << RANG_EXPR(rang::fg::green) << "'" << fn_name
              << "' executed succesfully\n"
              << RANG_EXPR(rang::fg::reset);

  } catch (const toml::parse_error &err) {

    std::cout << RANG_EXPR(rang::fg::red)
              << "Something went wrong with reading your cpi.toml file.\n";
    return 1;
  }
  return 0;
}
} // namespace cpi
