// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <EngineMinimal.h>
#include "GameFramework/ProjectileMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

UCLASS()
class MYGAME_API AMyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProjectile();
	bool m_IsHit;
	FVector newScale;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

///

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* m_ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* m_Box; //충돌 박스

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* m_Particle;


public:
	UProjectileMovementComponent* GetProjectile() { return m_ProjectileMovement; }
	UBoxComponent* GetBox() { return m_Box; }
	UParticleSystemComponent* GetParticle() { return m_Particle; }

protected:
	void SetProjectile(UProjectileMovementComponent* _com) { m_ProjectileMovement = _com; }
	void SetBox(UBoxComponent* _com) { m_Box = _com; }
	void SetParticle(UParticleSystemComponent* _com) { m_Particle = _com; }


// collision delegate
public:
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* _HitComponent,
			AActor* _OtherActor,
			UPrimitiveComponent* _OtherComp,
			FVector _NormalImpulse,
			const FHitResult& Hit);

	// Collision Event
public:
	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult) {};

	UFUNCTION()
		virtual void OnEndOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex) {};

};
