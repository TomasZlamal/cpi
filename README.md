# cpi - A collection of utility C++ tools
## Motivation

C++ always seems to be behind in terms of tools and setup. Rust has a great toolset ecosystem, and so does Java. Most other languages do aswell. But C++ doesn't really have one. The only thing that comes to mind is clang's toolchain. There's obviously Visual Studio, but that forces you to use an IDE, and isn't dependent only on your terminal.

That's what this collection of tools tries to fix. It promises to be a CLI powerhouse for your C++ projects.
## Quick overview
This tool allows you to quickly setup c++ projects and to add boilerplate (like splitting up class definitions into implementations and definitions). There should be some utility functions later, like counting the total lines of code in a project (`cpi loc`).

If you want to use the splitting up tools, read more about the `initcpi` tool and `create` group of tools.
## Building & setup
Here's how to build this library & use cpi:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
This should generate a `cpi` executable.
Put this inside of your PATH.
### Build options
#### -DBUILD_WITH_RANG
Use this option to specify whether you want to use colored output using the Rang library:
```bash
cmake .. -DBUILD_WITH_RANG=OFF
```
This disables colored output. The default is ON.
## Tools
### setup (working)
`cpi setup`
Creates an initialization UI for the user. This allows you to quickly setup a project with tools like Vcpkg.

### initcpi (working)
`cpi initcpi`
Initializes all cpi config files.
It is heavily recommended to run this when setting up cpi in your project.

### loc (working)
`cpi loc`
Get the Lines of Code count for your project (based on impl and header dir values in cpi.toml).

### hw (in progress)
`cpi hw`
Creates a main.cc (depends on .toml config) file with a hello world output in your current directory.

### Tool group - create
This is a set of tools that creates a header file and a implementation file, with some extra padding.
It will put the impl and header file inside of whatever your set directories are (aswell as prefer extensions), inside of `cpi.toml`.
The same applies to namespaces. Add "-nw" to ignore the default whitespace (TODO).
#### cclass - Create Class (working)
`cpi cclass CLASSNAME`
Creates an empty class, seperated into an implementation and header file.
#### csplit - split up FILENAME (working)
`cpi csplit FILENAME` 
split up FILENAME into a header and impl file. For example: `cclass "config"` creates two files: "config.h" and "config.cc" inside of the implementation and header directories.
## Cpi directory - cpi/ 
Recommend to put this inside of .gitignore.

### Config file - "cpi.toml"
This is a config file that contains information about your project. Should be located in `./cpi/cpi.toml`
#### Section - \[Implementator]
```toml
[Implementator]
impl = "" # sets the implementation directory
header = "" # sets the implementation directory
namespace = "" # OPTIONAL: namespace for files
```
