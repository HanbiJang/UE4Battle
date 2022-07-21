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
	//공격 주기
	float AttackTime;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* m_CapsuleSword;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AMyProjectile> m_Projectile;
public:
	//공격 관련
	virtual void Attack() override;
	virtual void RangeAttack() override;
	virtual void DownAttack() override;

	//데미지 입기
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//가드
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Charging();
	void Idle();


	// 어택 콜백
	virtual void AttackTrigger() override;
	virtual void RangeAttackTrigger() override;

	// 충돌 델리게이트
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor
		, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit) override;

	
	//사운드
	USoundBase*			hitSound;
	USoundBase*			rangeAttackSound;
	USoundBase*			SQ_Hit;
	virtual	void AttackSoundPlay() override;

};
