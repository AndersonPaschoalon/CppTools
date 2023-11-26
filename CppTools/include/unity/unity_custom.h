#ifndef UNITY_CUSTOM_H
#define UNITY_CUSTOM_H 1

#include <iostream>

#define RESET_COLOR "\033[0m"
#define GREEN_COLOR "\033[32m"

#define TEST_HEADER \
    std::cout << std::endl; \
    std::cout << GREEN_COLOR << "################################################################################" << RESET_COLOR << std::endl; \
    std::cout << GREEN_COLOR << "# " << __func__ << RESET_COLOR << std::endl; \
    std::cout << GREEN_COLOR << "################################################################################" << RESET_COLOR << std::endl ;


#endif