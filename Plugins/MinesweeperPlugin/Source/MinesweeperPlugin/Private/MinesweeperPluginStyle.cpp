// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinesweeperPluginStyle.h"
#include "MinesweeperPlugin.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FMinesweeperPluginStyle::StyleInstance = nullptr;

void FMinesweeperPluginStyle::Initialize()
{
    if (!StyleInstance.IsValid())
    {
        StyleInstance = Create();
        FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
    }
}

void FMinesweeperPluginStyle::Shutdown()
{
    FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
    ensure(StyleInstance.IsUnique());
    StyleInstance.Reset();
}

FName FMinesweeperPluginStyle::GetStyleSetName()
{
    static FName StyleSetName(TEXT("MinesweeperPluginStyle"));
    return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FMinesweeperPluginStyle::Create()
{
    TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("MinesweeperPluginStyle"));
    Style->SetContentRoot(IPluginManager::Get().FindPlugin("MinesweeperPlugin")->GetBaseDir() / TEXT("Resources"));

    Style->Set("MinesweeperPlugin.PluginAction", new IMAGE_BRUSH(TEXT("Icon20"), Icon20x20));
    return Style;
}

void FMinesweeperPluginStyle::ReloadTextures()
{
    if (FSlateApplication::IsInitialized())
    {
        FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
    }
}

const ISlateStyle &FMinesweeperPluginStyle::Get()
{
    return *StyleInstance;
}
