----

Version 0.1.0.0
Author: Anderson Paschoalon

* Major Changes (MAJOR):
    - Signature of `StringUtils::toLower` changed from `static std::string toLower(const char* str)` to `void toLower(std::string& str)`. 
    - all const std::string were changed to const char *;
    - New Folder Structure, no OS specific build. 

* New Features (MINOR):
    - Supports debug on VsCode enviroment. Just run debug_cpptools.
    - TEST_HEADER on unity tests.
    - CsvParser: new methods.
    - StringUtils: new methods.
    - new unity tests.
    - now, supports PLOG.
    - new class VectorUtils

* Bug Fixes (PATCH):
    - CscParser class fixed;

* Misc:
    - N/A

* Known Issues:
    - Wild log not yet supported
    - Rapdixml not yet supported
    - a lot of warnings


----

Version 0.0.0.1
Author: Anderson Paschoalon

* Major Changes (MAJOR):
    - N/A

* New Features (MINOR):
    - N/A

* Bug Fixes (PATCH):
    - N/A

* Misc:
    - First version

* Known Issues:
    - CscParser not working.

