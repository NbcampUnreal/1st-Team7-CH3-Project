#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CP_Item.h"
#include "CP_Ammo.h"
#include "CP_Gear.h"
#include "CP_Heal.h"
#include "CP_ItemSpawn.generated.h"

UCLASS()
class CYBERPUNK_API ACP_ItemSpawn : public AActor
{
	GENERATED_BODY()

public:
	ACP_ItemSpawn();

protected:
	virtual void BeginPlay() override;

private:
	AActor* SpawnedItem;
	FVector InitialSpawnLocation;
	float TimeElapsed;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionComponent;

	TSubclassOf<AActor> AmmoClass;
	TSubclassOf<AActor> GearClass;
	TSubclassOf<AActor> HealClass;

	UFUNCTION()
	void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	void SpawnItem();
};
