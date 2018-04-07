#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QWidget window;

  QPushButton *button1 = new QPushButton("Button 1");
	QPushButton *button2 = new QPushButton("Button 2");
  QPushButton *button3 = new QPushButton("Button 3");
  QPushButton *button4 = new QPushButton("Button 4");

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(button1);
  layout->addWidget(button2);
  layout->addWidget(button3);
  layout->addWidget(button4);

  window.setLayout(layout);
  window.show();

  return app.exec();
}

