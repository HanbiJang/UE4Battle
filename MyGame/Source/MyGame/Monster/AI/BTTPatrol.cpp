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


	// ���� ������ ��ġ�� �˾Ƴ��� �����忡 ����Ѵ�.
	FVector vPos = pMonster->GetNextPatrolPos();
	vPos.Z = pMonster->GetActorLocation().Z;
	pAI->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("NextPatrolPoint")), vPos);

	// ���� �������� ���ؼ� �̵��Ѵ�
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(pAI, vPos);

	// ������ �ִ� ���¸� ����� �ٲ۴�.
	pMonster->ChangeState(EMON_STATE::MOVE);

	bNotifyTick = 1;
	return EBTNodeResult::Type::InProgress;
}

void UBTTPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBTTaskNode::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// ������ �ӵ��� 0�� �����ϸ� �������� ����
	AMyAIController* pAI = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pAI)
		return;

	AMyMonster* pMonster = Cast<AMyMonster>(pAI->GetPawn());
	if (nullptr == pMonster)
		return;

	// �������� �����ߴ��� Ȯ��
	FVector vGoalPos = pAI->GetBlackboardComponent()->GetValueAsVector(FName(TEXT("NextPatrolPoint")));
	FVector vMonPos = pMonster->GetActorLocation();
	float fDistance = FVector::Distance(vGoalPos, vMonPos);

	if (EPathFollowingStatus::Idle == pAI->GetMoveStatus())
	{
		// �������� �����ϸ� 2�� �޽�
		pMonster->ChangeState(EMON_STATE::IDLE);

		// 2�ʴ��
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
