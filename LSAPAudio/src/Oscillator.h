#pragma once

#include "Wave.h"
#include "Note.h"
#include "Envelope.h"
#include "frwddec.h"

namespace LSAP {
	namespace Oscillator {
		class Oscillator
		{
			using OscCallback = std::function<double(Note&, double)>;
		public:
			Oscillator(Wave& wave);
			virtual ~Oscillator() = default;

			virtual void onOscUpdate() {}

			double onOscFill(Note& n, double time);

			void onOscAttach();
			void onOscDetach();
			void setOscillatorWave(const Wave& wave);

			inline Wave& getOscillatorWave() { return mOscillatorWave; }

			// Envelope stuff
			inline EnvelopeData& getEnvData() { return envData; }
			
			void setAttackRate(double attackRate);
			void setDecayRate(double decayRate);
			void setSustainLevel(double level);
			void setReleaseRate(double releaseRate);
		protected:
			double mFrequency;
			double mAmplitude;
			double mAngle;

			bool mIsActive = false;

			Wave& mOscillatorWave;
			OscCallback mOscCallback;
			EnvelopeData envData;

			std::mutex oscMutex;
		};
	}
}
