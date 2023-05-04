#pragma once
#include <array>
#include <cmath>  // for floor
using namespace std;
namespace Engine
{
	struct CellLocation // Outside the class, as we do not need this templated
	{
		int col = 0;
		int row = 0;
	};

	// Could use template for the cell value as this is the engine, but this would be over-engineering
	class WorldGrid
	{
	public:
		WorldGrid(float cellSizeX, float cellSizeY);

		static const int EmptyGridValue = -1;

		CellLocation GetCellLocationFromPosition(float xPosition, float yPosition) const;
		bool IsCellInbound(const CellLocation& cell) const;
		int GetCellValue(const CellLocation& cell) const;
		void SetCellValue(const CellLocation& cell, int value);

		static constexpr int rowQty = 10;
		static constexpr int colQty = 10;

		float GetCellSizeX() const { return m_CellSizeX; };
		float GetCellSizey() const { return m_CellSizeY; };
	private:
		array<array<int, colQty>, rowQty> m_Grid;
		float m_CellSizeX;
		float m_CellSizeY;
	};
}