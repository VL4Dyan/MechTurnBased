// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridObjectType.h"
#include "GridObjectComponent.h"
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
	UFUNCTION()
		virtual void ApplyEnvironmentalDamage(FMatrixIndex IndexOfAffectedTile, int Dmg);
	UFUNCTION(BlueprintCallable)
		virtual TArray<UGridObjectComponent*> GetGridObjectComponents();
	UFUNCTION(BlueprintCallable)
		virtual bool TryGetGridObjectTileIndex(FMatrixIndex& OutTileIndex);
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
		EGridObjectType GridObjectType;

};
