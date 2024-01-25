#pragma once
#define Print(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White,TEXT(Text), false);
#define PrintKey(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 15.f, FColor::White, TEXT(Text));
#define PrintFormat(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT(Format), ##__VA_ARGS__), false);
#define PrintFormatShort(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, FString::Printf(TEXT(Format), ##__VA_ARGS__), false);
#define PrintKeyFormat(Key, Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 15.f, FColor::White, FString::Printf(TEXT(Format), ##__VA_ARGS__));
#define Warn(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,TEXT(Text), false);
#define WarnKey(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 15.f, FColor::Yellow, TEXT(Text));
#define WarnFormat(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__), false);
#define WarnKeyFormat(Key, Format, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(Key, 15.f, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__));
#define PrintColor(Color, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, Color, TEXT(Text), false);
#define PrintCustom(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, Text, false);
#define WarnCustom(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, Text, false);
#define PrintKey_PathPoint 1