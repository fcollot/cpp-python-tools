// Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#ifndef PYNCPP_QT_QOBJECT_H
#define PYNCPP_QT_QOBJECT_H

#include <type_traits>

#include <pyncpp.h>

#include <QObject>

PYNCPP_EXPORT bool pyncppToPython(const QObject* object, PyObject** output);
PYNCPP_EXPORT bool pyncppToCPP(PyObject* nativeObject, QObject** output);

template <class TYPE, typename = std::enable_if_t<std::is_base_of_v<QObject, TYPE> > >
PYNCPP_EXPORT bool pyncppToCPP(PyObject* nativeObject, TYPE** output)
{
    return pyncppToCPP(nativeObject, (QObject**)(output));
}

#endif // PYNCPP_QT_QOBJECT_H
