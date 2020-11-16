#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Units/CombatUnit.h"
#include "TileData.generated.h"

USTRUCT(BlueprintType)
struct MECHTURNBASED_API FTileData
{
	GENERATED_BODY()

public:
	FTileData(float XAbsPosition, float YAbsPosition, float ZAbsPosition);

	FTileData();

	UPROPERTY(BlueprintReadWrite)
		bool bIsVoid = true;
	UPROPERTY(BlueprintReadOnly)
		FVector AbsoluteCoordinates;
	UPROPERTY(BlueprintReadWrite)
		class ACombatUnit* TileHolder = NULL;
};