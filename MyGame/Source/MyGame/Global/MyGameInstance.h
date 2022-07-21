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
	UDataTable* m_MonTable; //���� ������ ���̺�

	TSubclassOf<UCameraShakeBase>	m_CamShake; //ī�޶� �������Ʈ Ŭ����

public:
	const FMonInfo* GetMonInfo(const FString& _RowName);
	TSubclassOf<UCameraShakeBase> GetCameraShake() { return m_CamShake; }


public:
	UMyGameInstance();
	//~UMyGameInstance();
};
