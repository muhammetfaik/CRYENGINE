// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "stdafx.h"
#include "CVars.h"

#include <CrySystem/IConsole.h>

namespace CryAudio
{
namespace Impl
{
namespace Adx2
{
//////////////////////////////////////////////////////////////////////////
void SetVoiceAllocationMethod(ICVar* const pCvar)
{
	pCvar->Set(crymath::clamp(pCvar->GetIVal(), 0, 1));
}

//////////////////////////////////////////////////////////////////////////
void CCVars::RegisterVariables()
{
	// To do: Add platform specific default values.
	m_maxVirtualVoices = 16;
	m_maxVoiceLimitGroups = 16;
	m_maxCategories = 16;
	m_categoriesPerPlayback = 4;
	m_maxTracks = 32;
	m_maxTrackItems = 32;
	m_maxFaders = 4;
	m_numVoices = 8;
	m_maxChannels = 2;
	m_maxSamplingRate = 48000;
	m_numBuses = 8;
	m_outputChannels = 6;
	m_outputSamplingRate = 48000;
	m_maxStreams = 8;
	m_maxFiles = 32;
	m_voiceAllocationMethod = 0;
	m_maxPitch = 2400.0f;

	REGISTER_CVAR2("s_Adx2MaxVirtualVoices", &m_maxVirtualVoices, m_maxVirtualVoices, VF_REQUIRE_APP_RESTART,
	               "Specifies the maximum number of voices for which voice control is performed simultaneously.\n"
	               "Usage: s_Adx2MaxVirtualVoices [0/...]\n"
	               "Default PC: 16\n");

	REGISTER_CVAR2("s_AdxMaxVoiceLimitGroups", &m_maxVoiceLimitGroups, m_maxVoiceLimitGroups, VF_REQUIRE_APP_RESTART,
	               "Specifies the maximum number of Voice Limit Groups that can be created.\n"
	               "Usage: s_AdxMaxVoiceLimitGroups [0/...]\n"
	               "Default PC: 16\n");

	REGISTER_CVAR2("s_Adx2MaxCategories", &m_maxCategories, m_maxCategories, VF_REQUIRE_APP_RESTART,
	               "Specifies the maximum number of categories that can be created.\n"
	               "Usage: s_Adx2MaxCategories [0/...]\n"
	               "Default PC: 16\n");

	REGISTER_CVAR2("s_Adx2CategoriesPerPlayback", &m_categoriesPerPlayback, m_categoriesPerPlayback, VF_REQUIRE_APP_RESTART,
	               "Specifies the number of categories that can be referenced per playback.\n"
	               "Usage: s_Adx2CategoriesPerPlayback [0/...]\n"
	               "Default PC: 4\n");

	REGISTER_CVAR2("s_Adx2MaxTracks", &m_maxTracks, m_maxTracks, VF_REQUIRE_APP_RESTART,
	               "Specifies the total number of Tracks in a sequence that can be played back simultaneously.\n"
	               "Usage: s_Adx2MaxTracks [0/...]\n"
	               "Default PC: 32\n");

	REGISTER_CVAR2("s_Adx2MaxTrackItems", &m_maxTrackItems, m_maxTrackItems, VF_REQUIRE_APP_RESTART,
	               "Specifies the total number of events in a sequence that can be played back simultaneously.\n"
	               "Usage: s_Adx2MaxTrackItems [0/...]\n"
	               "Default PC: 32\n");

	REGISTER_CVAR2("s_Adx2MaxFaders", &m_maxFaders, m_maxFaders, VF_REQUIRE_APP_RESTART,
	               "Specifies the maximum number of faders used in the Atom library.\n"
	               "Usage: s_Adx2MaxFaders [0/...]\n"
	               "Default PC: 4\n");

	REGISTER_CVAR2("s_Adx2NumVoices", &m_numVoices, m_numVoices, VF_REQUIRE_APP_RESTART,
	               "Specifies the number of voices.\n"
	               "Usage: s_Adx2NumVoices [0/...]\n"
	               "Default PC: 8\n");

	REGISTER_CVAR2("s_Adx2MaxChannels", &m_maxChannels, m_maxChannels, VF_REQUIRE_APP_RESTART,
	               "Specifies the maximum number of channels that can be processed by a DSP.\n"
	               "Usage: s_Adx2MaxChannels [0/...]\n"
	               "Default PC: 2\n");

	REGISTER_CVAR2("s_Adx2MaxSamplingRate", &m_maxSamplingRate, m_maxSamplingRate, VF_REQUIRE_APP_RESTART,
	               "Specifies the maximum sampling rate that can be processed by a DSP.\n"
	               "Usage: s_Adx2MaxSamplingRate [0/...]\n"
	               "Default PC: 48000\n");

	REGISTER_CVAR2("s_Adx2NumBuses", &m_numBuses, m_numBuses, VF_REQUIRE_APP_RESTART,
	               "Specifies the number of buses.\n"
	               "Usage: s_Adx2NumBuses [0/...]\n"
	               "Default PC: 8\n");

	REGISTER_CVAR2("s_Adx2OutputChannels", &m_outputChannels, m_outputChannels, VF_REQUIRE_APP_RESTART,
	               "Specifies the number of output channels.\n"
	               "Usage: s_Adx2OutputChannels [0/...]\n"
	               "Default PC: 6\n");

	REGISTER_CVAR2("s_Adx2OutputSamplingRate", &m_outputSamplingRate, m_outputSamplingRate, VF_REQUIRE_APP_RESTART,
	               "Specifies the sampling rate.\n"
	               "Usage: s_Adx2OutputSamplingRate [0/...]\n"
	               "Default PC: 48000\n");

	REGISTER_CVAR2("s_Adx2MaxStreams", &m_maxStreams, m_maxStreams, VF_REQUIRE_APP_RESTART,
	               "Specifies the instantaneous maximum number of streamings.\n"
	               "Usage: s_Adx2MaxStreams [0/...]\n"
	               "Default PC: 8\n");

	REGISTER_CVAR2("s_Adx2MaxFiles", &m_maxFiles, m_maxFiles, VF_REQUIRE_APP_RESTART,
	               "Specifies the maximum number of files to open simultaneously.\n"
	               "Usage: s_Adx2MaxFiles [0/...]\n"
	               "Default PC: 32\n");

	REGISTER_CVAR2_CB("s_Adx2VoiceAllocationMethod", &m_voiceAllocationMethod, m_voiceAllocationMethod, VF_REQUIRE_APP_RESTART,
	                  "Specifies the method used when an AtomEx Player allocates voices.\n"
	                  "Usage: s_Adx2VoiceAllocationMethod [0/1]\n"
	                  "Default PC: 0\n"
	                  "0: Voice allocation is tried once.\n"
	                  "1: Voice allocation is tried as many times as needed.\n",
	                  SetVoiceAllocationMethod);

	REGISTER_CVAR2("s_Adx2MaxPitch", &m_maxPitch, m_maxPitch, VF_REQUIRE_APP_RESTART,
	               "Specifies the upper limit of the pitch change applied in the Atom library.\n"
	               "Usage: s_Adx2MaxPitch [0/...]\n"
	               "Default PC: 2400\n");
}

//////////////////////////////////////////////////////////////////////////
void CCVars::UnregisterVariables()
{
	IConsole* const pConsole = gEnv->pConsole;

	if (pConsole != nullptr)
	{
		pConsole->UnregisterVariable("s_Adx2MaxVirtualVoices");
		pConsole->UnregisterVariable("s_AdxMaxVoiceLimitGroups");
		pConsole->UnregisterVariable("s_Adx2MaxCategories");
		pConsole->UnregisterVariable("s_Adx2CategoriesPerPlayback");
		pConsole->UnregisterVariable("s_Adx2MaxTracks");
		pConsole->UnregisterVariable("s_Adx2MaxTrackItems");
		pConsole->UnregisterVariable("s_Adx2MaxFaders");
		pConsole->UnregisterVariable("s_Adx2NumVoices");
		pConsole->UnregisterVariable("s_Adx2MaxChannels");
		pConsole->UnregisterVariable("s_Adx2MaxSamplingRate");
		pConsole->UnregisterVariable("s_Adx2NumBuses");
		pConsole->UnregisterVariable("s_Adx2OutputChannels");
		pConsole->UnregisterVariable("s_Adx2OutputSamplingRate");
		pConsole->UnregisterVariable("s_Adx2MaxStreams");
		pConsole->UnregisterVariable("s_Adx2MaxFiles");
		pConsole->UnregisterVariable("s_Adx2VoiceAllocationMethod");
		pConsole->UnregisterVariable("s_Adx2MaxPitch");
	}
}
} // namespace Adx2
} // namespace Impl
} // namespace CryAudio
