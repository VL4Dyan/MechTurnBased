// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Teams.h"
#include "MatrixIndex.h"
#include "SpawnPoint.generated.h"

UCLASS()
class MECHTURNBASED_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETeams Team = ETeams::Team_Player;
	UPROPERTY(BlueprintReadWrite)
		FMatrixIndex TileIndex = FMatrixIndex(0, 0, 0);
};
