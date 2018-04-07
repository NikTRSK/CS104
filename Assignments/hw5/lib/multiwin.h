#ifndef MULTIWIN_H
#define MULTIWIN_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QWidget>
#include <QImage>
#include <QMessageBox>
#include <QListWidget>
#include <QComboBox>
#include <QStringBuilder>

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include "facile.h"
#include "msort.h"

class Multiwin : public QWidget
{
  Q_OBJECT
public:
  Multiwin(QApplication *app);
  ~Multiwin();

public slots:
  void loadProgram();
  void quitProgram();
  void setBreakpoint();
  void runDebugger();
  void next();
  void step();
  void continueProgram();
  void openValuesWindow();
  void updateValues();
  void closeValWindow();

private:
  QApplication* app;
  // LOAD WINDOW widgets
  QWidget* loadWindow;
  QGridLayout* inputLayout;
  QVBoxLayout* loadLayout;

  // logo label
  QLabel* logoContainer;
  QImage logoImage;

  // buttons
  QPushButton* quitButton;
  QPushButton* loadButton;

  // filename input form
  QLabel* filenameInputLabel;
  QHBoxLayout* filenameInputLayout;
  QLineEdit* filenameInput;

  // DEBUGGER WINDOW widgets
  QGridLayout* debuggerLayout;
  QWidget* debuggerWindow;
  QPushButton* closeDebuggerBtn;
  QListWidget* lineList;
  QPushButton* breakpointBtn;
  QPushButton* continueBtn;
  QPushButton* nextBtn;
  QPushButton* stepBtn;
  QPushButton* inspectBtn;
  QPushButton* runBtn;
  QLabel* execFinishedLabel;

  // VALUES WINDOW widgets
  QWidget* valuesWindow;
  QGridLayout* valuesLayout;
  QPushButton* updateValsBtn;
  QPushButton* closeValsBtn;
  QLabel* sortLabel;
  QListWidget* valueList;
  QComboBox* sortTypeBox;

  // facile variable and row tracking
  facile* interpreter = NULL; // set as NULL for destructor purposes.
                              // so that the program doesn't crash on close before loading a file
  int currRow;
  bool breakpointHit; // used in the next() function
};

#endif