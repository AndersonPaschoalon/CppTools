# CppTools 🚀
<p align="center">
  <img src="./Img/CppToolsLogo.jpg">
</p>
CppTools is a powerful C++ library designed to simplify your development process and enhance your C++ projects. 💻 With a collection of useful utilities and open-source libraries, CppTools offers a seamless experience for all C++ developers.

# Features 🛠️
- 🏭 Easy-to-use utilities to accelerate your C++ development.

- 📚 Comprehensive documentation with examples for quick understanding.

- 📦 Simple build process using make for easy compilation and testing.

- 🔧 Bundled with essential open-source libraries for your convenience.

# Getting Started 🚀

To build and use CppTools, follow these steps:

1.  Clone the repository:

    ```bash
    git clone https://github.com/AndersonPaschoalon/CppTools.
    ```

2. Build the library and run tests:
    ```bash
    cd CppTools/Linux
    make
    ```

3. Create a usable library package:
    ```bash
    make pkg
    ```
    The tarball (cpptools_<version>.tar.gz) with the binaries and includes will be created in the Linux/pkg folder.

4. Linking to CppTools in your project:
    Create a libs/cpptools/ folder in your project.
    Extract the tarball content into the libs/cpptools/ folder.
    Add the following flags to your g++ compilation command:
    ```bash
    -Llibs/cpptools/bin -lcpptools -Ilibs/cpptools/include
    ```
    Use the CppTools library in your code:

    In your source code, include "cpptools.h" to access all the necessary headers. For example:

    ```cpp
    #include "cpptools.h"

    int main() {
        std::string trimStr = "         abs     ";
        StringUtils::trim(trimStr);
        std::cout << trimStr << std::endl;
        // Output: "abs"

        return 0;
    }
    ```

# License 📜
This project is licensed under the MIT License. See the LICENSE file for details.


# Acknowledgements 🙌
CppTools wouldn't be possible without the amazing work of several open-source projects. Special thanks to:

- [rapidxml](https://rapidxml.sourceforge.net) - Fast XML parsing library.
- [Plog library](https://github.com/SergiusTheBest/plog) - A lightweight and flexible logging library.
- [Unity](http://www.throwtheswitch.org/unity) - A simple unit testing framework for C.
- [Wild logging](https://github.com/WildCoastSolutions/Logging) - A flexible C++ logging library.

A big thanks to the developers of these projects for their hard work and contributions to the open-source community!

# Let's Collaborate 🤝
CppTools is an open-source project, and we welcome your contributions and feedback. If you have ideas, bug reports, or want to add new features, feel free to create an issue or submit a pull request.

Happy Coding! 😄