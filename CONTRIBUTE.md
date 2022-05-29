# Contribute Inofrmations
In this file you find everything related to contribute to this project.

## Code Style
- Types start with upper case: `MyClass`
- Functions and Variables start with lower case: `myMethod` / `myVar`
- Macros and Constats names use uppder case with underscores: `MY_MACRO`
- Template parameter names use CamelCase: `InputParser`
- All other names use snake_case: `some_var`
<!--- Constats are all upper case: `const int ID = 394;`-->

## Project Structure
```yaml
../
├─ build/          # Build process is done in there.
├─ data/           # Contains example data.
├─ includes/       # Contains all C/C++ Header Files. (h and hpp)
│  ├─ parsers/     # Contains all Header Files related to Parsers.
│  ├─ version.h    # Contains version informations.
├─ source/         # Contains all C/C++ Source Files. (c and cpp)
│  ├─ parsers/     # Contains all Source Files related to Parsers.
├─ maintainers.md  # Contains Maintainer informations for each feature.
```