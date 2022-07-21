// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTPatrol.h"
#include "../MyMonster.h"



UBTTPatrol::UBTTPatrol()
{

}

EBTNodeResult::Type UBTTPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

	AMyAIController* pAI = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pAI)
		return EBTNodeResult::Type::Failed;

	//ANormalMonster* pMonster = Cast<ANormalMonster>(pAI->GetPawn());
	AMyMonster* pMonster = Cast<AMyMonster>(pAI->GetPawn());
	if (nullptr == pMonster)
		return EBTNodeResult::Type::Failed;


	// 다음 목적지 위치를 알아내서 블랙보드에 등록한다.
	FVector vPos = pMonster->GetNextPatrolPos();
	vPos.Z = pMonster->GetActorLocation().Z;
	pAI->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("NextPatrolPoint")), vPos);

	// 다음 목적지를 향해서 이동한다
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(pAI, vPos);

	// 몬스터의 애님 상태를 무브로 바꾼다.
	pMonster->ChangeState(EMON_STATE::MOVE);

	bNotifyTick = 1;
	return EBTNodeResult::Type::InProgress;
}

void UBTTPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBTTaskNode::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 몬스터의 속도가 0에 도달하면 목적지에 도착
	AMyAIController* pAI = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pAI)
		return;

	AMyMonster* pMonster = Cast<AMyMonster>(pAI->GetPawn());
	if (nullptr == pMonster)
		return;

	// 목적지에 도착했는지 확인
	FVector vGoalPos = pAI->GetBlackboardComponent()->GetValueAsVector(FName(TEXT("NextPatrolPoint")));
	FVector vMonPos = pMonster->GetActorLocation();
	float fDistance = FVector::Distance(vGoalPos, vMonPos);

	if (EPathFollowingStatus::Idle == pAI->GetMoveStatus())
	{
		// 목적지에 도착하면 2초 휴식
		pMonster->ChangeState(EMON_STATE::IDLE);

		// 2초대기
		float fAccTime = pAI->GetBlackboardComponent()->GetValueAsFloat(FName(TEXT("AccTime")));
		fAccTime += DeltaSeconds;
		pAI->GetBlackboardComponent()->SetValueAsFloat(FName(TEXT("AccTime")), fAccTime);

		if (2.f < fAccTime)
		{
			pAI->GetBlackboardComponent()->SetValueAsFloat(FName(TEXT("AccTime")), 0.f);
			FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		}
	}
}

EBTNodeResult::Type UBTTPatrol::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBTTaskNode::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type::Succeeded;
}
