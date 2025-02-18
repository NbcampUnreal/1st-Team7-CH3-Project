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
    // 백업용

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
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

    // 배럴 메쉬를 반환하는 함수
    USkeletalMeshComponent* GetBarrelMesh() const;

    // 배럴 정보 초기화
    void InitializeBarrelInfo(const FString& MeshName);
};
