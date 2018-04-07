#include "main_window.h"

MainWindow::MainWindow()
{
	// Overall layout
	overallLayout = new QVBoxLayout();



	// Result label
	resultLabel = new QLabel();
	overallLayout->addWidget(resultLabel);



	// Button
	button = new QPushButton("Show Wisdom");
	connect(button, SIGNAL(clicked()), this, SLOT(showPopup()));
	overallLayout->addWidget(button);



	// Set overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	delete resultLabel;
	delete button;
	delete overallLayout;
}



void MainWindow::showPopup()
{
	// Create message box
	QMessageBox msgBox;

	// Set message box text values
	msgBox.setWindowTitle("Wisdom");
	msgBox.setText("\"Would you believe in what you believed in if you were the only one who believed it?\"");
	msgBox.setInformativeText("  -Kanye West");

	// Add buttons to message box
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	// Show (execute) the message box and put the user's answer into `userAnswer`
	int userAnswer = msgBox.exec();

	// Display user's answer on the MainWindow
	if(userAnswer == QMessageBox::Yes) {
		resultLabel->setText("You accepted the wisdom.");
	}
	else if(userAnswer == QMessageBox::No) {
		resultLabel->setText("You rejected the wisdom.");
	}

	// Note: to see more detailed options for QMessageBox, including
	// adding Save, Cancel, and Discard buttons, go to the link below:
	// http://doc.qt.io/qt-4.8/qmessagebox.html#details
}