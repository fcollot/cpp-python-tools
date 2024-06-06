// Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include <pyncpp.h>

#include <QApplication>
#include <QMainWindow>

int main(int argc, char** argv)
{
    int exitStatus = EXIT_SUCCESS;

    QApplication app(argc, argv);

    pyncpp::Manager::setCommandLineArguments(argc, argv);
    pyncpp::Manager pyncppManager = pyncpp::Manager::instance();

    if (pyncppManager.errorOccured())
    {
        qCritical() << "Python initialization error: " << pyncppManager.errorMessage();
        exitStatus = EXIT_FAILURE;
    }
    else
    {
        try
        {
            pyncpp::Module consoleModule = pyncpp::Module::import(qUtf8Printable(QString("pyncpp_examples.qt%1").arg(PYNCPP_QT_VERSION)));
            //pyncpp::Object pyApp = consoleModule.callMethod<pyncpp::Object, pyncpp::Object>("wrapInstance", appPointer, qApplicationClass);
            //pyncpp::Module::import("__main__").attribute("app") = pyApp;
            consoleModule.callMethod("runConsole");
//            QWidget* console = d->console->toCPP<QWidget*>();
//            console->setWindowTitle("woohooo!!");
//            pythonManager.setConsoleShortcut(PYTHON_CONSOLE_SHORTCUT);
//            QObject::connect(mainwindow, &QObject::destroyed, [&]() { pythonManager.deleteConsole(); });
//            qInfo() << QString("The Python console can be accessed with %1")
//                       .arg(QKeySequence(PYTHON_CONSOLE_SHORTCUT).toString(QKeySequence::NativeText));
//            QObject::connect(&application, &QApplication::aboutToQuit, [&]() { pythonManager.finalize(); });
        }
        catch (pyncpp::Exception& e)
        {
            qCritical() << "Python error: " << e.what();
        }

       QMainWindow mainWindow;
       QVariant qvariant = QVariant::fromValue(&mainWindow);
       app.setProperty("main_window", qvariant);
       mainWindow.show();

       exitStatus = app.exec();
    }

    return exitStatus;
}
