#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QLabel helloWorldLabel("Hello world!");
  helloWorldLabel.show();

  return app.exec();
}

