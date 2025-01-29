// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainWindow.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWindow::Construct(const FArguments &InArgs)
{
    ChildSlot
        [
            SNew(SVerticalBox)
                // Header
                + SVerticalBox::Slot()
                .AutoHeight()
                .HAlign(EHorizontalAlignment::HAlign_Center)
                .VAlign(EVerticalAlignment::VAlign_Center)
                [
                    SNew(STextBlock).Text(FText::FromString("Minesweeper"))
                ]
        ];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
