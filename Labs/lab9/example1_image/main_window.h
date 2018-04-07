#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

private:
	// Layout
	QVBoxLayout* overallLayout;

	// Image
	QImage image;
	QLabel* imageContainer;

	// Image caption
	QLabel* captionLabel;
};
