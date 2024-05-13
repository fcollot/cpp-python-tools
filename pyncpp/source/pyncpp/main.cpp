#include <pyncpp.h>

#include <iostream>

int main(int argc, char** argv)
{
    int exit_status = EXIT_SUCCESS;

    pyncpp::Manager::setPythonHome(PYTHON_HOME);
    pyncpp::Manager::setCommandLineArguments(argc, argv);
    pyncpp::Manager pyncppManager = pyncpp::Manager::instance();

    if (pyncppManager.errorOccured())
    {
        std::cout << "Python initialization error: " << pyncppManager.errorMessage() << "\n";
        exit_status = EXIT_FAILURE;
    }
    else
    {
        exit_status = pyncppManager.runMain();
    }

    return exit_status;
}
