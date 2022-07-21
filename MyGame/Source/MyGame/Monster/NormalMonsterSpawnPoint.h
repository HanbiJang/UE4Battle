// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include <DrawDebugHelpers.h>
#include "MyMonster.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NormalMonsterSpawnPoint.generated.h"

UCLASS()
class MYGAME_API ANormalMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<AActor*>			m_PatrolPoints; //순찰 포인트 리스트

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* m_StaticMeshComponent; //매시

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AMyMonster>	m_SpawnType; //스폰 타입

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		uint8					m_SpawnNum; //스폰 지점 수

	float					m_AccTime;
	bool					bIsSpawnUse;


public:
	// Sets default values for this actor's properties
	ANormalMonsterSpawnPoint();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

};
