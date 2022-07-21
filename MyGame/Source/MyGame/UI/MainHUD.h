// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerHUD.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UPlayerHUD*						PlayerHUD;

public:
	UPlayerHUD* GetPlayerHUD(){return PlayerHUD;}
	
public:
	virtual void NativeConstruct() override;
};
