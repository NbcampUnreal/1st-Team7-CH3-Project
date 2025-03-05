#include "CP_TacticalLight.h"
#include "Components/SpotLightComponent.h"

// 생성자
ACP_TacticalLight::ACP_TacticalLight()
{
	PrimaryActorTick.bCanEverTick = false;

	// 루트 씬 생성
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	//  Tactical Spot Light 추가 (전방 조명)
	TacticalSpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("TacticalSpotLight"));
	TacticalSpotLight->SetupAttachment(RootScene);

	// Spot Light 기본 설정
	TacticalSpotLight->SetIntensity(50000.0f); // 광원 강도 (기본 값보다 높게 설정)
	TacticalSpotLight->SetLightColor(FLinearColor::Yellow); // 빛 색상
	TacticalSpotLight->SetAttenuationRadius(1000.0f); // 감쇠 거리 (빛이 퍼지는 범위)
	TacticalSpotLight->SetOuterConeAngle(35.0f); // 빛 퍼지는 범위 (각도)
	TacticalSpotLight->SetInnerConeAngle(20.0f); // 중심 빛의 범위
	TacticalSpotLight->SetVisibility(false); // 기본적으로 비활성화 키 바인딩으로 활성화

	//  광원 방향 조정 (전방을 비추도록 설정)
	TacticalSpotLight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	TacticalSpotLight->SetRelativeLocation(FVector(0.0f, 0.0f, -8.0f));
	//  Tactical Light의 Static Mesh 로드
	TArray<FString> MeshPaths = {
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Clip.FL_Clip"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_End_1.FL_End_1"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_End_2.FL_End_2"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Handle.FL_Handle"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Head.FL_Head"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Neck_1.FL_Neck_1"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Neck_2.FL_Neck_2")
	};

	for (const FString& Path : MeshPaths)
	{
		UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, *Path);
		if (LoadedMesh)
		{
			PreloadedMeshes.Add(LoadedMesh);
		}
	}
}


void ACP_TacticalLight::BeginPlay()
{
	Super::BeginPlay();

	for (UStaticMesh* Mesh : PreloadedMeshes)
	{
		if (Mesh)
		{
			AddLightPart(Mesh);
		}
	}
}


void ACP_TacticalLight::AddLightPart(UStaticMesh* Mesh, FTransform Transform)
{
	if (!Mesh) return;

	UStaticMeshComponent* NewMeshComponent = NewObject<UStaticMeshComponent>(this);

	if (NewMeshComponent)
	{
		NewMeshComponent->SetStaticMesh(Mesh);
		NewMeshComponent->SetupAttachment(RootScene);
		NewMeshComponent->SetRelativeTransform(Transform);
		NewMeshComponent->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
		NewMeshComponent->RegisterComponent();
	}
}

void ACP_TacticalLight::ToggleLight()
{
	if (TacticalSpotLight)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ACP_TacticalLight] ToggleLight() called! TacticalSpotLight exists."));
		TacticalSpotLight->SetVisibility(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[ACP_TacticalLight] ERROR: TacticalSpotLight is nullptr!"));
	}
}
