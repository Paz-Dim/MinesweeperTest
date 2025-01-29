// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class MINESWEEPERPLUGIN_API SMainWindow : public SCompoundWidget
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
    // Google Gemini request format
    static const FString HTTP_REQUEST_FORMAT;
    // Google Gemeni API URL
    static const FString HTTP_REQUEST_URL;

    // Fields
    // Request input field
    TSharedPtr<SEditableTextBox> m_requestInput {nullptr};

    // Methods
    // Request button clicked
    FReply onRequestButtonClick();
};
