#include "SMainWindow.h"
#include "SlateOptMacros.h"

const FSlateColor SMainWindow::SGridElement::HIDDEN_COLOR {FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))};
const FLinearColor SMainWindow::SGridElement::OPEN_COLOR {FLinearColor(0.0f, 1.0f, 0.0f, 1.0f)};
const FLinearColor SMainWindow::SGridElement::MINE_COLOR {FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)};

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWindow::Construct(const FArguments &InArgs)
{
    ChildSlot
        .Padding(20.0f)
        .HAlign(EHorizontalAlignment::HAlign_Fill)
        [
            SNew(SVerticalBox)
                // Header
                + SVerticalBox::Slot()
                .AutoHeight()
                .HAlign(EHorizontalAlignment::HAlign_Center)
                .VAlign(EVerticalAlignment::VAlign_Center)
                [
                    SNew(STextBlock)
                        .Text(FText::FromString("Minesweeper"))
                        .Font(FSlateFontInfo("Slate/Fonts/Roboto-Bold.ttf", 20))
                ]
                // Game part
                + SVerticalBox::Slot()
                .HAlign(EHorizontalAlignment::HAlign_Fill)
                .VAlign(EVerticalAlignment::VAlign_Fill)
                [
                    SNew(SHorizontalBox)
                        // Game grid
                        + SHorizontalBox::Slot()
                        .AutoWidth()
                        .HAlign(EHorizontalAlignment::HAlign_Center)
                        .VAlign(EVerticalAlignment::VAlign_Center)
                        [
                            SAssignNew(m_gameGrid, SUniformGridPanel)
                        ]
                        // Request result
                        + SHorizontalBox::Slot()
                        .AutoWidth()
                        .HAlign(EHorizontalAlignment::HAlign_Center)
                        .VAlign(EVerticalAlignment::VAlign_Center)
                        [
                            SAssignNew(m_requestResult, STextBlock)
                                .Text(FText::FromString(""))
                                .Font(FSlateFontInfo("Slate/Fonts/Roboto-Bold.ttf", 16))
                        ]
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


void SMainWindow::resetField(int32 width, int32 height)
{
    // Remove old grid
    m_gameGrid->ClearChildren();
    m_elements.setSize(width, height, TSharedPtr<SGridElement>());

    TSharedPtr<SGridElement> newElem;
    for (int32 iX = 0; iX < width; iX++)
        for (int32 iY = 0; iY < height; iY++)
        {
            m_gameGrid->AddSlot(iX, iY)
                [
                    SAssignNew(newElem, SGridElement)
                ];
            newElem->m_pos = TPair<int32, int32>(iX, iY);
            newElem->m_onClicked.BindSP(this, &SMainWindow::elementClicked);
            m_elements.setElem(iX, iY, newElem);
        }
}


void SMainWindow::openElement(int32 x, int32 y, const FText &label, bool mine)
{
    m_elements.getElem(x, y)->open(x, y, label, mine);
}


FReply SMainWindow::onRequestButtonClick()
{
    m_onSubmitRequest.Broadcast(m_requestInput->GetText().ToString());

    return FReply::Handled();
}


void SMainWindow::elementClicked(int32 x, int32 y)
{
    m_onClicked.ExecuteIfBound(x, y);
}


void SMainWindow::SGridElement::Construct(const FArguments &InArgs)
{
    ChildSlot
        .Padding(5.0f)
        [
            // Button to process clicks
            SAssignNew(m_button, SButton)
                .HAlign(EHorizontalAlignment::HAlign_Fill)
                .VAlign(EVerticalAlignment::VAlign_Fill)
                .ButtonColorAndOpacity(HIDDEN_COLOR)
                .OnClicked(this, &SGridElement::clicked)
                [
                    // Label to show mines number
                    SAssignNew(m_label, STextBlock)
                        .Margin(20.0f)
                        .ColorAndOpacity(FColor::Black)
                        .Font(FSlateFontInfo("Slate/Fonts/Roboto-Bold.ttf", 12))
                ]
        ];
}


void SMainWindow::SGridElement::open(int32 x, int32 y, const FText &label, bool mine)
{
    m_button->SetEnabled(false);
    if (mine)
        m_button->SetBorderBackgroundColor(MINE_COLOR);
    else
        m_button->SetBorderBackgroundColor(OPEN_COLOR);
    m_label->SetText(label);
}


FReply SMainWindow::SGridElement::clicked()
{
    m_onClicked.ExecuteIfBound(m_pos.Key, m_pos.Value);

    return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
