#pragma once
#include <Engine/WorldGrid.h>
#include "EntityTypes.h"
#include <unordered_map>
using namespace Engine;
namespace Game
{
	class IGhostMovementBehaviour
	{
	public:
		virtual ~IGhostMovementBehaviour() = default;

		virtual WorldGrid::CellLocation ChooseNextCellToMove() const = 0; // Will never be the current cell
	};

	class RedGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		RedGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~RedGhostMovementBehaviour() = default;

		WorldGrid::CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
		const unordered_map<int, EntityType>* m_EntityIdToEntityType;
	};

	class BlueGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		BlueGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~BlueGhostMovementBehaviour() = default;

		WorldGrid::CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
	};

	class OrangeGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		OrangeGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~OrangeGhostMovementBehaviour() = default;

		WorldGrid::CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
	};

	class PinkGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		PinkGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, EntityType>* entityIdToEntityType);
		virtual ~PinkGhostMovementBehaviour() = default;

		WorldGrid::CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
	};
}