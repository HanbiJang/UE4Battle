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
	// �۾� ����
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// �۾� ���� �� �� ������ ȣ��
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// �۾� Ż��
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
