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
	// ��ü ���� ��
}
void UMyAnimInstance::NativeBeginPlay()
{
	// ���� ���� ��
}

void UMyAnimInstance::NativeUpdateAnimation(float _fDT)
{
	// ���� ���� �� �������Ӹ��� ȣ���
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());

	if (nullptr != pCharacter)
	{
		UCharacterMovementComponent* pMovementComponent = pCharacter->GetCharacterMovement();
		m_fSpeed = pMovementComponent->Velocity.Size(); //�ӵ�
		m_eState = pCharacter->GetState(); //����
		m_bGround = pCharacter->GetMovementComponent()->IsMovingOnGround(); //���� �ִ��� ����

	}
}

#pragma region ----------------------------JumpAnimation-----------------------------------
void UMyAnimInstance::AnimNotify_JumpComboEnable() { //���� �޺� ����
	m_JumpComboEnable = true;
	//UE_LOG(LogTemp, Log, TEXT("AnimNotify_JumpComboEnable"));
}

void UMyAnimInstance::AnimNotify_Jump1End() { //1,2�� ���� ��
	m_JumpEnd = true;
	//UE_LOG(LogTemp, Log, TEXT("AnimNotify_Jump 1 End"));
}


void UMyAnimInstance::AnimNotify_JumpEnd() { //���� ������ �˸��� �Լ�
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	pCharacter->ChangeState(EPLAYER_STATE::IDLE);
	//UE_LOG(LogTemp, Log, TEXT("AnimNotify_JumpEnd"));
}
#pragma endregion

#pragma region ----------------------------AttackAnimation-----------------------------------
void UMyAnimInstance::AnimNotify_Attack01Combo() { //����1 ��
	//����
	m_Attack01ComboEnable = true;
}

void UMyAnimInstance::AnimNotify_Attack02Combo() { //����2 ��
	//����
	m_Attack02ComboEnable = true;
}


void UMyAnimInstance::AnimNotify_AttackEnd() { //����123 ��
	AMyCharacter* pCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	pCharacter->ChangeState(EPLAYER_STATE::IDLE);

	//�޺� �ʱ�ȭ
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
