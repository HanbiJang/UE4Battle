// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "MyCharacter.h"

UMyAnimInstance::UMyAnimInstance()
	: m_fSpeed(0.f)
	, m_fDirection(0.f)
	, m_eState(EPLAYER_STATE::IDLE)
	, m_bGround(false)
	,m_Attack01(false)
	,m_Attack02(false)
	, m_Attack01ComboEnable(false)
	, m_Jump2(false)
	, m_Attack02ComboEnable(false)
	, m_JumpComboEnable(false)
	, m_JumpEnd(false)
	, m_AttackEnd(false)
{}
void UMyAnimInstance::NativeInitializeAnimation()
{
	// 객체 생성 시
}
void UMyAnimInstance::NativeBeginPlay()
{
	// 게임 시작 시
}

void UMyAnimInstance::NativeUpdateAnimation(float _fDT)
{
	// 게임 시작 후 매프레임마다 호출됨
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());

	if (nullptr != pCharacter)
	{
		UCharacterMovementComponent* pMovementComponent = pCharacter->GetCharacterMovement();
		m_fSpeed = pMovementComponent->Velocity.Size(); //속도
		m_eState = pCharacter->GetState(); //상태
		m_bGround = pCharacter->GetMovementComponent()->IsMovingOnGround(); //땅에 있는지 여부

	}
}

#pragma region ----------------------------JumpAnimation-----------------------------------
void UMyAnimInstance::AnimNotify_JumpComboEnable() { //점프 콤보 가능
	m_JumpComboEnable = true;
	//UE_LOG(LogTemp, Log, TEXT("AnimNotify_JumpComboEnable"));
}

void UMyAnimInstance::AnimNotify_Jump1End() { //1,2단 점프 끝
	m_JumpEnd = true;
	//UE_LOG(LogTemp, Log, TEXT("AnimNotify_Jump 1 End"));
}


void UMyAnimInstance::AnimNotify_JumpEnd() { //점프 끝남을 알리는 함수
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	pCharacter->ChangeState(EPLAYER_STATE::IDLE);
	//UE_LOG(LogTemp, Log, TEXT("AnimNotify_JumpEnd"));
}
#pragma endregion

#pragma region ----------------------------AttackAnimation-----------------------------------
void UMyAnimInstance::AnimNotify_Attack01Combo() { //공격1 끝
	//끝남
	m_Attack01ComboEnable = true;
}

void UMyAnimInstance::AnimNotify_Attack02Combo() { //공격2 끝
	//끝남
	m_Attack02ComboEnable = true;
}


void UMyAnimInstance::AnimNotify_AttackEnd() { //공격123 끝
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	pCharacter->ChangeState(EPLAYER_STATE::IDLE);

	//콤보 초기화
	m_Attack01 = false;
	m_Attack02 = false;
	m_Attack01ComboEnable = false;
	m_Attack02ComboEnable = false;
	m_AttackEnd = true;
}

void UMyAnimInstance::AnimNotify_AttackMovableEnd() {
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	pCharacter->ChangeState(EPLAYER_STATE::MOVE);
}

void UMyAnimInstance::AnimNotify_RangeAttackTrigger()
{
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());

	if (nullptr != pCharacter)
	{
		pCharacter->RangeAttackTrigger();
	}
}

void UMyAnimInstance::AnimNotify_AttackTrigger()
{
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());

	if (nullptr != pCharacter)
	{
		pCharacter->AttackTrigger();
	}
}

void UMyAnimInstance::AnimNotify_AttackSound()
{
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());

	if (nullptr != pCharacter)
	{
		pCharacter->AttackSoundPlay();
	}
}


#pragma endregion

void UMyAnimInstance::AnimNotify_Idle()
{
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());

	if (pCharacter)
		pCharacter->ChangeState(EPLAYER_STATE::IDLE);
}
