#include "multiwin.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Multiwin mainWindow(&app);
  return app.exec();
}