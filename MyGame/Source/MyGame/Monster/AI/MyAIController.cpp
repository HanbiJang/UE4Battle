// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

AMyAIController::AMyAIController()
	: m_BehaviorTree(nullptr)
	, m_Blackboard(nullptr)
{
	
}

void AMyAIController::OnPossess(APawn* _mon)
{
	/* 폰이 소유되면 AI 로직이 시작되게한다 */
	AAIController::OnPossess(_mon); // 이 컨트롤러가 폰을 소유하도록 요청하는 함수입니다.

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
