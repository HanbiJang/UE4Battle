// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTTrace.h"

#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "MyAIController.h"
#include "../MyMonster.h"
#include "../../Player/MyCharacter.h"


UBTTTrace::UBTTTrace()
{

}

EBTNodeResult::Type UBTTTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//AAIController* pController = OwnerComp.GetAIOwner();
	////�����忡�� ���� Ÿ�� ������
	//AMyCharacter* pPlayer = Cast<AMyCharacter>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	////���͸� �����´�
	//AMyMonster* pMonster = Cast<AMyMonster>(pController->GetPawn());
	//if (nullptr == pMonster)
	//	return EBTNodeResult::Type::Failed;

	//pMonster->ChangeState(EMON_STATE::MOVE);

	//// �̵� ���·� ���������� ������� �ʾҴٸ� �̵���� ���� ����
	//if (pMonster->GetState() != EMON_STATE::MOVE)
	//	return EBTNodeResult::Type::Failed;

	//// ������ ���¸� MOVE ���·� �����.
	//pMonster->ChangeState(EMON_STATE::MOVE);
	//// �÷��̾��� ��ġ�� �̵��Ѵ�.
	//UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pPlayer);

	//return EBTNodeResult::Type::Succeeded;

	///����
	AAIController* pController = OwnerComp.GetAIOwner();
	AMyCharacter* pPlayer = Cast<AMyCharacter>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// ������ ���¸� MOVE ���·� �����.
	AMyMonster* pMonster = Cast<AMyMonster>(pController->GetPawn());
	if (nullptr == pMonster)
		return EBTNodeResult::Type::Succeeded;

	pMonster->ChangeState(EMON_STATE::MOVE);

	// �̵� ���·� ���������� ������� �ʾҴٸ� �̵���� ���� ����
	if (pMonster->GetState() != EMON_STATE::MOVE)
		return EBTNodeResult::Type::Succeeded;


	// �÷��̾��� ��ġ�� �̵��Ѵ�.
	UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pPlayer);
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, pPlayer->GetActorLocation());

	return EBTNodeResult::Type::Succeeded;
}

void UBTTTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	return Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

EBTNodeResult::Type UBTTTrace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
