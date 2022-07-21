// Fill out your copyright notice in the Description page of Project Settings.

#include "Knight.h"
#include "../Monster/MyMonster.h"
#include "../Global/MyEffectEnum.h"
#include "../Global/MyEffectManager.h"
#include "../Global/MyGameInstance.h"

#define RangeAttackMp 35.f

AKnight::AKnight() {
	//�Ž� ����
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		WarriorMesh(TEXT("SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Meshes/Kallari.Kallari'"));

	if (WarriorMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(WarriorMesh.Object);
	}

	//�ִϸ��̼�
	ConstructorHelpers::FClassFinder<UAnimInstance> animblueprint(TEXT("AnimBlueprint'/Game/Blueprints/Player/MyKnightAnimBlueprint.MyKnightAnimBlueprint_C'"));
	if (animblueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(animblueprint.Class);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> Down(TEXT("AnimMontage'/Game/Blueprints/Player/MMyKnightDownAttack.MMyKnightDownAttack'"));
	if (Down.Succeeded())
		m_arrMontage.Add(Down.Object);

	//Į
	m_CapsuleSword = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleSword"));
	m_CapsuleSword->SetupAttachment(GetMesh()); //�޽ÿ� sword������Ʈ ���̱�
	//�θ� ���� ����
	//m_CapsuleSword->AttachTo(GetMesh(), TEXT("Mesh"), EAttachLocation::SnapToTargetIncludingScale, true);

	//������
	m_Demage = 10.f;

	//���� ����
	// ����� ���� ����
	ConstructorHelpers::FObjectFinder<USoundBase> soundasset1(TEXT("SoundWave'/Game/MyBGM/hit_sound.hit_sound'"));
	if (soundasset1.Succeeded())
	{
		hitSound = soundasset1.Object;
	}

	//������ ���� ����
	//
	ConstructorHelpers::FObjectFinder<USoundBase> soundasset2(TEXT("SoundWave'/Game/MyBGM/RangeAttack.RangeAttack'"));
	if (soundasset2.Succeeded())
	{
		rangeAttackSound = soundasset2.Object;
	}
};


//Ű ���ε�
void AKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//ȸ��
	PlayerInputComponent->BindAction("Charge", EInputEvent::IE_Pressed, this, &AKnight::Charging);
}

void AKnight::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//���� �ֱ� �����ϱ�
	if (m_AnimInst->Getm_AttackEnd()) { //jumpend ������ true�϶��� 1�� �ڿ� ��ȯ��
		if (0.5f <= AttackTime)
		{
			m_AnimInst->Setm_AttackEnd(false);
			AttackTime = 0.f; //�ʱ�ȭ
			//UE_LOG(LogTemp, Log, TEXT("Tick _ jumpTime = 0"));
		}
		else {
			AttackTime += DeltaTime;
			//UE_LOG(LogTemp, Log, TEXT("Tick _ jumpTime = %f"), jumpTime);
		}
	}

}

void AKnight::BeginPlay() {
	Super::BeginPlay();

	//ĳ������ �Žÿ��� ������ AnimInstance Ŭ���� ��������
	m_AnimInst = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); 
}

void AKnight::Attack() {
	if (!m_AnimInst->Getm_AttackEnd()) {
		if (myState == EPLAYER_STATE::MOVE || myState == EPLAYER_STATE::JUMP) { //������ ���� ����
			AMyCharacter::ChangeState(EPLAYER_STATE::ATTACK_MOVABLE);
			// �Ҹ� ���, 2D
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, GetActorLocation(), 1.f, 1.f, 0.f);
		}

		//�Ϲݰ���
		else if (myState == EPLAYER_STATE::IDLE || myState == EPLAYER_STATE::ATTACK) 
		{

			if (m_AnimInst->Getm_Attack02()) { //3�ܰ� ���� �������Ͻ�
				return;
			}

			if( myState != EPLAYER_STATE::ATTACK){
				AMyCharacter::ChangeState(EPLAYER_STATE::ATTACK); //�������� ���� ��ȭ
			}
			

			if (m_AnimInst->Getm_Attack01ComboEnable()) {
				m_AnimInst->Setm_Attack01(true);
			}

			if (m_AnimInst->Getm_Attack02ComboEnable()) {
				m_AnimInst->Setm_Attack02(true);
			}

		}
	}
}

void AKnight::AttackSoundPlay() {

	// �Ҹ� ���, 2D
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, GetActorLocation(), 1.f, 1.f, 0.f);
	
}


