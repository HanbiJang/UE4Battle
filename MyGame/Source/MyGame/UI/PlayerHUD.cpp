// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PMyMP")));
	//m_TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
}

void UPlayerHUD::NativeTick(const FGeometry& Geometry, float DT)
{
	Super::NativeTick(Geometry, DT);
}

// void UPlayerHUD::SetText(const FString& _Name)
// {
// 	if (nullptr == m_TextBlock)
// 	{
// 		m_TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
// 		m_TextBlock->SetText(FText::FromString(_Name));
// 	}
// 	else
// 	{
// 		m_TextBlock->SetText(FText::FromString(_Name));
// 	}
// }

