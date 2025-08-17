# cpi - A collection of utility C++ tools
## Motivation

C++ always seems to be behind in terms of tools and setup. Rust has a great toolset ecosystem, and so does Java. Most other languages do aswell. But C++ doesn't really have one. The only thing that comes to mind is clang's toolchain. There's obviously Visual Studio, but that forces you to use an IDE, and isn't dependent only on your terminal.

That's what this collection of tools tries to fix. It promises to be a CLI powerhouse for your C++ projects.
## Tools
### init (working)
`cpi init`
Creates an initialization UI for the user. This allows you to quickly setup a project with tools like Vcpkg.

### initcpi (working)
Initializes all cpi config files.

#### Tool group - Implementator (in progress)
This is a set of tools that creates a header file and a implementation file, with some extra padding.
It will put the impl and header file inside of whatever your set directories are (aswell as prefer extensions), inside of `cpi.toml`.
The same applies to namespaces. Add "-nw" to ignore the default whitespace (TODO).
### cclass - Create Class (in progress)
`cpi cclass CLASSNAME`

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
