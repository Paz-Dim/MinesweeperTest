#include "AIConnector.h"

const FString FAIConnector::HTTP_REQUEST_FORMAT {"{'contents': [{'parts':[{'text': '{0}. Count rows, cols and mines carefully. Show only result, use X for empty cells and O for mines. Skip extra lines.'}]}]}"};
const FString FAIConnector::HTTP_REQUEST_URL {"https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=AIzaSyByLZNRcZviFG-nf2E2RjEkzm4W4mxWIK0"};

void FAIConnector::performRequest(const FString &request)
{
    // Start request to Google Gemini
    TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();
    httpRequest->SetVerb("POST");
    httpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    httpRequest->SetContentAsString(FString::Format(*HTTP_REQUEST_FORMAT, {request}));
    httpRequest->SetURL(*HTTP_REQUEST_URL);
    httpRequest->OnProcessRequestComplete().BindRaw(this, &FAIConnector::httpRequestCallback);
    httpRequest->ProcessRequest();
}


void FAIConnector::httpRequestCallback(FHttpRequestPtr httpRequest, FHttpResponsePtr httpResponse, bool bSucceeded)
{
    if (!bSucceeded)
        m_onRequestResultUI.Broadcast(false, FString("HTTP request failed"));
    else if (httpResponse->GetResponseCode() != 200)
        m_onRequestResultUI.Broadcast(false, FString::Printf(TEXT("HTTP request error %d %s"),
                                           httpResponse->GetResponseCode(),
                                           *httpResponse->GetContentAsString()));
    else
    {
        TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
        TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(httpResponse->GetContentAsString());
        if (!FJsonSerializer::Deserialize(jsonReader, jsonObject))
            m_onRequestResultUI.Broadcast(false, FString::Printf(TEXT("Parse error %s"), *httpResponse->GetContentAsString()));
        else
        {
            TArray<TSharedPtr<FJsonValue>> candidates = jsonObject->GetArrayField(TEXT("candidates"));
            if (candidates.IsEmpty())
                m_onRequestResultUI.Broadcast(false, FString("Candidates empty"));
            else
            {
                TSharedPtr<FJsonObject> content = candidates[0]->AsObject()->GetObjectField(TEXT("content"));
                if (!content)
                    m_onRequestResultUI.Broadcast(false, FString("No content"));
                else
                {
                    TArray<TSharedPtr<FJsonValue>> parts = content->GetArrayField(TEXT("parts"));
                    if (parts.IsEmpty())
                        m_onRequestResultUI.Broadcast(false, FString("Parts empty"));
                    else
                        m_onRequestResultUI.Broadcast(true, parts[0]->AsObject()->GetStringField(TEXT("text")));
                }
            }
        }
    }
}
