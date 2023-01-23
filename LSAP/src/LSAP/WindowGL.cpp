#include "lspch.h"
#include "WindowGL.h"

#include "LSAP/Events/ApplicationEvent.h"
#include "LSAP/Events/KeyEvent.h"
#include "LSAP/Events/MouseEvent.h"

#include "Log.h"

namespace LSAP
{
	Window* Window::createWindow(const WindowProperties& props) {
		return new WindowGL(props);
	}

	WindowGL::WindowGL(const WindowProperties& props) {
		WindowGL::initWindow(props);
	}

	WindowGL::~WindowGL() {
		WindowGL::shutDown();
	}
	
	void WindowGL::initWindow(const WindowProperties& props) {

		LS_CORE_INFO("Creating window {0} ({1}, {2})", props.wTitle, props.wWidth, props.wHeight);
		LS_ASSERT(glfwInit(), "Could not initialize GLFW");
		
		glfwWindow = glfwCreateWindow((int)props.wWidth, (int)props.wHeight, props.wTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(glfwWindow);
		glfwSetWindowUserPointer(glfwWindow, &mWindowContext);

		// -------------Callbacks-------------
		glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* window, int width, int height) {
		WindowContext cb = *(WindowContext*)glfwGetWindowUserPointer(window);
		WindowResizeEvent event(width, height);
		cb.EventCallback(event);
		});

		glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window) {
		WindowContext& cb = *(WindowContext*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		cb.EventCallback(event);
		});

		glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowContext& cb = *(WindowContext*)glfwGetWindowUserPointer(window);
		switch (action) {
		case GLFW_PRESS: {
			KeyPressedEvent event(key, 0);
			cb.EventCallback(event);
			break;
		}
		case GLFW_RELEASE: {
			KeyReleasedEvent event(key);
			cb.EventCallback(event);
			break;
		}
		case GLFW_REPEAT: {
			KeyPressedEvent event(key, 1);
			cb.EventCallback(event);
			break;
		}
		}
		});
		
		glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods) {
		WindowContext& cb = *(WindowContext*)glfwGetWindowUserPointer(window);

		switch (action) {
		case GLFW_PRESS: {
			MouseButtonPressedEvent event(button);
			cb.EventCallback(event);
			break;
		}
		case GLFW_RELEASE: {
			MouseButtonReleasedEvent event(button);
			cb.EventCallback(event);
			break;
		}
		}
		});
	
		glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xPos, double yPos){
		WindowContext& cb = *(WindowContext*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent event((float)xPos, (float)yPos);
		cb.EventCallback(event);
		});

		glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xPos, double yPos) {
		WindowContext& cb = *(WindowContext*)glfwGetWindowUserPointer(window);
		MouseMovedEvent event((float)xPos, (float)yPos);
		cb.EventCallback(event);
		});
	}
	void WindowGL::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(glfwWindow);
	}

	void WindowGL::shutDown() {
		glfwDestroyWindow(glfwWindow);
	}
}