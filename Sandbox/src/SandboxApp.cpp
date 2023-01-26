#pragma once
#include <LSAP.h>

class ExampleLayer : public LSAP::Layer
{
public:
	ExampleLayer() : LSAP::Layer("ExampleLayer") {}
	void onLayerUpdate() override {
		if (LSAP::Input::sIsKeyPressed(LSAP::Key::Tab)) {
			LS_TRACE("Tab key pressed");
		}
	}
	void onLayerEvent(LSAP::Event& event) override {

		LS_TRACE("{0}", event);
	}
};

class ExampleSound : public LSAP::SoundGenerator
{
public:
	ExampleSound() : SoundGenerator(getActiveDevice(), 44100, 1, 8, 512){}
};

class Sandbox : public LSAP::Application
{
public:
	Sandbox() {
		setSound(new ExampleSound());
		pushLayer(new ExampleLayer());
		pushOverlay(new LSAP::LSGui());
	}
};

LSAP::Application* LSAP::CreateApplication() {
	return new Sandbox();
}