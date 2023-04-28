#pragma once
#include <array>
#include <unordered_map>
using namespace std;
namespace Engine
{
	struct CellLocation // Outside the class, as we do not need this templated
	{
		int col = 0;
		int row = 0;
	};

	template <typename CellContent, typename size_t RowCount, typename size_t ColCount>
	class WorldGrid
	{
	public:

		WorldGrid(float cellSizeX, float cellSizeY) : 
			m_CellSizeX(cellSizeX), 
			m_CellSizeY(cellSizeY) 
		{};

		CellLocation GetCellLocationFromPosition(float xPosition, float yPosition) const
		{
			CellLocation cell;
			cell.col = static_cast<int>(xPosition / m_CellSizeX);
			cell.row = static_cast<int>(yPosition / m_CellSizeY);
			return cell;
		}

		bool IsCellInbound(const CellLocation &cell) const
		{
			if (cell.row < 0 || cell.row >= RowCount || cell.col < 0 || cell.col >= ColCount)
				return false;
			return true;
		}
		CellContent GetCellValue(const CellLocation& cell) const // -1 means no one is there
		{
			return m_Grid.at(cell.row).at(cell.col);
		}
		void SetCellValue(const CellLocation& cell, int value)
		{
			m_Grid.at(cell.row).at(cell.col) = value;
		}
	private:

		array<array<CellContent, ColCount>, RowCount> m_Grid;
		float m_CellSizeX;
		float m_CellSizeY;
	};
}