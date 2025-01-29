// Fill out your copyright notice in the Description page of Project Settings.


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
                    SNew(STextBlock).Text(FText::FromString("TODO"))
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


FReply SMainWindow::onRequestButtonClick()
{
    GEngine->AddOnScreenDebugMessage(-1,
                                     15.0f,
                                     FColor::Red,
                                     FString::Printf(TEXT("%s"), *m_requestInput->GetText().ToString()));
    return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
