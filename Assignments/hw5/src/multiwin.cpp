#include "multiwin.h"

Multiwin::Multiwin(QApplication *app) : QWidget(NULL)
{
  this->app = app;
  currRow = -1; // set initial row for the debugger
  breakpointHit = false;
  /*///////////////////////////////
            LOAD WINDOW
  *////////////////////////////////
  // create load window
  loadWindow = new QWidget();
  loadLayout = new QVBoxLayout();
  // set static geometry and window name
  loadWindow->setWindowTitle("the cOtes");
  loadWindow->setFixedSize(460, 215);
  
  // logo
  // load image
  logoImage.load("img/logo.png");
  // setup image container
  logoContainer = new QLabel();
  logoContainer->setPixmap(QPixmap::fromImage(logoImage));
  loadLayout->addWidget(logoContainer, Qt::AlignCenter);

  // input file form
  inputLayout = new QGridLayout();
  loadLayout->addLayout(inputLayout);

  // filename textbox
  filenameInputLabel = new QLabel("Program filename");
  inputLayout->addWidget(filenameInputLabel, 0,0);

  filenameInput = new QLineEdit("");
  inputLayout->addWidget(filenameInput, 0, 1, 1, 3);

  // load button
  loadButton = new QPushButton("&Load");
  inputLayout->addWidget(loadButton, 0, 4);
  QObject::connect(loadButton, SIGNAL(clicked()), this, SLOT(loadProgram()));
  QObject::connect(filenameInput, SIGNAL(returnPressed()), this, SLOT(loadProgram()));

  // init quit button
  quitButton = new QPushButton("&Quit");
  inputLayout->addWidget(quitButton, 1, 2, 1, 1, Qt::AlignCenter);
  QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));

  loadWindow->setLayout(loadLayout);
  loadWindow->show();

  /*///////////////////////////////
            DEBUGGER WINDOW
  *////////////////////////////////

  // create debugger window
  debuggerWindow = new QWidget();
  debuggerLayout = new QGridLayout();
  // set static geometry and name
  debuggerWindow->setFixedSize(600, 550);
  debuggerWindow->setWindowTitle("Debugger");

  // create the instruction list
  lineList = new QListWidget();
  debuggerLayout->addWidget(lineList, 0, 0, 10, 7);
  // Create buttons
  runBtn = new QPushButton("&Run");
  debuggerLayout->addWidget(runBtn, 0, 7, 1, 2);
  QObject::connect(runBtn, SIGNAL(clicked()), this, SLOT(runDebugger()));

  breakpointBtn = new QPushButton("&Breakpoint");
  debuggerLayout->addWidget(breakpointBtn, 1, 7, 1, 2);
  QObject::connect(breakpointBtn, SIGNAL(clicked()), this, SLOT(setBreakpoint()));

  continueBtn = new QPushButton("&Continue");
  debuggerLayout->addWidget(continueBtn, 2, 7, 1, 2);
  QObject::connect(continueBtn, SIGNAL(clicked()), this, SLOT(continueProgram()));

  nextBtn = new QPushButton("&Next");
  debuggerLayout->addWidget(nextBtn, 3, 7, 1, 1);
  QObject::connect(nextBtn, SIGNAL(clicked()), this, SLOT(next()));

  stepBtn = new QPushButton("&Step");
  debuggerLayout->addWidget(stepBtn, 3, 8, 1, 1);
  QObject::connect(stepBtn, SIGNAL(clicked()), this, SLOT(step()));

  inspectBtn = new QPushButton("&Inspect Values");
  debuggerLayout->addWidget(inspectBtn, 5, 7, 1, 2);
  QObject::connect(inspectBtn, SIGNAL(clicked()), this, SLOT(openValuesWindow()));

  closeDebuggerBtn = new QPushButton("&Close Debugger");
  debuggerLayout->addWidget(closeDebuggerBtn, 9, 8, 1, 1);
  QObject::connect(closeDebuggerBtn, SIGNAL(clicked()), this, SLOT(quitProgram()));

  execFinishedLabel = new QLabel("<font color=\"red\">Execution finished. \nPress Run to restart the program</font>");
  execFinishedLabel->setWordWrap(true);
  debuggerLayout->addWidget(execFinishedLabel, 7, 7, 1, 2);
  execFinishedLabel->hide();

  debuggerWindow->setLayout(debuggerLayout);

  /*///////////////////////////////
            VALUES WINDOW
  *////////////////////////////////
  // create values window
  valuesWindow = new QWidget();
  valuesLayout = new QGridLayout();
  // set static geometry and name
  valuesWindow->setFixedSize(600, 550);
  valuesWindow->setWindowTitle("Inspect Values");

  // create value list
  valueList = new QListWidget();
  valuesLayout->addWidget(valueList, 0, 0, 10, 7);

  // create the Sort Type picker
  sortLabel = new QLabel("Sort Type:");
  valuesLayout->addWidget(sortLabel, 0, 7, 1, 1);
  sortTypeBox = new QComboBox();
  sortTypeBox->addItem("Name (Ascending)");
  sortTypeBox->addItem("Name (Descending)");
  sortTypeBox->addItem("Value (Ascending)");
  sortTypeBox->addItem("Value (Descending)");
  valuesLayout->addWidget(sortTypeBox, 0, 8, 1, 1);

  // create rest of buttons
  updateValsBtn = new QPushButton("&Update Values");
  valuesLayout->addWidget(updateValsBtn, 3, 7, 1, 2);
  QObject::connect(updateValsBtn, SIGNAL(clicked()), this, SLOT(updateValues()));

  closeValsBtn = new QPushButton("&Close");
  valuesLayout->addWidget(closeValsBtn, 9, 8, 1, 1);
  QObject::connect(closeValsBtn, SIGNAL(clicked()), this, SLOT(closeValWindow()));

  valuesWindow->setLayout(valuesLayout);
}

