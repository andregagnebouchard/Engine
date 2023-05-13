#pragma once
#include <array>
#include <cmath>  // for floor
using namespace std;
namespace Engine
{
	// Could use template for the cell value as this is the engine, but this would be over-engineering
	class WorldGrid
	{
	public:
		struct CellLocation
		{
			int col = 0;
			int row = 0;
		};

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
		// Stack memory
		array<array<int, colQty>, rowQty> m_Grid;
		const float m_CellSizeX;
		const float m_CellSizeY;
	};
}