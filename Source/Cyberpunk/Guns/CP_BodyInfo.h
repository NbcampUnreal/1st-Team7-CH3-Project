#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunPart.h"
#include "Engine/Texture2D.h"
#include "CP_BodyInfo.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API ACP_BodyInfo : public AActor, public IGunPart
{
    GENERATED_BODY()

public:
    ACP_BodyInfo();

    /** BodyMesh 초기화 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    USkeletalMeshComponent* BodyMesh;

    /** 바디 이름 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    FString PartName;

    /** 바디 데미지 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float Damage;

    /** 이동 속도 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float MovementSpeed;

    /** 아이콘 텍스처 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* IconTexture;

    /** 아이콘 텍스처 경로 */
    FString IconTexturePath;

    /** Body 정보 초기화 함수 */
    virtual void Initialize(const FString& MeshName) override;

    /** BodyMesh 반환 함수 */
    virtual USkeletalMeshComponent* GetMesh() const override;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;

private:
    /** 아이콘 로드 함수 */
    void LoadIconTexture();
};
