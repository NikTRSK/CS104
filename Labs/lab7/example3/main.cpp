#include <QApplication>
#include <QGridLayout>
#include <QPushButton>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QWidget window;

  QPushButton *button1 = new QPushButton("Button 1");
  QPushButton *button2 = new QPushButton("Button 2");
  QPushButton *button3 = new QPushButton("Button 3");
  QPushButton *button4 = new QPushButton("Button 4");

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(button1, 0, 0, 1, 3);
  layout->addWidget(button2, 1, 0, 1, 2);
  layout->addWidget(button3, 1, 2, 1, 1);
  layout->addWidget(button4, 2, 0, 1, 3);

  window.setLayout(layout);
  window.show();

  return app.exec();
}

