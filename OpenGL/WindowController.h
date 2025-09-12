#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include "StandardIncludes.h"

class WindowController : public Singleton<WindowController>
{
private:
	GLFWwindow* m_window;
public:
	WindowController();
	virtual ~WindowController();
	
	void NewWindow();

	GLFWwindow* GetWindow() { if (m_window == nullptr) { NewWindow();} return m_window; }
};

#endif // WINDOWCONTROLLER_H

