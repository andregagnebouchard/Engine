#include "stdafx.h"
#include "GhostMovementBehaviour.h"
using namespace Engine;
namespace Game
{
	RedGhostMovementBehaviour::RedGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) :m_Grid(grid) {}
	BlueGhostMovementBehaviour::BlueGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) : m_Grid(grid) {}
	OrangeGhostMovementBehaviour::OrangeGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) : m_Grid(grid) {}
	PinkGhostMovementBehaviour::PinkGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) : m_Grid(grid) {}

	WorldGrid::CellLocation RedGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	WorldGrid::CellLocation BlueGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	WorldGrid::CellLocation OrangeGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	WorldGrid::CellLocation PinkGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}
}