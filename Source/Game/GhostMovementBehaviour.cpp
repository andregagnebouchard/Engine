#include "stdafx.h"
#include "GhostMovementBehaviour.h"
using namespace Engine;
namespace Game
{
	RedGhostMovementBehaviour::RedGhostMovementBehaviour(const Engine::Grid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) :m_Grid(grid) {}
	BlueGhostMovementBehaviour::BlueGhostMovementBehaviour(const Engine::Grid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) : m_Grid(grid) {}
	OrangeGhostMovementBehaviour::OrangeGhostMovementBehaviour(const Engine::Grid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) : m_Grid(grid) {}
	PinkGhostMovementBehaviour::PinkGhostMovementBehaviour(const Engine::Grid* grid, const unordered_map<int, EntityType>* entityIdToEntityType) : m_Grid(grid) {}

	Engine::Grid::CellLocation RedGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	Engine::Grid::CellLocation BlueGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	Engine::Grid::CellLocation OrangeGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}

	Engine::Grid::CellLocation PinkGhostMovementBehaviour::ChooseNextCellToMove() const
	{
		return {};
	}
}