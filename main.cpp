#include <iostream>
#include <CL/opencl.h>

int main() {
    cl_uint platformCount;
    clGetPlatformIDs(0, nullptr, &platformCount);
    std::cout << "Number of OpenCL platforms: " << platformCount << std::endl;
    return 0;
}