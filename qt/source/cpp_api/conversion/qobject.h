// Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#ifndef PYNCPP_QOBJECT_H
#define PYNCPP_QOBJECT_H

#include <pyncpp.h>

#include <QObject>

PYNCPP_EXPORT bool pyncppToPython(const QObject* object, PyObject** output);
PYNCPP_EXPORT bool pyncppToCPP(PyObject* nativeObject, QObject* output);

#endif // PYNCPP_QOBJECT_H
