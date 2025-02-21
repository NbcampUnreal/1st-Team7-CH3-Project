#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
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

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionComponent;

	// 블루프린트에서 설정할 아이템 클래스들
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<AActor> AmmoClass;

	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<AActor> GearClass;

	UFUNCTION()
	void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	void SpawnItem();
};
