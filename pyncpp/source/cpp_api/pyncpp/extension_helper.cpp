// Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include "extension_helper.h"

namespace pyncpp
{

struct ExtensionHelperPrivate
{
    std::string name;
    PyCFunction function;
    std::vector<PyMethodDef> methods;
};

ExtensionHelper::ExtensionHelper(const char* extensionName) :
    d(new ExtensionHelperPrivate)
{
    d->name = extensionName;
}

void ExtensionHelper::addMethod(const char* name, PyCFunction method, const char* doc)
{
    d->methods.push_back({name, method, METH_VARARGS, doc});
}

PyObject* ExtensionHelper::createModule()
{
    d->methods.push_back({nullptr, nullptr, 0, nullptr});

    PyModuleDef moduleDefinition = {
        PyModuleDef_HEAD_INIT,
        d->name.c_str(),
        nullptr,
        -1,
        d->methods.data(),
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };

    return PyModule_Create(&moduleDefinition);
}

} // namespace pyncpp
