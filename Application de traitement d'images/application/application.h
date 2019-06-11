#pragma once
#include "Controller.h"
#include "view.h"
#include "VIewMenu.h"
#include "AffImage.h"


class Application
{
private:
	Controller controller;
	VIewMenu ViewMenu;
	AffImage affichage;
public:
	/**
	 * Constructor
	 */
	Application();

	/**
	 * Runs the application
	 */
	void run();

	
};

application.run(controller.setScreen(0));