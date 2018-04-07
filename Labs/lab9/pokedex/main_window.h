#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>

#include <string>
#include <vector>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

private slots:
	void addPokemon();
	void displayPokemon(int quoteIndex);

private:

	// // UI

	// Layouts
	QHBoxLayout* overallLayout;

	// Displayed quote
	QVBoxLayout* pokemonDisplayLayout;
	QLabel* pokemonImageContainer;
	QLabel* pokemonNameDisplay;

	// List of quotes
	QListWidget* pokemonListWidget;

	// Form for new quote
	QVBoxLayout* formLayout;
	QLabel* pokemonNameLabel;
	QLineEdit* pokemonNameInput;
	QLabel* imageFilenameLabel;
	QLineEdit* imageFilenameInput;
	QPushButton* addButton;



	// // Data
	// note: the index of each name in `pokemonNames`
	// corresponds with the index of that pokemon's
	// image in `pokemonImages`

	// List of pokemon names
	std::vector<std::string> pokemonNames;
	// List of pokemon images
	std::vector<QImage*> pokemonImages;
};
