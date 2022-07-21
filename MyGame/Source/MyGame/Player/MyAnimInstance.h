// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include "../Global/MyCharacterStates.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

class AMyCharacter;

UCLASS()
class MYGAME_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float _fDT) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EPLAYER_STATE m_eState; //캐릭터 상태



#pragma region ----------------------------MoveAnimation-----------------------------------
	//움직임 관련 변수
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float	m_fSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float	m_fDirection;

	//움직임 관련 함수
public:
	void SetDirection(float _fDir) { m_fDirection = _fDir; }
	float GetDirection() { return m_fDirection; }
#pragma endregion

#pragma region ----------------------------JumpAnimation-----------------------------------
	//점프 관련 변수
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_Jump2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_JumpComboEnable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_JumpEnd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool	m_bGround;

	//점프 관련 함수
public:
	
	UFUNCTION()
		void AnimNotify_JumpComboEnable(); //점프 콤보 가능

	UFUNCTION()
		void AnimNotify_Jump1End(); //점프 끝남을 알림

	UFUNCTION()
		void AnimNotify_JumpEnd(); //1단 점프 끝남을 알림

	//점프
	void Setm_Jump2(bool value) { m_Jump2 = value; }
	bool Getm_Jump2() { return m_Jump2; }

	void Setm_JumpComboEnable(bool value) { m_JumpComboEnable = value; }
	bool Getm_JumpComboEnable() { return m_JumpComboEnable; }

	void Setm_JumpEnd(bool value) { m_JumpEnd = value; }
	bool Getm_JumpEnd() { return m_JumpEnd; }
#pragma endregion

#pragma region ----------------------------Attack-----------------------------------
	//공격관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_Attack01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_Attack02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_Attack01ComboEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_Attack02ComboEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_AttackEnd;

	//공격 관련 함수
public:
	UFUNCTION()
		void AnimNotify_Attack01Combo();
	UFUNCTION()
		void AnimNotify_Attack02Combo();
	UFUNCTION()
		void AnimNotify_AttackEnd();
	UFUNCTION()
		void AnimNotify_AttackMovableEnd();
	UFUNCTION()
		void AnimNotify_RangeAttackTrigger();
	UFUNCTION()
		void AnimNotify_AttackTrigger();
	UFUNCTION()
		void AnimNotify_AttackSound();		
public:
	void Setm_Attack01(bool value) { m_Attack01 = value; }
	bool Getm_Attack01() { return m_Attack01; }
	void Setm_Attack02(bool value) { m_Attack02 = value; }
	bool Getm_Attack02() { return m_Attack02; }
	void Setm_AttackEnd(bool value) { m_AttackEnd = value; }
	bool Getm_AttackEnd() { return m_AttackEnd; }

	void Setm_Attack01ComboEnable(bool value) { m_Attack01ComboEnable = value; }
	bool Getm_Attack01ComboEnable() { return m_Attack01ComboEnable; }
	void Setm_Attack02ComboEnable(bool value) { m_Attack02ComboEnable = value; }
	bool Getm_Attack02ComboEnable() { return m_Attack02ComboEnable; }

#pragma endregion

};
