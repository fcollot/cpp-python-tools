// Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include "manager.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "error/exception_types.h"

namespace pyncpp
{

std::unique_ptr<Manager> Manager::static_instance;

struct ManagerPrivate
{
    static std::filesystem::path pythonHome;
    static int argc;
    static std::vector<std::string> argv;
    static std::string mainModule;

    std::string errorMessage;
    bool ownsPython = false;
};

std::filesystem::path ManagerPrivate::pythonHome;
int ManagerPrivate::argc = -1;
std::vector<std::string> ManagerPrivate::argv;
std::string ManagerPrivate::mainModule;

void Manager::setPythonHome(const std::filesystem::path& pythonHome)
{
    ManagerPrivate::pythonHome = pythonHome;
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

Manager& Manager::instance()
{
    if (!static_instance)
    {
        static_instance = std::unique_ptr<Manager>(new Manager);
    }

    return *static_instance.get();
}

Manager::Manager() :
    d(new ManagerPrivate)
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

Manager::~Manager()
{
    finalizeInterpreterIfNeeded();
}

bool Manager::errorOccured()
{
    return !d->errorMessage.empty();
}

const char* Manager::errorMessage()
{
    return d->errorMessage.c_str();
}

std::filesystem::path Manager::getPythonHome()
{
    return d->pythonHome;
}

int Manager::runMain()
{
    return Py_RunMain();
}

void Manager::initializeInterpreterIfNeeded()
{
    if (!Py_IsInitialized())
    {
        PyConfig config;
        PyConfig_InitPythonConfig(&config);
        config.isolated = 1;
        std::wstring home = d->pythonHome.wstring();

        if (d->argc >= 1)
        {
            char* argv[d->argc];

            for (size_t i = 0; i < d->argc; i++)
            {
                argv[i] = const_cast<char*>(d->argv[i].c_str());
            }

            checkStatus(PyConfig_SetBytesArgv(&config, d->argc, argv));
        }

        if (!home.empty())
        {
            PyConfig_SetString(&config, &config.home, home.c_str());
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
