#include "CP_Guns.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CP_Player.h"
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

    // 파츠 정보 
    BarrelInfo = CreateDefaultSubobject<ACP_BarrelInfo>(TEXT("BarrelInfo"));
    BodyInfo = CreateDefaultSubobject<ACP_BodyInfo>(TEXT("BodyInfo"));
    TriggerInfo = CreateDefaultSubobject<ACP_TriggerInfo>(TEXT("TriggerInfo"));

    // 나이아가라 이펙트 
    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootScene);

    // 오디오 컴포넌트
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootScene);

    static ConstructorHelpers::FClassFinder<AActor> HitEffectBP(TEXT("Blueprint'/Game/FXVarietyPack/Blueprints/BP_ky_hit2.BP_ky_hit2_C'"));
    if (HitEffectBP.Succeeded())
    {
        HitEffectBPClass = HitEffectBP.Class;
    }

    AActor* OwnerActor = GetOwner();
    ACP_Player* Player = Cast<ACP_Player>(OwnerActor);
    if (Player)
    {
        InventoryRef = Player->PlayerInventory;
        UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] InventoryRef successfully set."));
    }
    // 발사 타이머
    AmmoCount = 0;
    MaxAmmo = 0;

    //발사할 프로젝타일 
    static ConstructorHelpers::FClassFinder<ACP_Projectile> ProjectileBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BP_Projectile.BP_Projectile_C'"));
    if (ProjectileBPClass.Succeeded())
    {
        ProjectileClass = ProjectileBPClass.Class;
    }

    // 발사 사운드 
    static ConstructorHelpers::FObjectFinder<USoundCue> FireSoundCueAsset(TEXT("SoundCue'/Game/Gun_BluePrint/MuzzleFlash/Demo/FPWeapon/Cue/FirstPersonTemplateWeaponFire02_Cue.FirstPersonTemplateWeaponFire02_Cue'"));
    if (FireSoundCueAsset.Succeeded() && AudioComponent)
    {
        AudioComponent->SetSound(FireSoundCueAsset.Object);
    }

    //기본 파츠 로드 
    LoadGunParts();


}


void ACP_Guns::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld())
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    TacticalLight = GetWorld()->SpawnActor<ACP_TacticalLight>(ACP_TacticalLight::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnParams);

    if (TacticalLight)
    {

        // 총기 바디에 붙이기
        TacticalLight->AttachToComponent(BodyMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Light"));
    }

}


// 틱 함수 
void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    NiagaraEffect->Deactivate();
}

void ACP_Guns::EquipPart(const FString& PartName, EGunPartType PartType)
{
    if (PartType == EGunPartType::Barrel)
    {
        if (BarrelInfo)
        {
            BarrelInfo->Initialize(PartName);  
            BarrelMesh->SetSkeletalMesh(BarrelInfo->GetMesh()->SkeletalMesh);
        }
    }
    else if (PartType == EGunPartType::Body)
    {
        if (BodyInfo)
        {
            BodyInfo->Initialize(PartName);  
            BodyMesh->SetSkeletalMesh(BodyInfo->GetMesh()->SkeletalMesh);
        }
    }
    else if (PartType == EGunPartType::Trigger)
    {
        if (TriggerInfo)
        {
            TriggerInfo->Initialize(PartName);  
            TriggerMesh->SetSkeletalMesh(TriggerInfo->GetMesh()->SkeletalMesh);
        }
    }
}





