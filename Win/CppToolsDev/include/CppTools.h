#ifndef  __CPP_TOOLS_H__
#define __CPP_TOOLS_H__ 1

// Unity
#define UNITY_INCLUDE_SETUP_STUBS  
#define UNITY_WEAK_ATTRIBUTE 
#include "unity/unity.h"
#include "unity/unity.h"
#include "unity/unity_internals.h"

// C++ Lang
#include "lang/Defines.h"
#include "lang/Namespaces.h"
#include "lang/Console.h"
#include "lang/DoubleBuffer.h"
#include "lang/StrBuffer.h"

// CSV
#include "csv/Csv.h"

// INI
#include "ini/ini.h"
#include "ini/INIReader.h"

// JSON
#define CJSON_IMPORT_SYMBOLS
#define CJSON_EXPORT_SYMBOLS
#include "cjson/cJSON.h"
#include "cjson/cJSON_Utils.h"


// Rapidxml
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_iterators.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

// Windows vs Linux
#ifndef  _WIN32
#include <sys/wait.h>
#else // ! _WIN32
#include "sys/wait.h" 
#endif

#endif // ! __CPP_TOOLS_H__
