#include "audiopch.h"
#include "OscillatorStack.h"

namespace LSAP {
	OscillatorStack::~OscillatorStack()
	{
		for (auto i : mOscillators) {
			delete i;
		}
	}
	void OscillatorStack::pushOsc(Oscillator* osc)
	{
		mOscillators.emplace(mOscillators.begin() + mOscIndex++, osc);
		osc->onOscAttach();
	}

	void OscillatorStack::popOsc(Oscillator* osc)
	{
		auto it = std::find(mOscillators.begin(), mOscillators.end(), osc);
		if (it != mOscillators.end()) {
			mOscillators.erase(it);
			mOscIndex--;
		}
	}
	void OscillatorStack::onOscStackUpdate()
	{
		for (auto& i : mOscillators) {
			i->onOscUpdate();
		}
	}
	void OscillatorStack::onImGuiRender()
	{
		for (auto& i : mOscillators) {
			i->onImGuiRender();
		}
	}
	Note& OscillatorStack::onNotePush(Note& note)
	{
		return mNotes.emplace_back(note);
	}
	double OscillatorStack::onOscStackFill(Note& n, double time)
	{
		double data = 0;
		for (auto& i : mOscillators) {
			data += i->onOscFill(n, time);
		}
		return data;
	}
}