// Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include "console.h"

#include "qt.h"

namespace pyncpp
{

Object pyncpp::newQtConsole(QWidget* parent)
{
    Object consoleClass = Module::import(qUtf8Printable(QString("pyncpp.qt%1.console").arg(PYNCPP_QT_VERSION))).attribute("Console");
    Object console = consoleClass();
    console.callMethod("run");
    QWidget* consoleWidget = console.toCPP<QWidget*>();
    consoleWidget->setParent(parent);
    return console;
}

}
