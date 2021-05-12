// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UActionResult;
class AGridObject;

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
		virtual void UpdateComponentState(FGridObjectComponentState ComponentStateReplacement);
	UFUNCTION(BlueprintCallable)
		virtual FMatrixIndex GetTileToHighlight(); //temp function
	UFUNCTION(BlueprintCallable)
		FGridObjectComponentState GetComponentState();
	UFUNCTION()
		UBoxComponent* GetCollisionRef();
	UFUNCTION(BlueprintCallable)
		void SetCollisionRef(UBoxComponent* CollisionBoxRefToSet);
	UFUNCTION(BlueprintCallable)
		EGridObjectCompType GetComponentType();
	UFUNCTION(BlueprintCallable)
		void SetGridObjectComponentOwner(AGridObject* GridObjectComponentOwnerToSet);
	UFUNCTION()
		AGridObject* GetGridObjectComponentOwner();

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
	UPROPERTY(BlueprintReadOnly)
		AGridObject* GridObjectComponentOwner;

};
