// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTTrace.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UBTTTrace : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTTrace();

protected:
	// �۾� ����
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// �۾� ���� �� �� ������ ȣ��
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// �۾� Ż��
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
