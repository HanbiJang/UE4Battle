// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSDetectPlayer.h"

UBTSDetectPlayer::UBTSDetectPlayer() {
	//설정하기
	Interval = 1.f;

	RandomDeviation = 0.f;

	NodeName = TEXT("Detect Player");
}

/// <summary>
/// 플레이어가 근처에 있는지 확인 후 이 서비스를 돌리고있는(탐지) 몬스터를 가져온다
/// 플레이어가 근처에 있으면 몬스터 블랙보드의 타겟에 설정한다
/// </summary>
/// <param name="OwnerComp">행동트리</param>
/// <param name="NodeMemory">노드메모리</param>
/// <param name="DeltaSeconds">시간</param>
void UBTSDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 플레이어가 근처에 있는지 확인한다.
	// 현재 서비스를 실행하는 몬스터를 가져온다.
	AAIController* pController = OwnerComp.GetAIOwner();

	if (nullptr == pController)
		return;

	AMyMonster* pMonster = Cast<AMyMonster>(pController->GetPawn());

	if (nullptr == pMonster)
		return;

	// 플레이어를 알아낸다.
	AMyCharacter* pPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (nullptr == pPlayer)
		return;

	// 몬스터의 탐지 범위와, 몬스터 본인의 위치값, 플레이어의 위치값을 가져온다.
	float fDetectionRange = pMonster->GetInfo().fDetectRange;
	FVector vMonPos = pMonster->GetActorLocation();
	FVector vPlayerPos = pPlayer->GetActorLocation();

	float fDistance = FVector::Distance(vMonPos, vPlayerPos);

	// 플레이어가 해당 몬스터의 탐지범위 이내에 있으면
	bool bDetect = false;
	if (fDetectionRange > fDistance)
	{
		// 플레이어를 타겟으로 설정한다 ==>  Blackboard 에 값 세팅
		pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), pPlayer);
		bDetect = true;
	}
	else
	{
		pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		// pMonster->ChangeState(EMON_STATE::IDLE);
	}

	//탐지 범위 보기
#ifdef ENABLE_DRAW_DEBUG
	FColor color;
	bDetect ? color = FColor::Red : color = FColor::Green;
	DrawDebugSphere(GetWorld(), vMonPos, fDetectionRange, 40, color, false, 0.6f);
#endif
}
