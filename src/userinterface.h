//
// userinterface.h
//
// MiniDexed - Dexed FM synthesizer for bare metal Raspberry Pi
// Copyright (C) 2022  The MiniDexed Team
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _userinterface_h
#define _userinterface_h

#include "config.h"
#include "ky040.h"
#include <display/hd44780device.h>
#include <circle/gpiomanager.h>
#include <circle/writebuffer.h>

class CMiniDexed;

class CUserInterface
{
public:
	CUserInterface (CMiniDexed *pMiniDexed, CGPIOManager *pGPIOManager, CConfig *pConfig);
	~CUserInterface (void);

	bool Initialize (void);

	void Process (void);

	void BankSelected (unsigned nBankLSB);		// 0 .. 127
	void ProgramChanged (unsigned nProgram);	// 0 .. 127

private:
	void LCDWrite (const char *pString);		// Print to optional HD44780 display

	void EncoderEventHandler (CKY040::TEvent Event);
	static void EncoderEventStub (CKY040::TEvent Event, void *pParam);

private:
	enum TUIMode
	{
		UIModeStart,
		UIModeVoiceSelect = UIModeStart,
		UIModeBankSelect,
		UIModeUnknown
	};

private:
	CMiniDexed *m_pMiniDexed;
	CGPIOManager *m_pGPIOManager;
	CConfig *m_pConfig;

	CHD44780Device *m_pLCD;
	CWriteBufferDevice *m_pLCDBuffered;

	CKY040 *m_pRotaryEncoder;

	TUIMode m_UIMode;

	unsigned m_nBank;
	unsigned m_nProgram;
};

#endif