Multiwin::~Multiwin() {
  // only delete if facile is created
  if (interpreter != NULL)
    delete interpreter;

  // DELETE IN REVERSE ORDER OF CREATION
  // Values vars
  delete closeValsBtn;
  delete sortTypeBox;
  delete valueList;
  delete valuesLayout;
  delete valuesWindow;
  // Debugger vars
  delete execFinishedLabel;
  delete closeDebuggerBtn;
  delete inspectBtn;
  delete stepBtn;
  delete nextBtn;
  delete continueBtn;
  delete breakpointBtn;
  delete runBtn;
  delete lineList;
  delete debuggerLayout;
  delete debuggerWindow;
  // Load vars
  delete quitButton;
  delete loadButton;
  delete filenameInput;
  delete filenameInputLabel;
  delete inputLayout;
  delete logoContainer;
  delete loadLayout;
  delete loadWindow;
}

// load facile commands into the list

void Multiwin::quitProgram() {
  QApplication::exit();
}

void Multiwin::loadProgram() {
  // handle empty input. More for the sake of completeness.
  if (filenameInput->text().isEmpty()) {
    QMessageBox emptyFileMsgBox;
    emptyFileMsgBox.information(0, "Missing file name", "Please input a filename !!!");
  }
  else {
    // Load the input file
    std::ifstream inputFile(filenameInput->text().toStdString().c_str());
    // check if the file could be open and open and print error message
    if (!inputFile) {
      QMessageBox badFileMsgBox;
      badFileMsgBox.critical(0,"Error","Error opening file !!!");
      badFileMsgBox.setFixedSize(500,200);
    }
    else {
      // initialize and load the commands to facile
      interpreter = new facile(inputFile);
      // load the commands into the List widget
      std::string line;
      // reset the file to the beginning
      inputFile.clear();
      inputFile.seekg(0, inputFile.beg);
      // fill out the instruction list
      while (getline(inputFile, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end()); // remove newline
        lineList->addItem(QString::fromStdString(line));
      }
      debuggerWindow->show();
      loadWindow->hide();
    }
  }
}

void Multiwin::runDebugger() {
  // clear all rows
  if (currRow > 0)
    lineList->item(currRow-1)->setBackground(QBrush(Qt::white));
  // mark first row. Prepare for execution
  lineList->item(0)->setBackground(QBrush(Qt::green));
  // start/restart facile and finish preparation for execution
  interpreter->initFacile();
  currRow = 1;
  execFinishedLabel->hide();
  lineList->clearSelection();
  breakpointHit = false;
}

void Multiwin::setBreakpoint() {
  // create breakpoint
  if ((lineList->item(lineList->currentRow())->foreground()).color() == Qt::black)
    lineList->item(lineList->currentRow())->setForeground(Qt::red);
  // delete breakpoint
  else if ((lineList->item(lineList->currentRow())->foreground()).color() == Qt::red)
    lineList->item(lineList->currentRow())->setForeground(Qt::black);
}

void Multiwin::continueProgram() {
  // handles case when program not started yet / execution finished
  if (currRow == -1)
    return;
  try {
    // execute commands until a breakpoint is hit & the row is within the bounds
    while (lineList->count() >= currRow && !execFinishedLabel->isVisible()) {
      // when at the end of execution (actually 1 past but last instruction executes when on last line)
      if (currRow == lineList->count()) {
        interpreter->executeInstruction(currRow);
        lineList->item(currRow-1)->setBackground(QBrush(Qt::white)); // clear the last row
        execFinishedLabel->show();
        currRow = -1;
        return;
      }
      
      // execute the instruction and advance one row
      interpreter->executeInstruction(currRow);
      lineList->item(currRow-1)->setBackground(QBrush(Qt::white)); // clear executed row
      currRow = interpreter->currentInstruction();
      lineList->item(currRow-1)->setBackground(QBrush(Qt::green));  // mark next row to be executed

      // stop execution at a break point
      if (((lineList->item(currRow-1)->foreground()).color()) == Qt::red)
        break;
    }
  }
  catch (const char* msg) {
    QMessageBox exceptionMsgBox;
    exceptionMsgBox.critical(0, "Exception Error", msg);
    exceptionMsgBox.setFixedSize(500,200);
    lineList->item(currRow-1)->setBackground(QBrush(Qt::white));
    currRow = -1;
    execFinishedLabel->show();
  }
}

