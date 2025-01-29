// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

class FMinesweeperPluginStyle
{
public:
    // Methods
    static void Initialize();
    static void Shutdown();
    /** reloads textures used by slate renderer */
    static void ReloadTextures();
    /** @return The Slate style set for the Shooter game */
    static const ISlateStyle &Get();
    static FName GetStyleSetName();

private:
    // Fields
    static TSharedPtr< class FSlateStyleSet > StyleInstance;

    // Methods
    static TSharedRef< class FSlateStyleSet > Create();
};