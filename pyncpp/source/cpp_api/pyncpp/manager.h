// Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#ifndef PYNCPP_MANAGER_H
#define PYNCPP_MANAGER_H

#include <filesystem>
#include <memory>

#include "external/cpython.h"

#include "export.h"

namespace pyncpp
{

struct ManagerPrivate;

class PYNCPP_EXPORT Manager
{
public:
    static void setPythonHome(const std::filesystem::path& pythonHome);

    static void setCommandLineArguments(int argc, char** argv);

    static void setMainModule(const char* name);

    static Manager& instance();

    Manager();
    ~Manager();

    bool errorOccured();
    const char* errorMessage();

    std::filesystem::path getPythonHome();

    int runMain();

private:
    static std::unique_ptr<Manager> static_instance;
    ManagerPrivate* const d;

    void initializeInterpreterIfNeeded();
    void initializeAPI();

    void finalizeInterpreterIfNeeded();

    void checkStatus(PyStatus status);
};

} // namespace pyncpp

#endif // PYNCPP_MANAGER_H