void Multiwin::step() {
  // handles case when program not started yet
  if (currRow == -1)
    return;
  try {
    // when at the end of execution (actually 1 past but last instruction executes when on last line)
    if (currRow == lineList->count() && !execFinishedLabel->isVisible()) {
      interpreter->executeInstruction(currRow);
      lineList->item(currRow-1)->setBackground(QBrush(Qt::white)); // clear the last row
      execFinishedLabel->show();
      currRow = -1;
      return;
    }
    interpreter->executeInstruction(currRow);
    lineList->item(currRow-1)->setBackground(QBrush(Qt::white)); // clear executed row
    currRow = interpreter->currentInstruction();
    lineList->item(currRow-1)->setBackground(QBrush(Qt::green)); // mark next row to be executed
  }
  catch (const char* msg) {
    QMessageBox exceptionMsgBox;
    exceptionMsgBox.critical(0, "Exception Error", msg);
    exceptionMsgBox.setFixedSize(500,200);
    lineList->item(currRow-1)->setBackground(QBrush(Qt::white));
    currRow = -1;
    execFinishedLabel->show();
  }
}

void Multiwin::next() {
  // handles case when program not started yet
  if (currRow == -1)
    return;
  try {
    // when at the end of execution (actually 1 past but last instruction executes when on last line)
    if (currRow == lineList->count() && !execFinishedLabel->isVisible()) {
      interpreter->executeInstruction(currRow);
      lineList->item(currRow-1)->setBackground(QBrush(Qt::white)); // clear the last row
      execFinishedLabel->show();
      currRow = -1;
      return;
    }
    interpreter->executeInstruction(currRow);
    lineList->item(currRow-1)->setBackground(QBrush(Qt::white));   // clear executed row
    currRow = interpreter->currentInstruction();
    
    // execute until return hit
    while (!interpreter->inSubroutine() && !breakpointHit) {
      interpreter->executeInstruction(currRow);
      currRow = interpreter->currentInstruction();
      // stop execution at a break point
      if (((lineList->item(currRow-1)->foreground()).color()) == Qt::red) {
        breakpointHit = true;
        break;
      }
    }
    // reset breakpoint checker once out of subroutine
    if (interpreter->inSubroutine())
      breakpointHit = false;
    
    lineList->item(currRow-1)->setBackground(QBrush(Qt::green));  // mark next row to be executed
  }
  catch (const char* msg) {
    QMessageBox exceptionMsgBox;
    exceptionMsgBox.critical(0, "Exception Error", msg);
    exceptionMsgBox.setFixedSize(500,200);
    lineList->item(currRow-1)->setBackground(QBrush(Qt::white));
    currRow = -1;
    execFinishedLabel->show();
  }
}

void Multiwin::openValuesWindow() {
  // only show if closed
  if (!valuesWindow->isVisible()) {
    valuesWindow->show();
    updateValues();
  }
}

void Multiwin::updateValues() {
  // if program finished / not started. nothing to display
  if (execFinishedLabel->isVisible()) {
    valueList->clear();
    return;
  }
  // create a vector map to hold variables and store them
  std::vector<std::pair<std::string, int> > vars;
  std::map<std::string, int>* variables = &interpreter->getAllVars();
  std::map<std::string, int>::iterator it;
  // find and update the key. If it doesn't exist throw an exception.
  for (it = variables->begin(); it != variables->end(); it++)
    vars.push_back(std::make_pair(it->first, it->second));

  // handle sorting types
  if (sortTypeBox->currentText().toStdString() == "Name (Ascending)") {
    AlphaStrCompAsc ascending;
    mergeSort(vars, ascending);
  }
  else if (sortTypeBox->currentText().toStdString() == "Name (Descending)") {
    AlphaStrCompDec descending;
    mergeSort(vars, descending);
  }
  else if (sortTypeBox->currentText().toStdString() == "Value (Ascending)") {
    NumberCompAsc ascending;
    mergeSort(vars, ascending);
  }
  else if (sortTypeBox->currentText().toStdString() == "Value (Descending)") {
    NumberCompDec descending;
    mergeSort(vars, descending);
  }
  // show sorted variables : values in list.
  valueList->clear();
  for (unsigned int i = 0; i < vars.size(); i++) {
    QString valueLine = QString::fromStdString(vars[i].first) % ": " % QString::number(vars[i].second);
    valueList->addItem(valueLine);
  }
}

void Multiwin::closeValWindow() {
  valuesWindow->hide();
}