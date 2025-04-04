#pragma once
#include "MyWindow.h"

class COFFEECORE_API WindowManager {
private:
	WindowManager();
	~WindowManager();

	static WindowManager* p_instance;
	MyWindow* p_Window;

public:
	//Création d'erreur pour ne pas copier et assigné
	WindowManager(WindowManager& other) = delete;
	void operator=(const WindowManager&) = delete;

	static WindowManager* getInstance();
	MyWindow* getWindow();
};