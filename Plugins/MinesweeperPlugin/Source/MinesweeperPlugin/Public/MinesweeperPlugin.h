// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FMinesweeperPluginModule : public IModuleInterface
{
public:
    // Methods
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    /** This function will be bound to Command. */
    void PluginButtonClicked();

private:
    // Fields
    TSharedPtr<class FUICommandList> PluginCommands;

    // Methods
    void RegisterMenus();
};
