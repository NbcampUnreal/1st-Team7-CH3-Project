#include "CP_TriggerInfo.h"

ACP_TriggerInfo::ACP_TriggerInfo()
{
    // 기본 RootComponent로 SceneComponent 설정
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;  // RootComponent 설정

    // TriggerMesh 초기화
    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootSceneComponent);  // TriggerMesh는 RootComponent의 자식
}

void ACP_TriggerInfo::Initialize(const FString& MeshName)
{
    if (MeshName == "SK_TriggerAuto")
    {
        PartName = "SK_TriggerAuto";
        Damage = 10.0f;
        MagazineCapacity = 70;

        // StaticLoadObject로 메시 로드
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerAuto.SK_TriggerAuto")));
        if (LoadedMesh)
        {
            TriggerMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_TriggerBurst")
    {
        PartName = "SK_TriggerBurst";
        Damage = 20.0f;
        MagazineCapacity = 60;

        // StaticLoadObject로 메시 로드
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerBurst.SK_TriggerBurst")));
        if (LoadedMesh)
        {
            TriggerMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_StockStandard")
    {
        PartName = "SK_StockStandard";
        Damage = 25.0f;
        MagazineCapacity = 50;

        // StaticLoadObject로 메시 로드
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_StockStandard.SK_StockStandard")));
        if (LoadedMesh)
        {
            TriggerMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_StockHeavy")
    {
        PartName = "SK_StockHeavy";
        Damage = 30.0f;
        MagazineCapacity = 30;

        // StaticLoadObject로 메시 로드
        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_StockHeavy.SK_StockHeavy")));
        if (LoadedMesh)
        {
            TriggerMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Trigger: %s"), *MeshName);
    }
}

USkeletalMeshComponent* ACP_TriggerInfo::GetMesh() const
{
    return TriggerMesh;
}
