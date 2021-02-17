// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridObjectType.h"
#include "GridObject.generated.h"

UCLASS(Abstract, Blueprintable)
class MECHTURNBASED_API AGridObject : public ACharacter
{
	GENERATED_BODY()

public:
	AGridObject();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		EGridObjectType GetGridObjectType();
	UFUNCTION()
		virtual bool TryToFall();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
		EGridObjectType GridObjectType;

};
