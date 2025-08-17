#include "initcpi.h"
namespace cpi {
namespace initcpi {} // namespace initcpi
void init_cpi() {
  std::filesystem::create_directory("cpi");
  std::ofstream cpi_toml("cpi/cpi.toml");

  cpi_toml << "\n\n[Implementator]\nimpl = \"\"\nheader = \"\"\n" << std::endl;

  cpi_toml.close();
  std::ofstream gitignore;

  gitignore.open(".gitignore",
                 std::ios_base::app); // append instead of overwrite
  gitignore << "cpi/";
}
} // namespace cpi
