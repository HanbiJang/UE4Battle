// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h>
#include "BehaviorTree/BlackboardComponent.h"

#include "MyAIController.h"
#include "../../Player/MyCharacter.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDIsInRange.generated.h"


UENUM(BlueprintType)
enum class ERANGE_TYPE : uint8
{
	DETECTION,
	ATTACK,
};



/**
 * 
 */
UCLASS()
class MYGAME_API UBTDIsInRange : public UBTDecorator
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ERANGE_TYPE m_Type;

public:
	UBTDIsInRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};

