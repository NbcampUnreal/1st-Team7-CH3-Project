#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.h"
#include "CP_BarrelInfo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_BarrelInfo : public ACP_GunInfo
{
    GENERATED_BODY()

public:
    ACP_BarrelInfo();

    // BarrelMesh 초기화
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    USkeletalMeshComponent* BarrelMesh;

    // 배럴 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    FString PartName;

    // 히트스캔 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    bool bIsHitscan;

    // 배럴 데미지
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    float Damage;

    // 배럴 정보 초기화 함수
    void InitializeBarrelInfo(const FString& MeshName);

    // BarrelMesh 반환 함수
    USkeletalMeshComponent* GetBarrelMesh() const;

protected:
    // RootComponent는 SceneComponent로 설정
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;
};
