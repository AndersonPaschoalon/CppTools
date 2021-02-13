#ifndef  __CPP_TOOLS_H__
#define __CPP_TOOLS_H__ 1

#include "Defines.h"
#include "Namespaces.h"
#include "Types.h"

#include "PlogMacros.h"
#include "Console.h"
#include "Csv.h"
#include "DoubleBuffer.h"
#include "ini.h"
#include "INIReader.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "StrBuffer.h"
#include "unity.h"
#include "unity_internals.h"

// Windows vs Linux
#ifndef  _WIN32
#include <sys/wait.h>
#else // ! _WIN32
#include "sys/wait.h" 
#endif

#endif // ! __CPP_TOOLS_H__