//기본 파츠 로드 
void ACP_Guns::LoadGunParts()
{
    USkeletalMesh* BarrelSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
    if (BarrelSkeletalMesh)
    {
        BarrelMesh->SetSkeletalMesh(BarrelSkeletalMesh);
        if (BarrelInfo)
        {
            BarrelInfo->Initialize("SK_BarrelBulletScatter");
        }

        UNiagaraSystem* NiagaraAsset = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, TEXT("NiagaraSystem'/Game/Gun_BluePrint/MuzzleFlash/MuzzleFlash/Niagara/NS_MuzzleFlash.NS_MuzzleFlash'")));
        if (NiagaraAsset)
        {
            NiagaraEffect->SetAsset(NiagaraAsset);
            NiagaraEffect->SetupAttachment(BarrelMesh, FName("Muzzle"));
        }
    }

    USkeletalMesh* BodySkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
    if (BodySkeletalMesh)
    {
        BodyMesh->SetSkeletalMesh(BodySkeletalMesh);
        BodyInfo->Initialize("SK_BodyFire");
    }

    USkeletalMesh* TriggerSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerSingle.SK_TriggerSingle")));
    if (TriggerSkeletalMesh)
    {
        TriggerMesh->SetSkeletalMesh(TriggerSkeletalMesh);
        TriggerInfo->Initialize("SK_TriggerAuto");
        AmmoCount = TriggerInfo->MagazineCapacity;
        MaxAmmo = TriggerInfo->MagazineCapacity * 2;
    }
}



// 무기 발사 
void ACP_Guns::Fire()
{
    if (!BarrelInfo) return;

    if (!TriggerInfo || AmmoCount <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No ammo"));
        return;
    }

    AmmoCount--;

    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));

    //  카메라 방향 가져오기
    AActor* OwnerActor = GetOwner();
    FVector AimDirection = FVector::ZeroVector;
    if (OwnerActor)
    {
        APawn* OwnerPawn = Cast<APawn>(OwnerActor);
        if (OwnerPawn && OwnerPawn->IsPlayerControlled())
        {
            APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
            if (PC)
            {
                FVector CameraLocation;
                FRotator CameraRotation;
                PC->GetPlayerViewPoint(CameraLocation, CameraRotation);  //  카메라 위치 및 회전 가져오기
                AimDirection = CameraRotation.Vector();  //  카메라가 바라보는 방향 사용
            }
        }
    }

    // 총구 방향을 에임 방향과 일치시킴
    FVector MuzzleDirection = AimDirection.IsNearlyZero() ? BarrelMesh->GetSocketRotation(FName("Muzzle")).Vector() : AimDirection;

    // 나이아가라 이펙트 실행
    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACP_Guns::DeactivateNiagaraEffect, 0.1f, false);
    }

    // 발사 사운드 실행
    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    // 히트스캔 무기 처리
    if (BarrelInfo->bIsHitscan)
    {
        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);
        QueryParams.AddIgnoredActor(GetOwner());
        QueryParams.bTraceComplex = true;

        FVector EndPoint = MuzzleLocation + (MuzzleDirection * 2000.0f);
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLocation, EndPoint, ECC_GameTraceChannel1, QueryParams);

        if (bHit)
        {
            EndPoint = HitResult.ImpactPoint;

            if (HitResult.GetActor())
            {
                ApplyDamage(HitResult.GetActor());
            }

            if (HitEffectBPClass)
            {
                AActor* HitEffect = GetWorld()->SpawnActor<AActor>(HitEffectBPClass, EndPoint, FRotator::ZeroRotator);
                if (HitEffect)
                {
                    HitEffect->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
                }
            }
        }
    }
    //  투사체 발사
    else 
    {
        if (ProjectileClass)
        {
            FRotator ProjectileRotation = MuzzleDirection.Rotation();
            ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, ProjectileRotation);
            if (Projectile)
            {
                Projectile->SetOwner(this);
                if (Projectile->ProjectileMovement)
                {
                    FVector Velocity = MuzzleDirection * 12000.f;
                    Projectile->ProjectileMovement->Velocity = Velocity;
                    Projectile->ProjectileMovement->Activate();
                }
            }

        }
    }

}


//npc 총 발사
void ACP_Guns::Fire(FVector FireDirection)
{
    if (!BarrelInfo) return;

    if (!TriggerInfo || AmmoCount <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No ammo"));
        return;
    }

    AmmoCount--;

    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));

    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACP_Guns::DeactivateNiagaraEffect, 0.1f, false);
    }

    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    if (ProjectileClass)
    {
        FRotator ProjectileRotation = FireDirection.Rotation();
        ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, ProjectileRotation);
        if (Projectile)
        {
            Projectile->SetOwner(this);
            if (Projectile->ProjectileMovement)
            {
                FVector Velocity = FireDirection * 8000.f;
                Projectile->ProjectileMovement->Velocity = Velocity;
                Projectile->ProjectileMovement->Activate();
            }
        }
    }
}




