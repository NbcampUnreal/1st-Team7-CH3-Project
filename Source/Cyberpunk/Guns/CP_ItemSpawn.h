#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CP_Ammo.h"
#include "CP_Gear.h"
#include "CP_Heal.h"
#include "Character/CP_Player.h"
#include "Inventory/CP_ItemInfo.h"
#include "CP_ItemSpawn.generated.h"

UCLASS()
class CYBERPUNK_API ACP_ItemSpawn : public AActor
{
    GENERATED_BODY()

public:
    ACP_ItemSpawn();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    /** 아이템 스폰 함수 */
    void SpawnItem();

    /** 아이템 획득 시 호출 */
    UFUNCTION()
    void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    /** 랜덤으로 생성된 아이템 정보 */
    FCP_ItemInfo SpawnedItemInfo;

    /** 스폰된 아이템 액터 */
    AActor* SpawnedItem;

    /** 루트 컴포넌트 */
    UPROPERTY()
    USceneComponent* RootScene;

    /** 충돌 컴포넌트 */
    UPROPERTY()
    USphereComponent* CollisionComponent;

    /** Ammo, Gear, Heal 클래스 저장 */
    UPROPERTY()
    TSubclassOf<AActor> AmmoClass;

    UPROPERTY()
    TSubclassOf<AActor> GearClass;

    UPROPERTY()
    TSubclassOf<AActor> HealClass;

    /** 초기 스폰 위치 */
    FVector InitialSpawnLocation;

    /** 시간 경과 */
    float TimeElapsed;
};
