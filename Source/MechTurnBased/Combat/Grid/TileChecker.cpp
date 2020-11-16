// Fill out your copyright notice in the Description page of Project Settings.


#include "TileChecker.h"

// Sets default values
ATileChecker::ATileChecker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//CollisionBox->SetBoxExtent(FVector(50, 50, 50), false);
}

FTileData ATileChecker::Scan(FTileData TileData)
{
	TArray<AActor*> OverlappingResult;
	CollisionBox->GetOverlappingActors(OverlappingResult);

	//logging start here

	//logging ends here

	if (OverlappingResult.Num() > 0)
	{
		TileData.bIsVoid = false;
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

