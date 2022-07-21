// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

AMyAIController::AMyAIController()
	: m_BehaviorTree(nullptr)
	, m_Blackboard(nullptr)
{
	
}

void AMyAIController::OnPossess(APawn* _mon)
{
	/* ���� �����Ǹ� AI ������ ���۵ǰ��Ѵ� */
	AAIController::OnPossess(_mon); // �� ��Ʈ�ѷ��� ���� �����ϵ��� ��û�ϴ� �Լ��Դϴ�.

	AMyMonster* pMonster = Cast<AMyMonster>(_mon);
	if (nullptr != pMonster)
	{
		m_BehaviorTree = pMonster->GetBehaviorTree();
		m_Blackboard = pMonster->GetBlackboard();

		UseBlackboard(m_Blackboard, Blackboard);
		RunBehaviorTree(m_BehaviorTree);
	}
}

void AMyAIController::OnUnPossess()
{
}
