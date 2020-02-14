// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Arkde_RoomPuzzleTarget : TargetRules
{
	public Arkde_RoomPuzzleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Arkde_RoomPuzzle" } );
	}
}
