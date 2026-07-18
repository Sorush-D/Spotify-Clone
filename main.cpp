#include <QApplication>
#include "Database/DatabaseManager.h"
#include "UI/MainWindow/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if (!DatabaseManager::instance().open()) return -1;
    if (!DatabaseManager::instance().createTables()) return -1;

    MainWindow window;
    window.show();

    return QApplication::exec();
}
