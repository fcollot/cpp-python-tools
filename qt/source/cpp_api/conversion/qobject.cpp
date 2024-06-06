// Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include "qobject.h"

bool pyncppToPython(const QObject* object, PyObject** output)
{
    bool success = true;

    try
    {
        QString className = object->metaObject()->className();
        pyncpp::Module pyncppQtModule = pyncpp::Module::import("pyncpp.qt@PYNCPP_QT_VERSION@");
        pyncpp::Object pythonClass = pyncppQtModule.callMethod("get_class", qUtf8Printable(className));

        pyncpp::Object objectPointer = PyLong_FromVoidPtr(const_cast<QObject*>(object));

        pyncpp::Module shibokenModule = pyncpp::Module::import("shiboken@PYNCPP_SHIBOKEN_VERSION@");
        pyncpp::Object wrappedObject = shibokenModule.callMethod("wrapInstance", objectPointer, pythonClass);

        *output = wrappedObject.newReference();
    }
    catch (pyncpp::Exception& e)
    {
        pyncpp::raiseError(&e);
        success = false;
    }

    return success;
}

bool pyncppToCPP(PyObject* nativeObject, QObject* output)
{

    return true;
}
