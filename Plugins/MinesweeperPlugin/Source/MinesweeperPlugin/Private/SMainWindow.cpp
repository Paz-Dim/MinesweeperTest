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
    TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();
    httpRequest->SetVerb("POST");
    httpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    httpRequest->SetContentAsString(*FString::Printf(TEXT("{'contents': [{'parts':[{'text': '%s. Show only result, use X for empty cells and O for mines. Skip extra lines.'}]}]}"),
                                    *m_requestInput->GetText().ToString()));
    httpRequest->SetURL(TEXT("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=AIzaSyByLZNRcZviFG-nf2E2RjEkzm4W4mxWIK0"));
    httpRequest->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr httpRequest, FHttpResponsePtr httpResponse, bool bSucceeded)
    {
        if (!bSucceeded)
            GEngine->AddOnScreenDebugMessage(-1,
                                             15.0f,
                                             FColor::Red,
                                             FString::Printf(TEXT("HTTP request failed")));
        else if (httpResponse->GetResponseCode() != 200)
            GEngine->AddOnScreenDebugMessage(-1,
                                             15.0f,
                                             FColor::Red,
                                             FString::Printf(TEXT("HTTP request error %d"), httpResponse->GetResponseCode()));
        else
        {
            TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
            TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(httpResponse->GetContentAsString());
            if (FJsonSerializer::Deserialize(jsonReader, jsonObject))
            {
                TArray<TSharedPtr<FJsonValue>> candidates = jsonObject->GetArrayField("candidates");
                if (candidates.IsEmpty())
                    GEngine->AddOnScreenDebugMessage(-1,
                                                     15.0f,
                                                     FColor::Red,
                                                     FString::Printf(TEXT("Candidates empty")));
                else
                {
                    TSharedPtr<FJsonObject> content = candidates[0]->AsObject()->GetObjectField("content");
                    if (!content)
                        GEngine->AddOnScreenDebugMessage(-1,
                                                         15.0f,
                                                         FColor::Red,
                                                         FString::Printf(TEXT("No content")));
                    else
                    {
                        TArray<TSharedPtr<FJsonValue>> parts = content->GetArrayField("parts");
                        if (parts.IsEmpty())
                            GEngine->AddOnScreenDebugMessage(-1,
                                                             15.0f,
                                                             FColor::Red,
                                                             FString::Printf(TEXT("Parts empty")));
                        else
                        {
                            GEngine->AddOnScreenDebugMessage(-1,
                                                             15.0f,
                                                             FColor::Red,
                                                             FString::Printf(TEXT("Part %d"), parts.Num()));
                            GEngine->AddOnScreenDebugMessage(-1,
                                                             15.0f,
                                                             FColor::Red,
                                                             FString::Printf(TEXT("Part |%s|"), *parts[0]->AsObject()->GetStringField("text")));
                        }
                    }
                }
            }
            else
                GEngine->AddOnScreenDebugMessage(-1,
                                                 15.0f,
                                                 FColor::Red,
                                                 FString::Printf(TEXT("Parse error %s"), *httpResponse->GetContentAsString()));
        }
    });
    httpRequest->ProcessRequest();

    return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
