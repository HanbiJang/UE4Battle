// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDIsInRange.h"
#include "../MyMonster.h"



UBTDIsInRange::UBTDIsInRange()
{
}

bool UBTDIsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = false; //�����

	// ���� üũ�� �����ϴ� ���� �˾Ƴ���
	AMyMonster* pMonster = Cast<AMyMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == pMonster)
		return false;

	const FMonInfo& info = pMonster->GetInfo();

	// ������ ��Ʈ�ѷ��� ���ؼ� �����忡 ��ϵ� �÷��̾� �˾ƿ���
	AMyAIController* pController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pController)
		return false;

	AMyCharacter* pPlayer = Cast<AMyCharacter>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (nullptr == pPlayer)
		return false;

	// �÷��̾�� ������ �Ÿ��� ���Ѵ�.
	float fDistance = FVector::Distance(pMonster->GetActorLocation(), pPlayer->GetActorLocation());

	// ���� ���� Ÿ�Կ� ���� �Ÿ��� �ش� �����̳��� �ִ��� üũ
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