#include "main_window.h"

MainWindow::MainWindow()
{
	// Overall layout
	overallLayout = new QVBoxLayout();



	// // Image

	// Load image
	image.load("images/redekopp.jpg");

	// Set up imageContainer
	imageContainer = new QLabel();
	imageContainer->setPixmap(QPixmap::fromImage(image));
	overallLayout->addWidget(imageContainer);



	// Caption
	captionLabel = new QLabel("Kanye West");
	overallLayout->addWidget(captionLabel);



	// Set overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	delete imageContainer;
	delete captionLabel;
	delete overallLayout;
}