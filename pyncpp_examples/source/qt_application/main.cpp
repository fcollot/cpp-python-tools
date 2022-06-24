// Copyright (c) 2022 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include <QApplication>

#include <pyncpp.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    pyncpp::Manager pythonManager;
    int success = pythonManager.initialize();

    if (success)
    {
        success = app.exec();
    }

    return success;
}
