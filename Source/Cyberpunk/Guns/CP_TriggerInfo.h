#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunPart.h"
#include "Engine/Texture2D.h"
#include "CP_TriggerInfo.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API ACP_TriggerInfo : public AActor, public IGunPart
{
    GENERATED_BODY()

public:
    ACP_TriggerInfo();

    /** 트리거 메쉬 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    USkeletalMeshComponent* TriggerMesh;

    /** 트리거 이름 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    FString PartName;

    /** 트리거 데미지 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    float Damage;

    /** 탄창 크기 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger Info")
    int32 MagazineCapacity;

    /** 아이콘 텍스처 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* IconTexture;

    /** 아이콘 텍스처 경로 */
    FString IconTexturePath;

    /** 트리거 정보 초기화 함수 */
    virtual void Initialize(const FString& MeshName) override;

    /** 트리거 메쉬를 반환하는 함수 */
    virtual USkeletalMeshComponent* GetMesh() const override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;

private:
    /** 아이콘 로드 함수 */
    void LoadIconTexture();
};
