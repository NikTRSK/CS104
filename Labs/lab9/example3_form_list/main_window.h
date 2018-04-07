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
	void addQuote();
	void displayQuote(int quoteIndex);

private:
	// // UI
	// Layouts
	QHBoxLayout* overallLayout;

	// Displayed quote
	QVBoxLayout* quoteDisplayLayout;
	QLabel* quoteDisplay;
	QLabel* personDisplay;

	// List of quotes
	QListWidget* quoteListWidget;

	// Form for new quote
	QVBoxLayout* formLayout;
	QLabel* personLabel;
	QLineEdit* personInput;
	QLabel* quoteLabel;
	QTextEdit* quoteInput;
	QPushButton* addButton;



	// // Data
	// note: the index of each person in `people` corresponds with 
	// the index of that person's quote in `quotes`

	// List of people quoted
	std::vector<std::string> people;

	// List of quotes
	std::vector<std::string> quotes;
};
