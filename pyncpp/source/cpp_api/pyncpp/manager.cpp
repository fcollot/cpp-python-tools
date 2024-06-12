// Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include "manager.h"

#if OS_WINDOWS
#elif OS_MACOS
#include <mach-o/dyld.h>
#elif OS_LINUX
#endif

#include <stdexcept>
#include <string>
#include <vector>

#include "conversion.h"
#include "error/exception_types.h"
#include "object.h"

namespace pyncpp
{

struct ManagerPrivate
{
    static int instanceCount;
    static std::filesystem::path pythonHome;
    static std::vector<std::filesystem::path> initialModulePaths;
    static int argc;
    static std::vector<std::string> argv;
    static std::string mainModule;

    std::string errorMessage;
    bool ownsPython = false;
};

int ManagerPrivate::instanceCount = 0;
std::filesystem::path ManagerPrivate::pythonHome;
std::vector<std::filesystem::path> ManagerPrivate::initialModulePaths;
int ManagerPrivate::argc = -1;
std::vector<std::string> ManagerPrivate::argv;
std::string ManagerPrivate::mainModule;

void Manager::setPythonHome(const std::filesystem::path& pythonHome)
{
    ManagerPrivate::pythonHome = absolutePath(pythonHome);
}

const std::filesystem::path& Manager::getPythonHome()
{
    return ManagerPrivate::pythonHome;
}

void Manager::addInitialModulePath(const std::filesystem::path& path)
{
    ManagerPrivate::initialModulePaths.push_back(absolutePath(path));
}

void Manager::setCommandLineArguments(int argc, char** argv)
{
    ManagerPrivate::argc = argc;
    ManagerPrivate::argv.reserve(argc);

    for (size_t i = 0; i < argc; i++)
    {
        ManagerPrivate::argv.push_back(argv[i]);
    }
}

void Manager::setMainModule(const char* name)
{
    ManagerPrivate::mainModule = name;
}

Manager::Manager() :
    d(new ManagerPrivate)
{
    if (ManagerPrivate::instanceCount++ == 0)
    {
        try
        {
            initializeInterpreterIfNeeded();
            initializeAPI();
        }
        catch (std::exception& e)
        {
            d->errorMessage = e.what();
        }
    }
}

Manager::~Manager()
{
    if (--ManagerPrivate::instanceCount == 0)
    {
        finalizeInterpreterIfNeeded();
    }
}

bool Manager::errorOccured()
{
    return !d->errorMessage.empty();
}

void Manager::clearError()
{
    d->errorMessage.clear();
}

const char* Manager::errorMessage()
{
    return d->errorMessage.c_str();
}

bool Manager::addModulePath(const std::filesystem::path& path)
{
    try
    {
        clearError();
        Object pythonPath = absolutePath(path).c_str();
        pyncpp::Module sysModule = pyncpp::Module::import("sys");
        sysModule.attribute("path").append(pythonPath);
    }
    catch (std::exception& e)
    {
        d->errorMessage = e.what();
    }

    return errorOccured();
}

int Manager::runMain()
{
    return Py_RunMain();
}

std::filesystem::path Manager::getExecutablePath()
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

std::filesystem::path Manager::absolutePath(const std::filesystem::path& path)
{
    if (path.is_relative())
    {
        return getExecutablePath().parent_path() / path;
    }
    else
    {
        return path;
    }
}

void Manager::initializeInterpreterIfNeeded()
{
    if (!Py_IsInitialized())
    {
        PyConfig config;
        PyConfig_InitPythonConfig(&config);
        config.isolated = 1;
        std::wstring home = d->pythonHome.wstring();
        std::vector<std::wstring> modulePaths;

        if (d->argc >= 1)
        {
            char* argv[d->argc];

            for (size_t i = 0; i < d->argc; i++)
            {
                argv[i] = const_cast<char*>(d->argv[i].c_str());
            }

            checkStatus(PyConfig_SetBytesArgv(&config, d->argc, argv));
        }

        if (home.empty())
        {
            home = absolutePath(DEFAULT_PYTHON_HOME).wstring();
        }

        PyConfig_SetString(&config, &config.home, home.c_str());

        if (!d->initialModulePaths.empty())
        {
            modulePaths.reserve(d->initialModulePaths.size());

            for (size_t i = 0; i < d->initialModulePaths.size(); i++)
            {
                modulePaths[i] = d->initialModulePaths[i].wstring();
                PyWideStringList_Append(&config.module_search_paths, modulePaths[i].data());
            }

            config.module_search_paths_set = 1;
        }

        if (!d->mainModule.empty())
        {
            PyConfig_SetBytesString(&config, &config.run_module, d->mainModule.c_str());
        }

        checkStatus(Py_InitializeFromConfig(&config));

        PyConfig_Clear(&config);

        d->ownsPython = true;
    }
}

void Manager::initializeAPI()
{
    internal::initializeExceptions();
}

void Manager::finalizeInterpreterIfNeeded()
{
    if (d->ownsPython && Py_IsInitialized())
    {
        Py_FinalizeEx();
    }
}

void Manager::checkStatus(PyStatus status)
{
    if (PyStatus_IsError(status))
    {
        throw std::runtime_error(status.err_msg);
    }

    if (PyStatus_IsExit(status))
    {
        throw pyncpp::SystemExit((std::string("System exit ") + std::to_string(status.exitcode)).c_str());
    }
}

} // namespace pyncpp
