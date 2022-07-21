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
	////블랙보드에서 현재 타겟 가져옴
	//AMyCharacter* pPlayer = Cast<AMyCharacter>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	////몬스터를 가져온다
	//AMyMonster* pMonster = Cast<AMyMonster>(pController->GetPawn());
	//if (nullptr == pMonster)
	//	return EBTNodeResult::Type::Failed;

	//pMonster->ChangeState(EMON_STATE::MOVE);

	//// 이동 상태로 정상적으로 변경되지 않았다면 이동명령 없이 종료
	//if (pMonster->GetState() != EMON_STATE::MOVE)
	//	return EBTNodeResult::Type::Failed;

	//// 몬스터의 상태를 MOVE 상태로 만든다.
	//pMonster->ChangeState(EMON_STATE::MOVE);
	//// 플레이어의 위치로 이동한다.
	//UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pPlayer);

	//return EBTNodeResult::Type::Succeeded;

	///변경
	AAIController* pController = OwnerComp.GetAIOwner();
	AMyCharacter* pPlayer = Cast<AMyCharacter>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// 몬스터의 상태를 MOVE 상태로 만든다.
	AMyMonster* pMonster = Cast<AMyMonster>(pController->GetPawn());
	if (nullptr == pMonster)
		return EBTNodeResult::Type::Succeeded;

	pMonster->ChangeState(EMON_STATE::MOVE);

	// 이동 상태로 정상적으로 변경되지 않았다면 이동명령 없이 종료
	if (pMonster->GetState() != EMON_STATE::MOVE)
		return EBTNodeResult::Type::Succeeded;


	// 플레이어의 위치로 이동한다.
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
