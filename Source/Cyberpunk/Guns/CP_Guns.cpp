#include "CP_Guns.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"

ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootScene);

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootScene);

    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootScene);

    ScopeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ScopeMesh"));
    ScopeMesh->SetupAttachment(RootScene);
}

void ACP_Guns::Fire()
{
    // 총기 발사 로직 구현
}

void ACP_Guns::Reload()
{
    // 재장전 로직 구현
}

void ACP_Guns::SetBarrel(USkeletalMeshComponent* SelectedBarrel)
{
    if (SelectedBarrel)
    {
        BarrelMesh->SetSkeletalMesh(SelectedBarrel->SkeletalMesh);
    }
}

void ACP_Guns::SetBody(USkeletalMeshComponent* SelectedBody)
{
    if (SelectedBody)
    {
        BodyMesh->SetSkeletalMesh(SelectedBody->SkeletalMesh);
    }
}

void ACP_Guns::SetTrigger(USkeletalMeshComponent* SelectedTrigger)
{
    if (SelectedTrigger)
    {
        TriggerMesh->SetSkeletalMesh(SelectedTrigger->SkeletalMesh);
    }
}

void ACP_Guns::SetScope(USkeletalMeshComponent* SelectedScope)
{
    if (SelectedScope)
    {
        ScopeMesh->SetSkeletalMesh(SelectedScope->SkeletalMesh);
    }
}

void ACP_Guns::SetGunParts(ACP_BarrelInfo* Barrel, ACP_BodyInfo* Body, ACP_TriggerInfo* Trigger)
{
    if (Barrel)
    {
        SetBarrel(Barrel->GetBarrelMesh());
    }

    if (Body)
    {
        SetBody(Body->GetBodyMesh());
    }

    if (Trigger)
    {
        SetTrigger(Trigger->GetTriggerMesh());
    }
}
