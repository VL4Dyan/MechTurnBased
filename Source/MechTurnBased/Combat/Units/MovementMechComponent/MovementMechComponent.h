// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MechComponent.h"
#include "CoreMinimal.h"
#include "MovementMechComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract, Blueprintable)
class MECHTURNBASED_API UMovementMechComponent : public UMechComponent
{
	GENERATED_BODY()

public:
	UMovementMechComponent();


};
