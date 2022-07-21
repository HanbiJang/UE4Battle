// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MyMonster.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()

private:
	UBehaviorTree* m_BehaviorTree; //행동트리
	UBlackboardData* m_Blackboard; //블랙보드


public:
	AMyAIController();


public:
	virtual void OnPossess(APawn* _mon) override;
	virtual void OnUnPossess() override;
	
};
