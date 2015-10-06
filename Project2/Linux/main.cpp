//
// Created by rustam_t on 10/6/15.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include "../IThread.hpp"
#include "LinuxThread.hpp"

int test(unsigned int thread_id, std::string string)
{
    std::cout << string << std::endl;
    sleep(2);
    return (0);
}

int main()
{
    LinuxThread<int, std::string> t(&test);

    std::cout << t.getStatus() << std::endl;
    t(std::string("coucou"));
    sleep(1);
    std::cout << t.getStatus() << std::endl;
    sleep(2);
    std::cout << t.getStatus() << std::endl;
    sleep(1);
    return (0);
}