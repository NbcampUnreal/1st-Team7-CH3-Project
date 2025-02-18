#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Guns.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    // 총기의 기본 설정
    ACP_Guns();

protected:
    virtual void BeginPlay() override;

public:
    // 매 tick마다 호출되는 함수
    virtual void Tick(float DeltaTime) override;

    // 총기의 발사 기능
    virtual void Fire();

    // 총기의 재장전 기능
    virtual void Reload();

    // 총기의 남은 탄약 수
    int32 AmmoCount;

    // 최대 탄약 수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    int32 MaxAmmo;

    // 재장전 중 여부
    bool bIsReloading;

    // 재장전 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    float ReloadTime;

    // Root 씬 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene;

    // 총기 부품들 (스켈레탈 메쉬)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* TriggerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* ScopeMesh;

    // 배럴 설정 함수
    void SetBarrel(USkeletalMeshComponent* SelectedBarrel);
};
