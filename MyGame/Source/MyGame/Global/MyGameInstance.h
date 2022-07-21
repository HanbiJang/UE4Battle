// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyInfo.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

private:
	UDataTable* m_MonTable; //몬스터 데이터 테이블

	TSubclassOf<UCameraShakeBase>	m_CamShake; //카메라 블루프린트 클래스

public:
	const FMonInfo* GetMonInfo(const FString& _RowName);
	TSubclassOf<UCameraShakeBase> GetCameraShake() { return m_CamShake; }


public:
	UMyGameInstance();
	//~UMyGameInstance();
};
