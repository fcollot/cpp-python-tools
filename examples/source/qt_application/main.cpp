// Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include <pyncpp.h>

#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QLayout>

#include "test_button.h"

int main(int argc, char** argv)
{
    int exitStatus = EXIT_SUCCESS;

    pyncpp::Manager::setPythonHome(PYTHON_HOME);
    pyncpp::Manager::setCommandLineArguments(argc, argv);
    pyncpp::Manager pyncppManager;

    if (pyncppManager.errorOccured())
    {
       qCritical() << QString("Python initialization error: %1").arg(pyncppManager.errorMessage());
       exitStatus = EXIT_FAILURE;
    }
    else
    {
        try
        {
            QApplication app(argc, argv);

            pyncppManager.addModulePath("site");

            QMainWindow mainWindow;
            pyncpp::Module::import("__main__").attribute("main_window") = &mainWindow;
            mainWindow.show();

            TestButton* testButton = new TestButton();
            mainWindow.setCentralWidget(testButton);

            pyncpp::Object console = pyncpp::newQtConsole();
            QWidget* consoleWidget = console.toCPP<QWidget*>();
            consoleWidget->setAttribute(Qt::WA_QuitOnClose);
            consoleWidget->show();
            pyncpp::Module::import("__main__").attribute("console") = console;

            //            QObject::connect(&application, &QApplication::aboutToQuit, [&]() { pythonManager.finalize(); });

            exitStatus = app.exec();
        }
        catch (pyncpp::Exception& e)
        {
            qCritical() << "Python error: " << e.what();
            exitStatus = EXIT_FAILURE;
        }
    }

    return exitStatus;
}
