// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMonsterAnimInstance.h"

UMyMonsterAnimInstance::UMyMonsterAnimInstance() {

}

void UMyMonsterAnimInstance::NativeInitializeAnimation()
{
	// ��ü ���� ��
}
void UMyMonsterAnimInstance::NativeBeginPlay()
{
	// ���� ���� ��
}

void UMyMonsterAnimInstance::NativeUpdateAnimation(float _fDT)
{
	// ���� ���� �� �������Ӹ��� ȣ���
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (nullptr != pMonster)
	{
		UCharacterMovementComponent* pMovementComponent = pMonster->GetCharacterMovement();
		m_fSpeed = pMovementComponent->Velocity.Size(); //�ӵ�
		m_eState = pMonster->GetState(); //����
		m_bGround = pMonster->GetMovementComponent()->IsMovingOnGround(); //���� �ִ��� ����

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
		// ���� ���ۿ� ���� ������ Ǯ�� ��
		pMonster->SetUnStopable(false);
	}
}

void UMyMonsterAnimInstance::AnimNotify_HitEnd() {
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (nullptr != pMonster)
	{
		// ��Ʈ ��ǿ� ���� ������ Ǯ�� ��
		pMonster->SetUnStopable(false);
	}
}

void UMyMonsterAnimInstance::AnimNotify_DeadEnd() {
	//�ױ�
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());
	pMonster->Destroy();
}

void UMyMonsterAnimInstance::AnimNotify_Idle()
{
	AMyMonster* pMonster = Cast<AMyMonster>(TryGetPawnOwner());

	if (pMonster)
		pMonster->ChangeState(EMON_STATE::IDLE);
}