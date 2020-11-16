// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Grid/MatrixIndexes.h"
#include "CombatUnit.generated.h"

UCLASS()
class MECHTURNBASED_API ACombatUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadWrite)
		FMatrixIndexes CurrentUnitGridPosition = FMatrixIndexes(0, 0, 0);
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MovingSpeedScale = 1.0;
};
