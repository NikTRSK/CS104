#include "main_window.h"

MainWindow::MainWindow()
{
	// Title
	setWindowTitle("Pokedex");



	// Overall layout
	overallLayout = new QHBoxLayout();




	// // Selected pokemon display
	// Layout
	pokemonDisplayLayout = new QVBoxLayout();
	overallLayout->addLayout(pokemonDisplayLayout);

	// Pokemon image
	//TODO

	// Pokemon name
	//TODO

	// Make it so image and name are at the top
	pokemonDisplayLayout->addStretch();




	// // List of all pokemon
	//TODO




	// // Form to add pokemon
	// Layout
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);


	// Pokemon name label
	pokemonNameLabel = new QLabel("Pokemon's Name:");
	formLayout->addWidget(pokemonNameLabel);

	// Pokemon name input
	//TODO


	// Image filename label
	imageFilenameLabel = new QLabel("Image Filename:");
	formLayout->addWidget(imageFilenameLabel);

	// Image filename input
	//TODO


	// Add button
	//TODO




	// Set overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	// Delete the images
	for(std::vector<QImage*>::iterator i = pokemonImages.begin();
		i != pokemonImages.end();
		++i)
	{
		delete *i;
	}

	//TODO the delete UI objects
}



void MainWindow::addPokemon()
{
	// Do nothing if user left at least one input blank
	//TODO


	// // Get form values
	// Pokemon name
	//TODO
	
	// Image
	QString filename = imageFilenameInput->text();
	QImage* newImage = new QImage();
	//TODO what should go right here?
	pokemonImages.push_back(newImage);


	// Create a new list item with the pokemon's name
	//TODO


	// Clear the form inputs
	//TODO
}



void MainWindow::displayPokemon(int pokemonIndex)
{
	// Get the pokemon specified by the index,
	// which is passed into the function when
	// the user clicks on pokemonListWidget

	// Image
	//TODO

	// Pokemon name
	//TODO
}
