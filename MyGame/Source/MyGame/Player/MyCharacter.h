// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include "../Global/MyCharacterStates.h"
#include "../Global/MyInfo.h"
#include "../UI/PlayerHUD.h"
#include <components/widgetcomponent.h>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


class UMyAnimInstance; //�ߺ� ��� ���� ���� �ذ�

UCLASS()
class MYGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* m_Cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* m_Arm;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EPLAYER_STATE			myState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		FPlayerInfo				m_Info;

	FPlayerInfo& GetInfo() { return m_Info; }


	float					m_PrevHP;
	float					m_PrevMP;
	float					m_Demage;

	float GetM_Demage() { return m_Demage; };

protected:
	UMyAnimInstance* m_AnimInst; //Ŭ���� ��ü �޾ƿ� ��

	UMyAnimInstance* GetAnimInst() { return m_AnimInst; }

private:
	float jumpTime; // ���� �ð� ����

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	TArray<UAnimMontage*>	m_arrMontage; //��Ÿ�� �ִϸ��̼�

public: //�̵� ����
	void MoveFront(float fscale);
	void MoveSide(float fscale);
	virtual void JumpAction();

	//���� ����
	virtual void Attack() {};
	virtual void RangeAttack();
	virtual void DownAttack();
	virtual void RangeAttackTrigger() {};
	virtual void AttackTrigger() {};

	//ī�޶�
	void Zoom(float fscale);
	void RotationY(float fscale);
	void RotationZ(float fscale);


public://���� ����
	EPLAYER_STATE GetState(); //���� �� ��������
	void SetState(EPLAYER_STATE newState);
	void ChangeState(EPLAYER_STATE newState); //���� ��ȭ
	void ResetAnimState();


	
	// Collision Event
public:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex);

	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit);


	//����
	virtual	void AttackSoundPlay(){};

	//UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_PlayerHUD;
};