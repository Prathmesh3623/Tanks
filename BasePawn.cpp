// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
//#include "Classes/Components/SaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh")); 
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpwanPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn point"));
	ProjectileSpwanPoint->SetupAttachment(TurretMesh);

	

}

void ABasePawn:: RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation =FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this),15.f));


}
void ABasePawn::Fire(){
	FVector ProjectileSpawnPointLocation = ProjectileSpwanPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation=ProjectileSpwanPoint->GetComponentRotation();
	//DrawDebugSphere(GetWorld(),ProjectileSpawnPointLocation,35.f,12,FColor::Red,false,30.f);


	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPointLocation,ProjectileSpawnPointRotation);
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	if(DeathParticles){
	UGameplayStatics::SpawnEmitterAtLocation(this , DeathParticles,GetActorLocation(),GetActorRotation());
	}
	if(DeathSound){
	UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());
	}
	if(DeathCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
		}
}
