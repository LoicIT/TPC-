#pragma once
#include <iostream>
#include "View.h"
#include "controller.h"

using namespace std;

class VIewMenu
{
private:
	Controller& controller;
public:
	VIewMenu();
	~VIewMenu();
	void ViewMenu(Controller&_controller);
	void notify();
	void Display();
};

Controller::controller

cout << "1 - Afficher l'image" << endl;
cout << "2 - Effets applicables à l'image" << endl;
cout << "3 - Quitter" << endl;
