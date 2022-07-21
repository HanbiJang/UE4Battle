// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineMinimal.h> //�߰���Ŵ
#include <Engine/DataTable.h> //�߰���Ŵ

#include "CoreMinimal.h"
#include "MyInfo.generated.h" //�߰���Ŵ

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
	: public FTableRowBase // ������ ���̺�� �����Ǵ� ����ü
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


// ������ �ֵ��� ���ٹ�
USTRUCT(Atomic, BlueprintType)
struct FMonInfo
	: public FTableRowBase // ������ ���̺�� �����Ǵ� ����ü
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