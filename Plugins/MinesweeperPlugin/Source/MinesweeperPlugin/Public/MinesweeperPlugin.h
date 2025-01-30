#pragma once

#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;
class SMainWindow;
class FAIConnector;

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
    // Main window
    TSharedPtr<SMainWindow> m_mainWindow {nullptr};
    // AI connector to perform requests to Gemini
    TSharedPtr<FAIConnector> m_aiConnector {nullptr};

    // Methods
    void RegisterMenus();
};
