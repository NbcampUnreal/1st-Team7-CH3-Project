#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Guns.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "Components/SphereComponent.h"
#include "CP_GunSpawn.generated.h"

UCLASS()
class CYBERPUNK_API ACP_GunSpawn : public AActor
{
    GENERATED_BODY()

public:
    ACP_GunSpawn();

protected:
    virtual void BeginPlay() override;
    FVector InitialLocation;

private:
    UPROPERTY()
    AActor* SpawnedPart;

public:
    virtual void Tick(float DeltaTime) override;

    // 루트 씬 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    // 충돌 감지 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* CollisionComponent;

    // 스폰할 총기 파츠의 클래스 (Barrel, Body, Trigger)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    TSubclassOf<ACP_BarrelInfo> BarrelClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    TSubclassOf<ACP_BodyInfo> BodyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    TSubclassOf<ACP_TriggerInfo> TriggerClass;

    // 총기 파츠 스폰 함수
    void SpawnGunParts();

    UFUNCTION()
    void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);
};
