// Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#ifndef PYNCPP_QT_CONSOLE_H
#define PYNCPP_QT_CONSOLE_H

#include <pyncpp.h>

#include <QWidget>

namespace pyncpp
{

PYNCPP_EXPORT Object newQtConsole(QWidget* parent = nullptr);

}

#endif // PYNCPP_QT_CONSOLE_H
