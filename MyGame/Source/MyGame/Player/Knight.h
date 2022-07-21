// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "MyProjectile.h"
#include "MySoulProjectile.h"
#include <DrawDebugHelpers.h>

#include "Knight.generated.h"


/**
 * 
 */
UCLASS()
class MYGAME_API AKnight : public AMyCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

public:
	AKnight();

public:
	//���� �ֱ�
	float AttackTime;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* m_CapsuleSword;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AMyProjectile> m_Projectile;
public:
	//���� ����
	virtual void Attack() override;
	virtual void RangeAttack() override;
	virtual void DownAttack() override;

	//������ �Ա�
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//����
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Charging();
	void Idle();


	// ���� �ݹ�
	virtual void AttackTrigger() override;
	virtual void RangeAttackTrigger() override;

	// �浹 ��������Ʈ
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor
		, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit) override;

	
	//����
	USoundBase*			hitSound;
	USoundBase*			rangeAttackSound;
	USoundBase*			SQ_Hit;
	virtual	void AttackSoundPlay() override;

};
