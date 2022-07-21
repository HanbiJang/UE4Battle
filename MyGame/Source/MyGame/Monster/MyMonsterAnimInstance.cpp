// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMonsterAnimInstance.h"

UMyMonsterAnimInstance::UMyMonsterAnimInstance() {

}

void UMyMonsterAnimInstance::NativeInitializeAnimation()
{
	// 객체 생성 시
}
void UMyMonsterAnimInstance::NativeBeginPlay()
{
	// 게임 시작 시
}

void UMyMonsterAnimInstance::NativeUpdateAnimation(float _fDT)
{
	// 게임 시작 후 매프레임마다 호출됨
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (nullptr != pMonster)
	{
		UCharacterMovementComponent* pMovementComponent = pMonster->GetCharacterMovement();
		m_fSpeed = pMovementComponent->Velocity.Size(); //속도
		m_eState = pMonster->GetState(); //상태
		m_bGround = pMonster->GetMovementComponent()->IsMovingOnGround(); //땅에 있는지 여부

	}
}

void UMyMonsterAnimInstance::AnimNotify_OnAttakTrigger()
{
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (nullptr != pMonster)
	{
		pMonster->OnAttakTrigger();
	}

}

void UMyMonsterAnimInstance::AnimNotify_NormalMon_AttEnd()
{
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (nullptr != pMonster)
	{
		// 공격 동작에 의한 경직을 풀어 줌
		pMonster->SetUnStopable(false);
	}
}

void UMyMonsterAnimInstance::AnimNotify_HitEnd() {
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (nullptr != pMonster)
	{
		// 히트 모션에 의한 경직을 풀어 줌
		pMonster->SetUnStopable(false);
	}
}

void UMyMonsterAnimInstance::AnimNotify_DeadEnd() {
	//죽기
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());
	pMonster->Destroy();
}

void UMyMonsterAnimInstance::AnimNotify_Idle()
{
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (pMonster)
		pMonster->ChangeState(EMON_STATE::IDLE);
}