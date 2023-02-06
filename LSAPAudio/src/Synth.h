#pragma once

#include "LSAP/Input.h"
#include "LSAP/MouseCodes.h"

#include "OscillatorStack.h"
#include "Wave.h"
#include "Note.h"
#include "SoundGenerator.h"

namespace LSAP {
	class Synth
	{
	public:
		Synth();
		~Synth();

		virtual void onSynthUpdate();
		void outputSound();
		void onSynthStop();
		void runSynth();
		void pushOscillator(Oscillator::Oscillator* osc);
		void pushNote(const Note& note);
		void popNote(Note& note);
		void checkInput(uint16_t key, Note note);

		double fillOutputBuffer(double time);

		static Synth& getSynth() { return *sSynthInstance; }
		inline SoundGenerator& getSoundGenerator() { return *mSoundGenerator; }

		std::vector<Note> mNotes;
	private:
		OscillatorStack mOscStack;
		static Synth* sSynthInstance;

		std::shared_ptr<SoundGenerator> mSoundGenerator;

		std::mutex notes;
	};
	Synth* createSynth();
}

