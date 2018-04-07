#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

private slots:
	void showPopup();

private:
	// Layout
	QVBoxLayout* overallLayout;

	// Result label
	QLabel* resultLabel;

	// Button
	QPushButton* button;
};
