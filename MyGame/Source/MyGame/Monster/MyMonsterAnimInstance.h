// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include "MyMonster.h"
#include "../Global/MyCharacterStates.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMyMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()



private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EMON_STATE m_eState; //캐릭터 상태

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float	m_fSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float	m_fDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool	m_bGround;
	
public:
	UMyMonsterAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float _fDT) override;

	UFUNCTION()
		void AnimNotify_HitEnd(); //맞음 끝

	UFUNCTION()
	void AnimNotify_NormalMon_AttEnd(); //공격 끝

	UFUNCTION()
		void AnimNotify_DeadEnd(); //죽음 끝
};
