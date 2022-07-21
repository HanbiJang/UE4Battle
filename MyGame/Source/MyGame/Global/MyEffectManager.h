// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyEffectEnum.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyEffectManager.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMyEffectManager : public UObject
{
	GENERATED_BODY()
	
private:
	static UMyEffectManager* m_This;
	static UWorld* m_World;

public:
	static UMyEffectManager* GetInst(UWorld* _world);
	static void Destroy();


public:
	void CreateEffect(EEFFECT _type, FTransform _trans, ULevel* _Level);

private:
	UMyEffectManager();
	~UMyEffectManager();
};
