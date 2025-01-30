#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Components/UniformGridSlot.h"

#include "MatrixArray.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubmitRequest, const FString &/*Request*/);
DECLARE_DELEGATE_TwoParams(FOnGridClick, int32 /*X*/, int32 /*Y*/);

/**
 *
 */
class MINESWEEPERPLUGIN_API SMainWindow : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMainWindow)
        {}
    SLATE_END_ARGS()

    // Fields
    // Request delegate
    FOnSubmitRequest m_onSubmitRequest;
    // Grid element clicked delegate
    FOnGridClick m_onClicked;

    // Methods
    /** Constructs this widget with InArgs */
    void Construct(const FArguments &InArgs);
    // HTTP request result
    void httpResult(bool result, const FString &message);
    // Reset game field
    void resetField(int32 width, int32 height);
    // Open grid element
    void openElement(int32 x, int32 y, const FText &label, bool mine);

protected:
    // Types
    // Grid element
    class SGridElement : public SCompoundWidget
    {
    public:
        SLATE_BEGIN_ARGS(SMainWindow)
            {}
        SLATE_END_ARGS()

        // Fields
        // Element clicked delegate
        FOnGridClick m_onClicked;
        // Element coordinates <x, y>
        TPair<int32, int32> m_pos;

        // Methods
        /** Constructs this widget with InArgs */
        void Construct(const FArguments &InArgs);
        // Open element
        void open(int32 x, int32 y, const FText &label, bool mine);

    protected:
        // Constants
        // Hidden color
        static const FSlateColor HIDDEN_COLOR;
        // Open color
        static const FLinearColor OPEN_COLOR;
        // Mine color
        static const FLinearColor MINE_COLOR;

        // Fields
        // Button
        TSharedPtr<SButton> m_button {nullptr};
        // Label
        TSharedPtr<STextBlock> m_label {nullptr};

        // Methods
        // Click event
        FReply clicked();
    };

    // Fields
    // Request result field
    TSharedPtr<STextBlock> m_requestResult {nullptr};
    // Request input field
    TSharedPtr<SEditableTextBox> m_requestInput {nullptr};
    // Game grid widget
    TSharedPtr<SUniformGridPanel> m_gameGrid {nullptr};
    // Matrix of grid elements
    FMatrixArray<TSharedPtr<SGridElement>> m_elements;

    // Methods
    // Request button clicked
    FReply onRequestButtonClick();
    // Element clicked
    void elementClicked(int32 x, int32 y);
};
