#include "main_window.h"

MainWindow::MainWindow()
{
	// Overall layout
	overallLayout = new QHBoxLayout();




	// // Selected quote display
	// Layout
	quoteDisplayLayout = new QVBoxLayout();
	overallLayout->addLayout(quoteDisplayLayout);

	// Quote
	quoteDisplay = new QLabel(" ");
	quoteDisplayLayout->addWidget(quoteDisplay);

	// Person
	personDisplay = new QLabel(" ");
	quoteDisplayLayout->addWidget(personDisplay);

	// Make it so quote and person are at the top
	quoteDisplayLayout->addStretch();




	// // List of all quotes
	quoteListWidget = new QListWidget();
	connect(quoteListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(displayQuote(int)));
	overallLayout->addWidget(quoteListWidget);




	// // Form to add quotes
	// Layout
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);


	// Person
	personLabel = new QLabel("Wise Person's Name:");
	formLayout->addWidget(personLabel);

	personInput = new QLineEdit();
	formLayout->addWidget(personInput);


	// Quote
	quoteLabel = new QLabel("Quote of Wisdom:");
	formLayout->addWidget(quoteLabel);

	quoteInput = new QTextEdit();
	formLayout->addWidget(quoteInput);


	// Add button
	addButton = new QPushButton("Add Quote");
	connect(addButton, SIGNAL(clicked()), this, SLOT(addQuote()));
	formLayout->addWidget(addButton);




	// Set overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	//TODO delete everything
}



void MainWindow::addQuote()
{
	// Do nothing if user left at least one input blank
	if(personInput->text().isEmpty() || quoteInput->toPlainText().isEmpty())
	{
		return;
	}


	// Get form values
	people.push_back(personInput->text().toStdString());
	quotes.push_back(quoteInput->toPlainText().toStdString());


	// Create a new list item with the person's name
    quoteListWidget->addItem(personInput->text());


	// Clear the form inputs
	personInput->setText("");
	quoteInput->setPlainText("");
}



void MainWindow::displayQuote(int quoteIndex)
{
	// Get the quote specified by the index, which comes from the quoteListWidget

	// Quote
	QString quoteText;
	quoteText += "\"";
	quoteText += QString::fromStdString(quotes[quoteIndex]);
	quoteText += "\"";
	quoteDisplay->setText(quoteText);

	// Person
	QString personText;
	personText += "  -";
	personText += QString::fromStdString(people[quoteIndex]);
	personDisplay->setText(personText);
}