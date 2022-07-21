// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardData.h>

#include "../Global/MyCharacterStates.h"
#include "../Global/MyInfo.h"
#include "../Player/MyCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyMonster.generated.h"

UCLASS()
class MYGAME_API AMyMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyMonster();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBehaviorTree* m_BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBlackboardData* m_Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		FMonInfo		m_Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
		EMON_STATE		m_eState;

	TArray<FVector>	m_PatrolPoints;

	bool			bIsUnStopable;

public:
	UBehaviorTree* GetBehaviorTree() { return m_BehaviorTree; }
	UBlackboardData* GetBlackboard() { return m_Blackboard; }

	//순찰하기
	FVector	GetNextPatrolPos();
	int8			m_NextPatrolIdx;
	void AddPatrolPoint(FVector _vPosition) { m_PatrolPoints.Add(_vPosition); }

protected:
	void SetMonInfo(const FMonInfo& _info) { m_Info = _info; }
	void SetBehaviorTree(UBehaviorTree* _Tree) { m_BehaviorTree = _Tree; }
	void SetBlackboard(UBlackboardData* _board) { m_Blackboard = _board; }
	void SetState(EMON_STATE _eState) { m_eState = _eState; }




public:
	EMON_STATE GetState() { return m_eState; }
	const FMonInfo& GetInfo() { return m_Info; }

	void SetDamage(float _fDamage) { m_Info.fCurHP -= _fDamage; }
	bool IsUnStopable() { return bIsUnStopable; }
	void SetUnStopable(bool _bState) { bIsUnStopable = _bState; }

public:
	virtual bool ChangeState(EMON_STATE _eNextState) { return true; }

//------------------------------

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EMON_STATE m_state;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION() // 충돌 알림 함수
	virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);


public:
	virtual void OnAttakTrigger();

	float fDamage = 10.f;
	float GetDamage() { return fDamage;  }

	//맞는 반응
public:
	virtual void HitFunc(){};
};
