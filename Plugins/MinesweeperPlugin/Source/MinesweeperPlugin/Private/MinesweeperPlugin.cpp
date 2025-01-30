#include "MinesweeperPlugin.h"
#include "MinesweeperPluginStyle.h"
#include "MinesweeperPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "SMainWindow.h"
#include "AIConnector.h"

static const FName MinesweeperPluginTabName("MinesweeperPlugin");

#define LOCTEXT_NAMESPACE "FMinesweeperPluginModule"

void FMinesweeperPluginModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    FMinesweeperPluginStyle::Initialize();
    FMinesweeperPluginStyle::ReloadTextures();

    FMinesweeperPluginCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    PluginCommands->MapAction(
        FMinesweeperPluginCommands::Get().PluginAction,
        FExecuteAction::CreateRaw(this, &FMinesweeperPluginModule::PluginButtonClicked),
        FCanExecuteAction());

    // Create plugin components
    m_aiConnector = MakeShared<FAIConnector>();

    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMinesweeperPluginModule::RegisterMenus));
}

void FMinesweeperPluginModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.
    UToolMenus::UnRegisterStartupCallback(this);

    // Clear components connections
    m_aiConnector->m_onRequestResultUI.Clear();

    UToolMenus::UnregisterOwner(this);

    FMinesweeperPluginStyle::Shutdown();

    FMinesweeperPluginCommands::Unregister();
}

void FMinesweeperPluginModule::PluginButtonClicked()
{
    auto MyWindow = SNew(SWindow).ClientSize({600.0f, 400.0f})
        [
            SAssignNew(m_mainWindow, SMainWindow)
        ];

    // Connect created window to other components
    m_mainWindow->m_onSubmitRequest.AddSP(m_aiConnector.ToSharedRef(), &FAIConnector::performRequest);
    m_aiConnector->m_onRequestResultUI.AddSP(m_mainWindow.ToSharedRef(), &SMainWindow::httpResult);

    FSlateApplication::Get().AddWindow(MyWindow, true);
}

void FMinesweeperPluginModule::RegisterMenus()
{
    // Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
    FToolMenuOwnerScoped OwnerScoped(this);

    {
        UToolMenu *Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
        {
            FToolMenuSection &Section = Menu->FindOrAddSection("WindowLayout");
            Section.AddMenuEntryWithCommandList(FMinesweeperPluginCommands::Get().PluginAction, PluginCommands);
        }
    }

    {
        UToolMenu *ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
        {
            FToolMenuSection &Section = ToolbarMenu->FindOrAddSection("PluginTools");
            {
                FToolMenuEntry &Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMinesweeperPluginCommands::Get().PluginAction));
                Entry.SetCommandList(PluginCommands);
            }
        }
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMinesweeperPluginModule, MinesweeperPlugin)