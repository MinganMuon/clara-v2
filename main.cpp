// main.cpp

#include "ui.h"

int main(){
	MainUI TheMainUI;
	if (!TheMainUI.initUI())
		return 1;

	TheMainUI.MainMenu();

	TheMainUI.closeUI();
	return 0;
}

