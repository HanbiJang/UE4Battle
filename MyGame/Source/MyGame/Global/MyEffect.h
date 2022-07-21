// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include "MyEffectEnum.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEffect.generated.h"

UCLASS()
class MYGAME_API AMyEffect : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		EEFFECT			  m_eType;

public:	
	// Sets default values for this actor's properties
	AMyEffect();

public:
	void SetEffectType(EEFFECT _eType) { m_eType = _eType; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void OnFinish(UParticleSystemComponent* _Particle);

};
