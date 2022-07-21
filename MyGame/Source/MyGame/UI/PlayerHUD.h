// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include <components/progressbar.h>
#include <components/TextBlock.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
	
	//블루프린트의 위젯 내용 가져오기ㅣ
private:
	UWidget* m_playerHUD;
	UProgressBar*	m_MPBar;
	//UTextBlock*		m_TextBlock;

public:
	void SetMP(float _fRatio){m_MPBar->SetPercent(_fRatio);};
	//void SetText(const FString& _Name);
	UWidget* GetPlayerHUD(){return m_playerHUD;};
	UProgressBar* GetPlayerMPBar(){return m_MPBar;};

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DT) override;

};
