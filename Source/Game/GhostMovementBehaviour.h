#pragma once
#include <Engine/Grid.h>
#include "EntityTypes.h"
#include <unordered_map>
namespace Game
{
	class IGhostMovementBehaviour
	{
	public:
		virtual ~IGhostMovementBehaviour() = default;

		virtual Engine::Grid::CellLocation ChooseNextCellToMove() const = 0; // Guaranteed to never be the current cell
	};

	class RedGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		RedGhostMovementBehaviour(const Engine::Grid *grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~RedGhostMovementBehaviour() = default;

		Engine::Grid::CellLocation ChooseNextCellToMove() const override;
	private:
		const Engine::Grid* m_Grid; // Owner is EntityFactory
		const unordered_map<int, EntityType>* m_EntityIdToEntityType; // Owner is EntityFactory
	};

	class BlueGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		BlueGhostMovementBehaviour(const Engine::Grid* grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~BlueGhostMovementBehaviour() = default;

		Engine::Grid::CellLocation ChooseNextCellToMove() const override;
	private:
		const Engine::Grid* m_Grid; // Owner is EntityFactory
	};

	class OrangeGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		OrangeGhostMovementBehaviour(const Engine::Grid* grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~OrangeGhostMovementBehaviour() = default;

		Engine::Grid::CellLocation ChooseNextCellToMove() const override;
	private:
		const Engine::Grid* m_Grid; // Owner is EntityFactory
	};

	class PinkGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		PinkGhostMovementBehaviour(const Engine::Grid* grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~PinkGhostMovementBehaviour() = default;

		Engine::Grid::CellLocation ChooseNextCellToMove() const override;
	private:
		const Engine::Grid* m_Grid; // Owner is EntityFactory
	};
}