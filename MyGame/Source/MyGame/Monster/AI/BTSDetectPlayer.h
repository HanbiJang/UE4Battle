// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAIController.h"
#include "../../Player/MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <DrawDebugHelpers.h>

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTSDetectPlayer.generated.h"

UCLASS()
/// <summary>
/// 서비스 : 매시간 플레이어를 탐지함
/// </summary>
class MYGAME_API UBTSDetectPlayer : public UBTService
{
	GENERATED_BODY()

public:
	UBTSDetectPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
