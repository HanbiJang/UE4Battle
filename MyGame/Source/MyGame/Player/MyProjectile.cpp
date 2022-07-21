// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));

}

// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetBox()->OnComponentHit.AddDynamic(this, &AMyProjectile::OnHit);
	GetBox()->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectile::OnBeginOverlap);
}


// Called every frame
void AMyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyProjectile::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{

}