void AKnight::RangeAttack() { 

	if( myState != EPLAYER_STATE::RANGEATTACK && GetInfo().fCurMP >= RangeAttackMp){
	//����Ʈ �����
	FVector vPos = GetActorLocation();
	FVector vFoward = GetActorForwardVector();
	FTransform trans(GetActorRotation(), vPos+ vFoward *50.f);

	UMyEffectManager::GetInst(GetWorld())->CreateEffect(EEFFECT::RANGEATTACK, trans, GetLevel());

	// �Ҹ� ���, 2D
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), rangeAttackSound, GetActorLocation(), 1.f, 1.f, 0.f);

	ChangeState(EPLAYER_STATE::RANGEATTACK);
	}
}

void AKnight::DownAttack() { //�ٿ� ����
	Super::DownAttack();

	GetAnimInst()->Montage_Play(m_arrMontage[0]);
}

void AKnight::Charging() { //ü�� ȸ��

	ChangeState(EPLAYER_STATE::CHARGE);

	//ü��ȸ�� �ڵ�
	//...
}


void AKnight::AttackTrigger() 
{
	if (!m_AnimInst->Getm_AttackEnd()) {
		//camera shake
		UMyGameInstance* pGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (nullptr != pGI)
		{
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(pGI->GetCameraShake());
		}

		//�ֵθ��� ����Ʈ ���
		FVector vPos = GetActorLocation();
		FVector vFoward = GetActorForwardVector();
		FTransform trans(GetActorRotation(), vPos + vFoward * 50.f);
		UMyEffectManager::GetInst(GetWorld())->CreateEffect(EEFFECT::ATTACK1, trans, GetLevel());

		//���� (�浹) ���� üũ
		//Trace ä���� �̿��� ���� üũ		
		float fRadius = 200.f; //���� ũ��

		TArray<FHitResult> arrHit; //�浹 ���
		FCollisionQueryParams param(NAME_None, false, this);

		GetWorld()->SweepMultiByChannel(arrHit, vPos + FVector(0, 0, 50.f), vPos + FVector(0, 0, 50.f), FQuat::Identity
			, ECC_GameTraceChannel3/*PlayerAttack Trace Channel*/
			, FCollisionShape::MakeSphere(fRadius), param);

		bool isCheckMonster = false;
		if (arrHit.Num())
		{

			for (size_t i = 0; i < arrHit.Num(); ++i) {
				if (arrHit[i].GetActor()->Tags.Num() != 0) {
					if ((arrHit[i].GetActor()->Tags)[0] == "Monster") {
						isCheckMonster = true;
						break;
					}
				}
			}

			if (isCheckMonster) {
				//����Ʈ ���
				UMyEffectManager::GetInst(GetWorld())->CreateEffect(EEFFECT::ATTACK2, trans, GetLevel());

				//���Ͱ� �°��ϱ�...
				for (size_t i = 0; i < arrHit.Num(); ++i) {
					AMyMonster* m_mon = Cast<AMyMonster>(arrHit[i].GetActor());
					if (nullptr != m_mon)
						m_mon->HitFunc();
						
						//MP ȸ���ϱ�

						GetInfo().fCurMP += 10.f;

						if(GetInfo().fMaxMP <= GetInfo().fCurMP){
							GetInfo().fCurMP = GetInfo().fMaxMP;
						}
				}
			}

			for (size_t i = 0; i < arrHit.Num(); ++i)
			{
				UE_LOG(LogTemp, Log, TEXT("collision : %i"), arrHit.Num());
				FString namemon = arrHit[i].GetActor()->GetName();
				UE_LOG(LogTemp, Log, TEXT("%s"), *namemon);
				//FTransform trans(arrHit[i].ImpactNormal.Rotation(), arrHit[i].ImpactPoint);
			}
		}
	

#ifdef ENABLE_DRAW_DEBUG //������ ������ Ȯ��
	FColor color;
	arrHit.Num() ? color = FColor::Red : color = FColor::Green;
	DrawDebugSphere(GetWorld(), vPos + FVector(0, 0, 50.f), fRadius, 12, color, false, 2.5f);
#endif
	}
}

void AKnight::RangeAttackTrigger() //���������ݿ� ��Ƽ���̷� ���
{

	if(GetInfo().fCurMP >= RangeAttackMp){

		// ����ü ����
		FVector vPos = GetActorLocation();
		FVector vFoward = GetActorForwardVector();

		FActorSpawnParameters SpawnParam = {};

		SpawnParam.OverrideLevel = GetLevel();
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParam.bDeferConstruction = true;

		AMySoulProjectile* pSoul = GetWorld()->SpawnActor<AMySoulProjectile>(m_Projectile
			, vPos + vFoward * 100.f
			, vFoward.Rotation()
			, SpawnParam);

		if (pSoul != nullptr) {
			pSoul->GetProjectile()->Velocity = vFoward;
			// begin play ȣ��
			pSoul->FinishSpawning(pSoul->GetTransform());
		}

		else UE_LOG(LogTemp, Log, TEXT("?"));	

		//mp����
		GetInfo().fCurMP -= RangeAttackMp;
	}

}

void AKnight::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{

}
