// Fill out your copyright notice in the Description page of Project Settings.


#include "TileChecker.h"

// Sets default values
ATileChecker::ATileChecker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

FTileData ATileChecker::Scan(FTileData TileData)
{
	TArray<AActor*> OverlappingResult;
	CollisionBox->GetOverlappingActors(OverlappingResult);

	for (int i = 0; i < OverlappingResult.Num(); i++)
	{
		if (OverlappingResult[i]->IsA<ASpawnPoint>())
		{
			TileData.SpawnPoint = Cast<ASpawnPoint>(OverlappingResult[i]);
		}
		else
		{
			TileData.bIsVoid = false;
		}
	}

	return TileData;
}

// Called when the game starts or when spawned
void ATileChecker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileChecker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

