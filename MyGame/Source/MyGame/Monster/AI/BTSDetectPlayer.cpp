// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSDetectPlayer.h"

UBTSDetectPlayer::UBTSDetectPlayer() {
	//�����ϱ�
	Interval = 1.f;

	RandomDeviation = 0.f;

	NodeName = TEXT("Detect Player");
}

/// <summary>
/// �÷��̾ ��ó�� �ִ��� Ȯ�� �� �� ���񽺸� �������ִ�(Ž��) ���͸� �����´�
/// �÷��̾ ��ó�� ������ ���� �������� Ÿ�ٿ� �����Ѵ�
/// </summary>
/// <param name="OwnerComp">�ൿƮ��</param>
/// <param name="NodeMemory">���޸�</param>
/// <param name="DeltaSeconds">�ð�</param>
void UBTSDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// �÷��̾ ��ó�� �ִ��� Ȯ���Ѵ�.
	// ���� ���񽺸� �����ϴ� ���͸� �����´�.
	AAIController* pController = OwnerComp.GetAIOwner();

	if (nullptr == pController)
		return;

	AMyMonster* pMonster = Cast<AMyMonster>(pController->GetPawn());

	if (nullptr == pMonster)
		return;

	// �÷��̾ �˾Ƴ���.
	AMyCharacter* pPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (nullptr == pPlayer)
		return;

	// ������ Ž�� ������, ���� ������ ��ġ��, �÷��̾��� ��ġ���� �����´�.
	float fDetectionRange = pMonster->GetInfo().fDetectRange;
	FVector vMonPos = pMonster->GetActorLocation();
	FVector vPlayerPos = pPlayer->GetActorLocation();

	float fDistance = FVector::Distance(vMonPos, vPlayerPos);

	// �÷��̾ �ش� ������ Ž������ �̳��� ������
	bool bDetect = false;
	if (fDetectionRange > fDistance)
	{
		// �÷��̾ Ÿ������ �����Ѵ� ==>  Blackboard �� �� ����
		pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), pPlayer);
		bDetect = true;
	}
	else
	{
		pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		// pMonster->ChangeState(EMON_STATE::IDLE);
	}

	//Ž�� ���� ����
#ifdef ENABLE_DRAW_DEBUG
	FColor color;
	bDetect ? color = FColor::Red : color = FColor::Green;
	DrawDebugSphere(GetWorld(), vMonPos, fDetectionRange, 40, color, false, 0.6f);
#endif
}
