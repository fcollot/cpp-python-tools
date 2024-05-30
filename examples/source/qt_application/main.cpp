// Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
// License: BSD-3-Clause

#include <pyncpp.h>

#include <QApplication>
#include <QMainWindow>
#include <QThread>

int pythonExitStatus;

void runPython(int argc, char** argv)
{

}

int main(int argc, char** argv)
{
    int exitStatus = EXIT_SUCCESS;

    QApplication app(argc, argv);

    QString pythonHome = app.applicationDirPath() + "/" + PYTHON_HOME;
    pyncpp::Manager::setPythonHome(qUtf8Printable(pythonHome));
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
            pyncpp::Object appPointer = PyLong_FromVoidPtr(&app);
            pyncpp::Module qtWidgetsModule = pyncpp::Module::import("PySide6.QtWidgets");
            pyncpp::Object qApplicationClass = qtWidgetsModule.attribute("QApplication");
            pyncpp::Module consoleModule = pyncpp::Module::import("qt_console");
            qDebug() << "-------------------";
            pyncpp::Object pyApp = consoleModule.callMethod<pyncpp::Object, pyncpp::Object>("wrapInstance2", appPointer, qApplicationClass);
            pyncpp::Module::import("__main__").attribute("app") = pyApp;
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
