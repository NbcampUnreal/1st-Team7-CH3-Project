// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define CP_LOG(Verbosity, Format, ...) UE_LOG(CPLog, Verbosity, TEXT("%s(%s) %s"), LOG_CALLINFO, *FString::FromInt(__LINE__), *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(CPLog, Log, All);