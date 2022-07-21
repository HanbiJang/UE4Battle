// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <blueprint/UserWidget.h>
#include "UI/MainHUD.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMyGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		AMyGameGameModeBase();

private:

	TSubclassOf<UUserWidget>	m_MainHUDClass;
	TSubclassOf<UUserWidget>	m_TitleHUDClass;
	UMainHUD*					m_MainHUD;
		
public:
	virtual void BeginPlay() override;
	void UpdatePlayerHUD(float _CurHPRatio,float _CurMPRatio);
};
