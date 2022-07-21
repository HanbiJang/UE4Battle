// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDIsInRange.h"
#include "../MyMonster.h"



UBTDIsInRange::UBTDIsInRange()
{
}

bool UBTDIsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = false; //결과값

	// 범위 체크를 진행하는 몬스터 알아내기
	AMyMonster* pMonster = Cast<AMyMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == pMonster)
		return false;

	const FMonInfo& info = pMonster->GetInfo();

	// 몬스터의 컨트롤러를 통해서 블랙보드에 등록된 플레이어 알아오기
	AMyAIController* pController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pController)
		return false;

	AMyCharacter* pPlayer = Cast<AMyCharacter>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (nullptr == pPlayer)
		return false;

	// 플레이어와 몬스터의 거리를 구한다.
	float fDistance = FVector::Distance(pMonster->GetActorLocation(), pPlayer->GetActorLocation());

	// 비교할 범위 타입에 따라서 거리가 해당 범위이내에 있는지 체크
	if (ERANGE_TYPE::DETECTION == m_Type)
	{
		if (fDistance < info.fDetectRange)
		{
			bResult = true;
		}
	}
	else if (ERANGE_TYPE::ATTACK == m_Type)
	{
		if (fDistance < info.fAttackRange)
		{
			bResult = true;
		}
	}

	return bResult;
}