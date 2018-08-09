// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <CryCore/Project/CryModuleDefs.h>
#define eCryModule eCryM_AudioImplementation
#include <CryCore/Platform/platform.h>
#include <CryCore/StlUtils.h>
#include <CryCore/Project/ProjectDefines.h>
#include <CrySystem/ISystem.h>
#include <CrySystem/File/ICryPak.h>

#if !defined(_RELEASE)
	#define INCLUDE_ADX2_IMPL_PRODUCTION_CODE
#endif // _RELEASE

namespace CryAudio
{
namespace Impl
{
namespace Adx2
{

}      // Adx2
}      // Impl
}      // CryAudio
