// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonster.h"

ANormalMonster::ANormalMonster() {


	fDamage = 20.f;
	
	//�޽� ��������
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		WarriorMesh(TEXT("SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Corpse_Sword.Corpse_Sword'"));

	if (WarriorMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(WarriorMesh.Object);
	}

	//�ִϸ��̼� ��������
	ConstructorHelpers::FClassFinder<UAnimInstance> animblueprint(TEXT("AnimBlueprint'/Game/Blueprints/Monster/AMyNormalMonsterAnimBlueprint.AMyNormalMonsterAnimBlueprint_C'"));
	if (animblueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(animblueprint.Class);
	}


	// ��� �� �ൿƮ��
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/Blueprints/Monster/MonsterAI/BTNormalMonster.BTNormalMonster'"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}

	// ��� �� ������	
	ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/Blueprints/Monster/MonsterAI/BBNormalMonster.BBNormalMonster'"));
	if (BB.Succeeded())
	{
		SetBlackboard(BB.Object);
	}


}


void ANormalMonster::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add("Monster");

	// ���̺��� NormalMonster ������ �����ͼ� �����Ѵ�.
	UMyGameInstance* pGameInst = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != pGameInst)
	{
		const FMonInfo* pTableRow = pGameInst->GetMonInfo(TEXT("NormalMonster"));
		if (nullptr != pTableRow)
		{
			SetMonInfo(*pTableRow);
		}
	}
}

void ANormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ü���� 0�̸� �׾������
	FMonInfo info = GetInfo();
	if (info.fCurHP <= 0.f) {
		ChangeState(EMON_STATE::DEAD);
	}

}

bool ANormalMonster::ChangeState(EMON_STATE _eNextState)
{
	if (EMON_STATE::HIT == _eNextState)
	{
		SetUnStopable(false); //false�� ���� Ǭ��
	}


	EMON_STATE eCurState = GetState();
	if (IsUnStopable() || eCurState == _eNextState) //true�� ���� �ش�
		return false;

	SetState(_eNextState);


	// ���� ���� ���� �� ��ó��
	switch (GetState())
	{
	case EMON_STATE::IDLE:
		GetMovementComponent()->StopMovementImmediately();
		break;
	case EMON_STATE::MOVE:
		break;
	case EMON_STATE::ATTACK:
		SetUnStopable(true);
		break;
	case EMON_STATE::ATTACK_MOVABLE:
		break;
	case EMON_STATE::JUMP:
		break;
	case EMON_STATE::HIT:
		SetUnStopable(true);
		break;
	case EMON_STATE::DEAD:
		SetUnStopable(true);
		break;
	default:
		break;
	}

	return true;
}

////����
//void ANormalMonster::Attack()
//{
//	//���� (�浹) ���� üũ
//	//Trace ä���� �̿��� ���� üũ	
//
//	// ���� ���� ��������
//	AMyMonster* pMonster = Cast<AMyMonster>(this);
//	if (nullptr == pMonster)
//		return;
//
//	FVector vPos = pMonster->GetActorLocation();
//	FVector vFoward = pMonster->GetActorForwardVector();
//	FTransform trans(pMonster->GetActorRotation(), vPos + vFoward * 50.f);
//	float fRadius = 150.f; //���� ũ��
//
//	TArray<FHitResult> arrHit; //�浹 ���
//	FCollisionQueryParams param(NAME_None, false, pMonster);
//
//	GetWorld()->SweepMultiByChannel(arrHit, vPos + FVector(0, 0, 50.f), vPos + FVector(0, 0, 50.f), FQuat::Identity
//		, ECC_GameTraceChannel6/*MonsterAttack Trace Channel*/
//		, FCollisionShape::MakeSphere(fRadius), param);
//
//	bool isCheckPlayer = false;
//	if (arrHit.Num())
//	{
//
//		for (size_t i = 0; i < arrHit.Num(); ++i) {
//			if (arrHit[i].GetActor()->Tags.Num() != 0) {
//				if ((arrHit[i].GetActor()->Tags)[0] == "Player") {
//					isCheckPlayer = true;
//					break;
//				}
//			}
//		}
//
//		if (isCheckPlayer) {
//			float damage = pMonster->GetDamage();
//
//			//�÷��̾ �°��ϱ�...
//			for (size_t i = 0; i < arrHit.Num(); ++i) {
//				AMyCharacter* m_Player = Cast<AMyCharacter>(arrHit[i].GetActor());
//				if (nullptr != m_Player) {
//					FDamageEvent DamageEvent;
//					m_Player->TakeDamage(damage, DamageEvent, NULL, pMonster);
//				}
//
//			}
//
//		}
//
//		for (size_t i = 0; i < arrHit.Num(); ++i)
//		{
//			UE_LOG(LogTemp, Log, TEXT("collision : %i"), arrHit.Num());
//			FString namemon = arrHit[i].GetActor()->GetName();
//			UE_LOG(LogTemp, Log, TEXT("%s"), *namemon);
//			//FTransform trans(arrHit[i].ImpactNormal.Rotation(), arrHit[i].ImpactPoint);
//		}
//	}
//
//
//#ifdef ENABLE_DRAW_DEBUG //������ ������ Ȯ��
//	FColor color;
//	arrHit.Num() ? color = FColor::Red : color = FColor::Green;
//	DrawDebugSphere(GetWorld(), vPos + FVector(0, 0, 50.f), fRadius, 12, color, false, 2.5f);
//#endif
//}


void ANormalMonster::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor
	, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(_HitComponent, _OtherActor, _OtherComp, _NormalImpulse, Hit);

	if (ECC_GameTraceChannel2 == _OtherComp->GetCollisionObjectType()) //�÷��̾� �ҿ����
	{
		ChangeState(EMON_STATE::HIT);
		//UE_LOG(LogTemp, Log, TEXT("OnHit"));
	}

	//UE_LOG(LogTemp, Log, TEXT("OnHit"));
}
void ANormalMonster::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	Super::OnBeginOverlap(_PrimitiveComponent, _OtherActor, _OtherComp, _OtherBodyIndex, _bFromSweep, _SweepResult);

	if (ECC_GameTraceChannel2 == _OtherComp->GetCollisionObjectType()) //�÷��̾� �ҿ����
	{
		ANormalMonster::HitFunc();

		//ChangeState(EMON_STATE::HIT);
		//GetMovementComponent()->StopMovementImmediately();
		//FMonInfo info = GetInfo();
		//info.fCurHP -= 35.f;
		//SetMonInfo(info);
		////UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

		//FString text =  "monster  HP: " + FString::SanitizeFloat(info.fCurHP);

		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, text);
	}
	//UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

}

//�¾��� �� 
void ANormalMonster::HitFunc() {
	ChangeState(EMON_STATE::HIT);
	GetMovementComponent()->StopMovementImmediately();
	FMonInfo info = GetInfo();
	info.fCurHP -= 20.f;
	SetMonInfo(info);
	//UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

	FString text = "monster  HP: " + FString::SanitizeFloat(info.fCurHP);

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, text);
}
