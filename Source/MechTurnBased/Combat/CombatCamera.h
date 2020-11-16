// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime\Engine\Classes\Camera\CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CombatCamera.generated.h"


UCLASS(Blueprintable)
class MECHTURNBASED_API ACombatCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACombatCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		FTransform CalculateZoomTransform(FTransform Transform, float ZoomingScale);
	UFUNCTION(BlueprintCallable)
		void SetDefaultPosition(UCameraComponent* Camera);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CameraMovingSpeed = 10.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CameraRotationSpeed = 5.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxZoomDistance = 100.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MinZoomDistance = 10.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ZoomStep = 10.0;

};
