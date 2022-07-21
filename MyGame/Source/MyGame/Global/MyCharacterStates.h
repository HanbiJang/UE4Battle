// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class MYGAME_API MyCharacterStates
{

};


UENUM(BlueprintType)
enum class EPLAYER_STATE : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	ATTACK_MOVABLE,
	RANGEATTACK,
	DOWNATTACK,
	CHARGE,
	DASH,
	JUMP,
	HIT,
	DEAD,
};

UENUM(BlueprintType)
enum class EMON_STATE : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	ATTACK_MOVABLE,
	RANGEATTACK,
	DOWNATTACK,
	CHARGE,
	DASH,
	JUMP,
	HIT,
	DEAD,
};

