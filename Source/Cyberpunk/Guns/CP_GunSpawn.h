#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Guns.h"
#include "CP_BarrelInfo.h"  // BarrelInfo 헤더 파일 인클루드
#include "CP_BodyInfo.h"    // BodyInfo 헤더 파일 인클루드
#include "CP_TriggerInfo.h" // TriggerInfo 헤더 파일 인클루드
#include "CP_GunSpawn.generated.h"

UCLASS()
class CYBERPUNK_API ACP_GunSpawn : public AActor
{
    GENERATED_BODY()

public:
    ACP_GunSpawn();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USkeletalMeshComponent* SpawnedPart;

public:
    virtual void Tick(float DeltaTime) override;

    // 루트 씬 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    // 스폰 플랫폼 (네모난 판)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* PlatformMesh;

    // Barrel 파츠에 대한 스켈레탈 메쉬 배열
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    TArray<USkeletalMesh*> BarrelMeshes;

    // Body 파츠에 대한 스켈레탈 메쉬 배열
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    TArray<USkeletalMesh*> BodyMeshes;

    // Trigger 파츠에 대한 스켈레탈 메쉬 배열
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    TArray<USkeletalMesh*> TriggerMeshes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
    ACP_Guns* Gun;  // 총기 인스턴스를 참조할 변수

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RotationPivot; // 회전 중심점

    // 파츠 스폰 함수
    void SpawnGunParts();
};