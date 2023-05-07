#pragma once
#include <Engine/WorldGrid.h>
#include "Entity.h"
#include <unordered_map>
using namespace Engine;
namespace Game
{
	class IGhostMovementBehaviour
	{
	public:
		virtual ~IGhostMovementBehaviour() = default;

		virtual CellLocation ChooseNextCellToMove() const = 0; // Will never be the current cell
	};

	class RedGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		RedGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType);
		virtual ~RedGhostMovementBehaviour() = default;

		CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
		const unordered_map<int, Entity::Type>* m_EntityIdToEntityType;
	};

	class BlueGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		BlueGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType);
		virtual ~BlueGhostMovementBehaviour() = default;

		CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
	};

	class OrangeGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		OrangeGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType);
		virtual ~OrangeGhostMovementBehaviour() = default;

		CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
	};

	class PinkGhostMovementBehaviour : public IGhostMovementBehaviour
	{
	public:
		PinkGhostMovementBehaviour(const WorldGrid* grid, const unordered_map<int, Entity::Type>* entityIdToEntityType);
		virtual ~PinkGhostMovementBehaviour() = default;

		CellLocation ChooseNextCellToMove() const override;
	private:
		const WorldGrid* m_Grid;
	};
}