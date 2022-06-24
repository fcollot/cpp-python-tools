// Copyright (c) 2022 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include "manager.h"

#include <iostream>
#include <stdexcept>

#include "cpython.h"

namespace pyncpp
{

struct ManagerPrivate
{
    bool isRunning = false;
    Manager::OutputFunction infoOutput = nullptr;
    Manager::OutputFunction warningOutput = nullptr;
    Manager::OutputFunction errorOutput = nullptr;
};

Manager::Manager() :
    d(new ManagerPrivate)
{
}

Manager::~Manager()
{
    finalize();
}

void Manager::setOutputFunctions(OutputFunction info, OutputFunction warning, OutputFunction error)
{
    d->infoOutput = info;
    d->warningOutput = warning;
    d->errorOutput = error;
}

bool Manager::isRunning()
{
    return d->isRunning;
}

bool Manager::initialize()
{
    try
    {
        initializeOutputFunctions();
        initializeInterpreter();
        initializeAPI();
        d->isRunning = true;
    }
    catch (std::exception& e)
    {
        std::string message = std::string("PYNCPP initialization failed: ") + e.what();
        d->errorOutput(message.c_str());
    }

    return d->isRunning;
}

void Manager::initializeOutputFunctions()
{
    if (!d->infoOutput)
    {
        d->infoOutput = [] (const char* text) { std::cout << text << std::endl; };
    }

    if (!d->warningOutput)
    {
        d->warningOutput = [] (const char* text) { std::cout << text << std::endl; };
    }

    if (!d->errorOutput)
    {
        d->errorOutput = [] (const char* text) { std::cerr << text << std::endl; };
    }
}

void Manager::initializeInterpreter()
{
    Py_Initialize();

    if (Py_IsInitialized())
    {
        std::string message = std::string("Python interpreter initialized: ") + Py_GetVersion();
        d->infoOutput(message.c_str());
    }
    else
    {
        throw std::runtime_error("Could not initialize the Python interpreter.");
    }
}

void Manager::initializeAPI()
{
    //internal::initializeExceptions();
}

void Manager::finalize()
{
    finalizeInterpreter();
    d->isRunning = false;
}

void Manager::finalizeInterpreter()
{
    if (Py_IsInitialized())
    {
        Py_FinalizeEx();
        d->infoOutput("Python interpreter terminated.");
    }
}

} // namespace pyncpp
