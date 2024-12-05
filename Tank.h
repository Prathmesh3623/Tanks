// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
ATank();
// Called to bind functionality to input
virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController ;}
	bool bAlive = true;



private:


UPROPERTY(VisibleAnywhere,Category = "Component")
class USpringArmComponent* SpringArm;

UPROPERTY(VisibleAnywhere,Category = "Component")
class UCameraComponent* Camera;

UPROPERTY(EditAnywhere , Category ="Movement" )
float Speed=250;
UPROPERTY(EditAnywhere , Category ="Movement" )
float TurnRate=200;

void Move(float value);
void Turn(float value);

APlayerController* TankPlayerController;


//FHitResult* HitResult; 
	
};
