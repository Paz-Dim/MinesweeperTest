#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Components/UniformGridSlot.h"

#include "MatrixArray.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubmitRequest, const FString &/*Request*/);

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

    // Methods
    /** Constructs this widget with InArgs */
    void Construct(const FArguments &InArgs);
    // HTTP request result
    void httpResult(bool result, const FString &message);
    // Reset game field
    void resetField(int32 width, int32 height);

protected:
    // Types
    // Grid element
    class SGridElement : public SCompoundWidget
    {
    public:
        SLATE_BEGIN_ARGS(SMainWindow)
            {}
        SLATE_END_ARGS()

        // Methods
        /** Constructs this widget with InArgs */
        void Construct(const FArguments &InArgs);

    protected:
        // Constants
        // Hidden color
        static const FSlateColor HIDDEN_COLOR;

        // Fields
        // Button
        TSharedPtr<SButton> m_button {nullptr};

        // Methods
        // Click event
        FReply clicked();
    };

    // Fields
    // Request result field
    TSharedPtr<STextBlock> m_requestResult {nullptr};
    // Request input field
    TSharedPtr<SEditableTextBox> m_requestInput {nullptr};
    // Game grid
    TSharedPtr<SUniformGridPanel> m_gameGrid {nullptr};

    // Methods
    // Request button clicked
    FReply onRequestButtonClick();
};
