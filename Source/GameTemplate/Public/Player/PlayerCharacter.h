// © Anastasis Marinos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class GAMETEMPLATE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	// Player Camera & UI System //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float CameraSensitivity;
	
	
	// Player Input System//
	// Set mapping context and input action variables inside player character blueprint.
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", Meta=(AllowPrivateAccess=true))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", Meta=(AllowPrivateAccess=true))
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", Meta=(AllowPrivateAccess=true))
	class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", Meta=(AllowPrivateAccess=true))
	class UInputAction* IA_Jump;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", Meta=(AllowPrivateAccess=true))
	class UInputAction* IA_Crouch;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", Meta=(AllowPrivateAccess=true))
	class UInputAction* IA_Sprint;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input", Meta=(AllowPrivateAccess=true))
	class UInputAction* IA_Interact;
	

	// Player Movement System //
	void PlayerMove(const FInputActionValue& Value);
	void PlayerLook(const FInputActionValue& Value);
	void PlayerJump(const FInputActionValue& Value);
	void PlayerStartCrouch();
	void PlayerStopCrouch();
	void PlayerStartSprint();
	void PlayerStopSprint();
	void PlayerInteract(const FInputActionValue& Value);
	
};

