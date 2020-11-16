// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileData.h"
#include "Components/BoxComponent.h"
#include "TileChecker.generated.h"

UCLASS()
class MECHTURNBASED_API ATileChecker : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileChecker();
	//ATileChecker();
	UFUNCTION(BlueprintCallable)
		FTileData Scan(FTileData TileData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TileStep = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* CollisionBox;

};
