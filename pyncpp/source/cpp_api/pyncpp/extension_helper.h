// Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#ifndef PYNCPP_EXTENSION_HELPER_H
#define PYNCPP_EXTENSION_HELPER_H

#include "object/module.h"

#include "export.h"

namespace pyncpp
{

struct ExtensionHelperPrivate;

class PYNCPP_EXPORT ExtensionHelper
{
public:
    ExtensionHelper(const char* extensionName);

    void addMethod(const char* name, PyCFunction method, const char* doc);

    PyObject* createModule();

private:
    ExtensionHelperPrivate* const d;
};

} // namespace pyncpp

#endif // PYNCPP_EXTENSION_HELPER_H
