// Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include "manager.h"

#include <stdexcept>

#if PYNCPP_QT5_SUPPORT
#include <QDebug>
#include <QDir>
#endif

#include "error/exception_types.h"

namespace pyncpp
{

std::unique_ptr<Manager> Manager::static_instance;

struct ManagerPrivate
{
    static std::string pythonHome;
    static int argc;
    static std::vector<std::string> argv;
    static std::string mainModule;

    wchar_t* pythonHome_wchar;
    std::string errorMessage;
    bool finalizePython = false;
};

std::string ManagerPrivate::pythonHome;
int ManagerPrivate::argc = -1;
std::vector<std::string> ManagerPrivate::argv;
std::string ManagerPrivate::mainModule;

void Manager::setPythonHome(const char* pythonHome)
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
    // warn if already init
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
    finalizeIfNeeded();
}

bool Manager::errorOccured()
{
    return !d->errorMessage.empty();
}

const char* Manager::errorMessage()
{
    return d->errorMessage.c_str();
}

const char* Manager::getPythonHome()
{
    return d->pythonHome.c_str();
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

        if (d->argc >= 1)
        {
            char* argv[d->argc];

            for (size_t i = 0; i < d->argc; i++)
            {
                argv[i] = const_cast<char*>(d->argv[i].c_str());
            }

            checkStatus(PyConfig_SetBytesArgv(&config, d->argc, argv));
        }

        if (!d->pythonHome.empty())
        {
            d->pythonHome_wchar = Py_DecodeLocale(qUtf8Printable(QDir::toNativeSeparators(d->pythonHome.c_str())), nullptr);
            Py_SetPythonHome(d->pythonHome_wchar);
        }

        if (!d->mainModule.empty())
        {
            PyConfig_SetBytesString(&config, &config.run_module, d->mainModule.c_str());
        }

        checkStatus(Py_InitializeFromConfig(&config));

        PyConfig_Clear(&config);

        d->finalizePython = true;
    }
}

void Manager::initializeAPI()
{
    internal::initializeExceptions();
}

void Manager::finalizeIfNeeded()
{
    if (d->finalizePython)
    {
        finalizeInterpreter();
    }
}

void Manager::finalizeInterpreter()
{
    if (Py_IsInitialized())
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
        throw pyncpp::SystemExit(QString("System exit %1").arg(status.exitcode));
    }
}

} // namespace pyncpp
