#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunPart.h"  
#include "CP_BarrelInfo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_BarrelInfo : public AActor, public IGunPart
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
    virtual void Initialize(const FString& MeshName) override;

    // BarrelMesh 반환 함수
    virtual USkeletalMeshComponent* GetMesh() const override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;
};
