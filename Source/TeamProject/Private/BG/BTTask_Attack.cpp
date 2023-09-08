// Fill out your copyright notice in the Description page of Project Settings.


#include "BG/BTTask_Attack.h"
#include "AIController.h"
#include "EnemyCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;
}

