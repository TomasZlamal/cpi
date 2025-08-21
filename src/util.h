#pragma once
#ifdef CPI_COMPILE_WITH_RANG
#define RANG_EXPR(x) x
#else
#define RANG_EXPR(x) ""
#endif

#ifdef CPI_COMPILE_WITH_RANG
#include "../libs/rang/rang.hpp"
#endif

namespace cpi {
enum class ToolChoice { NONE, SETUP, INITCPI, CCLASS };
}
