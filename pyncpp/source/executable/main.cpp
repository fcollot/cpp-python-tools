#include <pyncpp.h>

#include <iostream>

#if OS_WINDOWS
#elif OS_MACOS
#include <mach-o/dyld.h>
#elif OS_LINUX
#endif

std::filesystem::path getExecutablePath()
{
    std::filesystem::path path;

#if OS_WINDOWS
    wchar_t buffer[MAX_PATH];
    if (GetModuleFileName(nullptr, buffer, MAX_PATH) != 0)
    {
        path = buffer;
    }
#elif OS_MACOS
    char buffer[PATH_MAX];
    uint32_t bufferSize = PATH_MAX;
    if(_NSGetExecutablePath(buffer, &bufferSize) == 0)
    {
        path = buffer;
    }
#elif OS_LINUX
    path = "/proc/self/exe"
#endif

    return std::filesystem::canonical(path);
}

std::filesystem::path getPythonHome()
{
    return getExecutablePath().parent_path() / PYTHON_HOME;
}

int main(int argc, char** argv)
{
    int exitStatus = EXIT_SUCCESS;

    pyncpp::Manager::setPythonHome(getPythonHome());
    pyncpp::Manager::setCommandLineArguments(argc, argv);
    pyncpp::Manager pyncppManager = pyncpp::Manager::instance();

    if (pyncppManager.errorOccured())
    {
        std::cout << "Python initialization error: " << pyncppManager.errorMessage() << "\n" << std::endl;
        exitStatus = EXIT_FAILURE;
    }
    else
    {
        exitStatus = pyncppManager.runMain();
    }

    return exitStatus;
}
