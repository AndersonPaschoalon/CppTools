#include <assert.h> 
#include "cpptools.h"



void test_StringUtils()
{
    const char strA01[] = "         abs";
    const char strA02[] = "abs     ";
    const char strA03[] = "         abs     ";
    const char strA04[] = "abs";
    const char strA[] = "abs";

    std::string trimStr = strA03;
    StringUtils::trim(trimStr);

    TEST_ASSERT_EQUAL_STRING(strA,  trimStr.c_str());

}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_StringUtils);

    return UNITY_END();
}