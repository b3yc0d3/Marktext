# Marktext Typeset
![C++: c++17](https://img.shields.io/static/v1?label=c%2B%2B&message=c%2B%2B17&color=%23044F88)
![GNU Make: 4.3](https://img.shields.io/badge/gnu%20make-4.3-lightgrey)
![Platforms: Linux, BSD](https://img.shields.io/badge/platform-linux%20%7C%20bsd-blue)

The new begin of my old Project `oroff`

## Use Code Style
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


<!-- https://cbea.ms/git-commit/ -->