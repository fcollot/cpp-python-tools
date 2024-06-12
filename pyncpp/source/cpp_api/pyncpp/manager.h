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
    static const std::filesystem::path& getPythonHome();

    void addInitialModulePath(const std::filesystem::path& path);

    static void setCommandLineArguments(int argc, char** argv);

    static void setMainModule(const char* name);

    Manager();
    ~Manager();

    bool errorOccured();
    void clearError();
    const char* errorMessage();

    bool addModulePath(const std::filesystem::path& path);

    int runMain();

private:
    static std::unique_ptr<Manager> static_instance;
    ManagerPrivate* const d;

    static std::filesystem::path getExecutablePath();
    static std::filesystem::path absolutePath(const std::filesystem::path& path);

    void initializeInterpreterIfNeeded();
    void initializeAPI();

    void finalizeInterpreterIfNeeded();

    void checkStatus(PyStatus status);
};

} // namespace pyncpp

#endif // PYNCPP_MANAGER_H
