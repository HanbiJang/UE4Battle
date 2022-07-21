// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAIController.h"
#include "../../Global/MyCharacterStates.h"
#include "MyGame/Player/MyCharacter.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UBTTAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTAttack();

protected:
	// 작업 진입
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// 작업 진행 중 매 프레임 호출
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// 작업 탈출
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
