#include "controller.h"

/**
 * Constructor
 */
Controller::Controller()
	: Subject(), currentScreen(0)
{
	//TODO
}

/**
 * Defines the current screen to display
 * @param value : id of the screen to display
 */
void Controller::setScreen(const int& value)
{
	if (value >= 0 && value <= 9)
		currentScreen = value;

	notify();
}

/**
 * Returns the id of the current displayed screen
 */
int Controller::getCurrentScreen()
{
	return currentScreen;
}

