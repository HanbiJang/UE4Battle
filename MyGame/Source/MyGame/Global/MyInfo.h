// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h> //추가시킴
#include <Engine/DataTable.h> //추가시킴

#include "CoreMinimal.h"
#include "MyInfo.generated.h" //추가시킴

/**
 * 
 */
class MYGAME_API MyInfo
{
public:
	MyInfo();
	~MyInfo();
};

USTRUCT(Atomic, BlueprintType)
struct FPlayerInfo
	: public FTableRowBase // 데이터 테이블과 연동되는 구조체
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		FString strClassName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		float fMaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		float fCurHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		float fMaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
		float fCurMP;
};


// 데이터 주도형 접근법
USTRUCT(Atomic, BlueprintType)
struct FMonInfo
	: public FTableRowBase // 데이터 테이블과 연동되는 구조체
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float fMaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float fCurHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float fAtt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float fDetectRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float fAttackRange;
};