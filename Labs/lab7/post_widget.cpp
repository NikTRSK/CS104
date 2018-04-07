#include <QString>
#include <QFont>
#include "post_widget.h"

PostWidget::PostWidget(Post* p) {
	post = p;
	layout = new QGridLayout();

	// ADD YOUR CODE HERE.
	// Create the suitable labels and add them to GridLayout properly.
}

PostWidget::~PostWidget() {
	delete titleLabel;
	delete usernameLabel;
	delete subredditLabel;
	delete urlLabel;
	delete karmaLabel;
	delete layout;
}
