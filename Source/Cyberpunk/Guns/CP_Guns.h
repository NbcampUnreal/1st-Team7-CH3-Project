#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "CP_Guns.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Guns : public AActor
{
    GENERATED_BODY()

public:
    // 총기의 기본 설정
    ACP_Guns();

protected:

public:


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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BarrelMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* BodyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* TriggerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun Parts")
    USkeletalMeshComponent* ScopeMesh;

    // 배럴 설정 함수
    void SetBarrel(USkeletalMeshComponent* SelectedBarrel);

    // 바디 설정 함수
    void SetBody(USkeletalMeshComponent* SelectedBody);

    // 트리거 설정 함수
    void SetTrigger(USkeletalMeshComponent* SelectedTrigger);

    // 스코프 설정 함수
    void SetScope(USkeletalMeshComponent* SelectedScope);

    // 총기 부품들을 설정하는 함수
    void SetGunParts(ACP_BarrelInfo* Barrel, ACP_BodyInfo* Body, ACP_TriggerInfo* Trigger);
};
