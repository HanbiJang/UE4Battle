// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include "../Global/MyGameInstance.h"

#include "CoreMinimal.h"
#include "MyMonster.h"
#include "NormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API ANormalMonster : public AMyMonster
{
	GENERATED_BODY()

	
public:
	ANormalMonster();
	//~ANormalMonster();


	virtual bool ChangeState(EMON_STATE _eNextState) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit) override;
	void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult) override;

	virtual void HitFunc() override;

};
