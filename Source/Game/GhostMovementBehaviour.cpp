#include "stdafx.h"
#include "GhostMovementBehaviour.h"
using namespace Engine;
namespace Game
{
	RedGhostMovementBehaviour::RedGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType) :m_Grid(grid) {}
	BlueGhostMovementBehaviour::BlueGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType) : m_Grid(grid) {}
	OrangeGhostMovementBehaviour::OrangeGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType) : m_Grid(grid) {}
	PinkGhostMovementBehaviour::PinkGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType) : m_Grid(grid) {}

	CellLocation RedGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	CellLocation BlueGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	CellLocation OrangeGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	CellLocation PinkGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}
}