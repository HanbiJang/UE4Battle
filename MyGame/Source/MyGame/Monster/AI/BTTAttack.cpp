// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTAttack.h"
#include "../MyMonster.h"


UBTTAttack::UBTTAttack()
{

}


EBTNodeResult::Type UBTTAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);
	//Succeeded,		// finished as success
	//Failed,			// finished as failure
	//Aborted,			// finished aborting = failure
	//InProgress,		// not finished yet

	// 동작 몬스터 가져오기
	AMyAIController* pController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pController)
		return EBTNodeResult::Type::Failed;

	AMyMonster* pMonster = Cast<AMyMonster>(pController->GetPawn());
	if (nullptr == pMonster)
		return EBTNodeResult::Type::Failed;

	// 공격 상태로 바꾼다.
	pMonster->ChangeState(EMON_STATE::ATTACK);

	// 이동을 멈춘다.
	pController->StopMovement();
	//pMonster->GetMovementComponent()->StopMovementImmediately();

	return EBTNodeResult::Type::Succeeded;
}

void UBTTAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/*if ()
	{
		FinishLatentAbort(OwnerComp);
	}*/
}

EBTNodeResult::Type UBTTAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return UBTTaskNode::AbortTask(OwnerComp, NodeMemory);
	//return Super::AbortTask(OwnerComp, NodeMemory);
}