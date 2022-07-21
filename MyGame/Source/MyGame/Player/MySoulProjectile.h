// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectile.h"
#include "MySoulProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMySoulProjectile : public AMyProjectile
{
	GENERATED_BODY()

private:
	float				m_fAccTime;

	USoundBase* m_Sound;
	USoundAttenuation* m_Attenuation;
	
public:
	AMySoulProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit);

	// Collision Event
public:

	void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult) override;
	void OnEndOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex) override;

};
