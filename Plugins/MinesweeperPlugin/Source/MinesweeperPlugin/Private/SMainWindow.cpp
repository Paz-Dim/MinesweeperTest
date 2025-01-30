#include "SMainWindow.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWindow::Construct(const FArguments &InArgs)
{
    ChildSlot
        .Padding(20.0f)
        [
            SNew(SVerticalBox)
                // Header
                + SVerticalBox::Slot()
                .AutoHeight()
                .HAlign(EHorizontalAlignment::HAlign_Center)
                .VAlign(EVerticalAlignment::VAlign_Center)
                [
                    SNew(STextBlock).Text(FText::FromString("Minesweeper"))
                        .Font(FSlateFontInfo("Slate/Fonts/Roboto-Bold.ttf", 20))
                ]
                // Game grid
                + SVerticalBox::Slot()
                .HAlign(EHorizontalAlignment::HAlign_Center)
                .VAlign(EVerticalAlignment::VAlign_Fill)
                [
                    SAssignNew(m_requestResult, STextBlock).Text(FText::FromString("TODO"))
                        .Font(FSlateFontInfo("Slate/Fonts/Roboto-Bold.ttf", 20))
                ]
                // Request block
                + SVerticalBox::Slot()
                .AutoHeight()
                .HAlign(EHorizontalAlignment::HAlign_Fill)
                .VAlign(EVerticalAlignment::VAlign_Center)
                [
                    SNew(SHorizontalBox)
                        // Input
                        + SHorizontalBox::Slot()
                        .HAlign(EHorizontalAlignment::HAlign_Fill)
                        .VAlign(EVerticalAlignment::VAlign_Center)
                        [
                            SAssignNew(m_requestInput, SEditableTextBox)
                                .BackgroundColor(FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f)))
                        ]
                        // Request button
                        + SHorizontalBox::Slot()
                        .AutoWidth()
                        .VAlign(EVerticalAlignment::VAlign_Center)
                        [
                            SNew(SButton)
                                .OnClicked(this, &SMainWindow::onRequestButtonClick)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("Request"))
                                ]
                        ]
                ]
        ];
}


void SMainWindow::httpResult(bool result, const FString &message)
{
    if (result)
        m_requestResult->SetColorAndOpacity(FSlateColor(FColor::Green));
    else
        m_requestResult->SetColorAndOpacity(FSlateColor(FColor::Red));
    m_requestResult->SetText(FText::FromString(message));
}


FReply SMainWindow::onRequestButtonClick()
{
    m_onSubmitRequest.Broadcast(m_requestInput->GetText().ToString());

    return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
