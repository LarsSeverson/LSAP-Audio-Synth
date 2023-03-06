#pragma once

#include "lspch.h"
#include "Core.h"
#include "Events/Event.h"

namespace LSAP {

	struct WindowProperties {
		std::string wTitle;
		unsigned int wWidth;
		unsigned int wHeight;
		WindowProperties(const std::string title = "LSAP Synth", 
			unsigned int width = 1200, unsigned int height = 880)
			: wWidth(width), wHeight(height), wTitle(title)
		{}
	};

	class LSAP_API Window
	{
	public:
		using EventCallbackW = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		
		virtual void* getNativeWindow() const = 0;
		virtual void onUpdate() = 0;
		virtual void setEventCallback(const EventCallbackW& event) = 0;

		virtual void setVSync(bool enabled) = 0;
		
		static Window* createWindow(const WindowProperties& props = WindowProperties());
	};
}