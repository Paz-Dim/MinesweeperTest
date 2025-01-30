#pragma once

#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"

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

protected:
    // Fields
    // Request result field
    TSharedPtr<STextBlock> m_requestResult {nullptr};
    // Request input field
    TSharedPtr<SEditableTextBox> m_requestInput {nullptr};

    // Methods
    // Request button clicked
    FReply onRequestButtonClick();
};
