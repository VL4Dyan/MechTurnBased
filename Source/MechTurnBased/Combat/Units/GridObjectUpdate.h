// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AGridObject;

#include "CoreMinimal.h"
#include "GridObjectUpdate.generated.h"

UENUM(BlueprintType)
enum class EGridObjectUpdateType : uint8
{
	GOUT_Attack = 0 UMETA(DisplayName = "Attack"),
	GOUT_Movement = 1 UMETA(DisplayName = "Movement"),
	GOUT_Shift = 2 UMETA(DisplayName = "Shift"),
	GOUT_Fall = 3 UMETA(DisplayName = "Fall"),
	GOUT_DamageReception = 4 UMETA(DisplayName = "DamageReception"),
	GOUT_Death = 5 UMETA(DisplayName = "Death")
};

USTRUCT(BlueprintType)
struct MECHTURNBASED_API FGridObjectUpdate
{
	GENERATED_BODY()

public:
	FGridObjectUpdate();
	FGridObjectUpdate(EGridObjectUpdateType GridObjectUpdateType, TArray<FVector> WorldLocationTargets, TArray<AGridObject*> AffectedGridObjects);

public:
	UPROPERTY(BlueprintReadOnly)
		EGridObjectUpdateType VisualUpdateType;
	UPROPERTY(BlueprintReadOnly)
		TArray<FVector> WorldLocationTargets;
	UPROPERTY(BlueprintReadOnly)
		TArray<AGridObject*> AffectedGridObjects;
};