void ACP_Guns::SetInventory(UCP_Inventory* Inventory)
{
    InventoryRef = Inventory;
}


void ACP_Guns::DeactivateNiagaraEffect()
{
    if (NiagaraEffect)
    {
        NiagaraEffect->Deactivate();
    }
}

void ACP_Guns::ApplyDamage(AActor* HitActor)
{
    if (!HitActor) return;

    float TotalDamage = CalculateTotalDamage();

    AActor* OwnerActor = GetOwner();
    AController* OwnerController = nullptr;

    if (OwnerActor)
    {
        APawn* OwnerPawn = Cast<APawn>(OwnerActor);
        if (OwnerPawn)
        {
            OwnerController = OwnerPawn->GetController();
        }
    }

    // 피격 대상이 ACP_CharacterBase를 상속받는지 확인
    ACP_CharacterBase* Character = Cast<ACP_CharacterBase>(HitActor);
    if (Character)
    {
        float AppliedDamage = UGameplayStatics::ApplyDamage(
            Character,  // 적이든 플레이어든 모두 처리 가능
            TotalDamage,
            OwnerController,
            this,
            UDamageType::StaticClass()
        );
    }
}



float ACP_Guns::CalculateTotalDamage()
{
    float TotalDamage = 0.0f;
    if (TriggerInfo) TotalDamage += TriggerInfo->Damage;
    if (BodyInfo) TotalDamage += BodyInfo->Damage;
    if (BarrelInfo) TotalDamage += BarrelInfo->Damage;
    return TotalDamage;
}

void ACP_Guns::Reload()
{
    UE_LOG(LogTemp, Warning, TEXT("[ACP_guns] Reload() called."));
    if (!TriggerInfo)
    {
        UE_LOG(LogTemp, Error, TEXT("[ACP_Guns] ERROR: TriggerInfo is nullptr! Cannot reload."));
        return;
    }

    if (!InventoryRef)
    {
        UE_LOG(LogTemp, Error, TEXT("[ACP_Guns] ERROR: InventoryRef is nullptr! Cannot reload."));
        return;
    }

    int32 MagazineCapacity = TriggerInfo->MagazineCapacity;
    int32 AmmoBox = InventoryRef->GetItemCount("Ammo Pack");

    if (AmmoBox <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[ACP_Guns] No ammo available for reload!"));
        return;
    }

    if (MaxAmmo <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[ACP_Guns] Not enough reserve ammo to reload!"));
        return;
    }


    int32 AmmoNeeded = MagazineCapacity - AmmoCount;
    int32 AmmoToLoad = FMath::Min(AmmoNeeded, MaxAmmo); // MaxAmmo와 필요한 탄약 중 작은 값 선택

    AmmoCount += AmmoToLoad;
    MaxAmmo -= AmmoToLoad;

    // 사운드 재생
    USoundBase* ReloadSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Gun_BluePrint/Sound/ak_reload.ak_reload'"));
    if (ReloadSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
        UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Reload sound played successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[ACP_Guns] Failed to load reload sound! Check path."));
    }

    // 인벤토리에서 `Ammo` 1개만 제거
    UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Removing 1 Ammo from inventory."));
    FCP_ItemInfo AmmoItem;
    AmmoItem.ItemName = "Ammo Pack";
    AmmoItem.ItemType = ECP_ItemType::Ammo;
    InventoryRef->ReduceItemCountByName("Ammo Pack", 1);

    UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Reload complete. AmmoCount: %d, MaxAmmo: %d"), AmmoCount, MaxAmmo);
}


void ACP_Guns::ToggleLight()
{
    TacticalLight->ToggleLight();
}
