#include "CP_BodyInfo.h"
#include "Engine/Texture2D.h"

ACP_BodyInfo::ACP_BodyInfo()
{
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootSceneComponent);

    // 기본값 설정
    IconTexture = nullptr;
    IconTexturePath = TEXT(""); // 기본 경로 초기화
}

void ACP_BodyInfo::Initialize(const FString& MeshName)
{
    USkeletalMesh* LoadedMesh = nullptr;

    if (MeshName == "SK_BodyTesla")
    {
        PartName = "SK_BodyTesla";
        Damage = 100.0f;
        MovementSpeed = 1.0f;
        GearCost = 5;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyTesla.SK_BodyTesla")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BodyTesla.SK_BodyTesla");
    }
    else if (MeshName == "SK_BodyNormal")
    {
        PartName = "SK_BodyNormal";
        Damage = 130.0f;
        MovementSpeed = 0.9f;
        GearCost = 4;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyNormal.SK_BodyNormal")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BodyNormal.SK_BodyNormal");
    }
    else if (MeshName == "SK_BodyFire")
    {
        PartName = "SK_BodyFire";
        Damage = 200.0f;
        MovementSpeed = 0.5f;
        GearCost = 5;
        LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
        IconTexturePath = TEXT("/Game/Gun_BluePrint/RenderTargets/SK_BodyFire.SK_BodyFire");
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Body: %s"), *MeshName);
    }

    if (LoadedMesh)
    {
        BodyMesh->SetSkeletalMesh(LoadedMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
    }

    // 아이콘 로드
    LoadIconTexture();
}

/** 아이콘 로드 함수 */
void ACP_BodyInfo::LoadIconTexture()
{
    if (!IconTexturePath.IsEmpty())
    {
        IconTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *IconTexturePath));
        if (!IconTexture)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load IconTexture: %s"), *IconTexturePath);
        }
    }
}

USkeletalMeshComponent* ACP_BodyInfo::GetMesh() const
{
    return BodyMesh;
}
