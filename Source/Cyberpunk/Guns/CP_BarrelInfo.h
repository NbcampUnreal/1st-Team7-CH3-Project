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

    // 배럴 메시
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    USkeletalMeshComponent* BarrelMesh;

    // 배럴 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    FString PartName;

    // 배럴 아이콘 텍스처 (경로 기반으로 로드)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FString IconTexturePath;

    // 아이콘 텍스처 (로드된 텍스처)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* IconTexture;

    // 히트스캔 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    bool bIsHitscan;

    // 배럴 데미지
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrel Info")
    float Damage;

    int32 GearCost;

    int32 GetGearCost() const { return GearCost; }

    // 초기화 함수
    virtual void Initialize(const FString& MeshName) override;

    // 아이콘 로드 함수
    void LoadIconTexture();

    virtual USkeletalMeshComponent* GetMesh() const override;

    UFUNCTION(BlueprintCallable, Category = "Gun Info")
    FString GetPartName() const { return PartName; }

    UFUNCTION(BlueprintCallable, Category = "Gun Info")
    float GetDamage() const { return Damage; }

    UFUNCTION(BlueprintCallable, Category = "Gun Info")
    bool IsHitscan() const { return bIsHitscan; }

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;
};
