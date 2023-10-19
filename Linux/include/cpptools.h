#ifndef __CPP_TOOLS_H__
#define __CPP_TOOLS_H__ 1

//
// My Implementations
//

#include "utils/StringUtils.h"
#include "utils/VectorUtils.h"
#include "utils/OSUtils.h"
#include "console/Console.h"
#include "csv/CsvParser.h"
#include "thread/TSQueue.h"

//
// Unity testes framework
//

#define UNITY_INCLUDE_SETUP_STUBS 
#include "unity/unity.h"
#include "unity/unity_internals.h"
#include "unity/unity_custom.h"


//
// Rapidxml
//

// #include "rapidxml/rapidxml.hpp"
// #include "rapidxml/rapidxml_iterators.hpp"
// #include "rapidxml/rapidxml_print.hpp"
// #include "rapidxml/rapidxml_utils.hpp"

//
// Plog log framework
//

#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/plog_custom.h"


//
// Wild log framework
//

//#include "wild/Logging.h"


#endif // __CPP_TOOLS_H__