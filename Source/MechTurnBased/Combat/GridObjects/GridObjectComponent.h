// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UActionResult;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "../Grid/MatrixIndex.h"
#include "GridObjectComponentState.h"
#include "GridObjectComponent.generated.h"

UENUM(BlueprintType)
enum class EGridObjectCompType : uint8
{
	CompType_Movement UMETA(DisplayName = "MovementComponent"),
	CompType_Attack UMETA(DisplayName = "AttackingComponent"),
	CompType_Other UMETA(DisplayName = "Other")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract)
class MECHTURNBASED_API UGridObjectComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UGridObjectComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		virtual FGridObjectComponentState GetComponentState();
	UFUNCTION(BlueprintCallable)
		virtual void UpdateComponentState(FGridObjectComponentState ComponentStateReplacement);
	UFUNCTION()
		virtual UBoxComponent* GetCollisionRef();
	UFUNCTION(BlueprintCallable)
		virtual void SetCollisionRef(UBoxComponent* CollisionBoxRefToSet);
	UFUNCTION(BlueprintCallable)
		virtual FMatrixIndex GetTileToHighlight(); //temp function
	UFUNCTION(BlueprintCallable)
		EGridObjectCompType GetComponentType();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		UBoxComponent* CollisionBoxRef;
	UPROPERTY()
		FGridObjectComponentState ComponentState;

protected:
	UPROPERTY(BlueprintReadWrite)
		EGridObjectCompType ComponentType = EGridObjectCompType::CompType_Other;

};
