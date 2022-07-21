// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAIController.h"
#include "../../Global/MyCharacterStates.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTPatrol.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UBTTPatrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTPatrol();

protected:
	// �۾� ����
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// �۾� ���� �� �� ������ ȣ��
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// �۾� Ż��
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
