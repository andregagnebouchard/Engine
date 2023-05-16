#include "stdafx.h"
#include "Grid.h"

namespace Engine
{
	Grid::Grid(float cellSizeX, float cellSizeY) :
		m_CellSizeX(cellSizeX),
		m_CellSizeY(cellSizeY)
	{
		for (int row(0); row < rowQty; row++)
			for (int col(0); col < colQty; col++)
				m_Grid[row][col] = EmptyGridValue;
	};

	Grid::CellLocation Grid::GetCellLocationFromPosition(float xPosition, float yPosition) const
	{
		CellLocation cell;
		cell.col = static_cast<int>(floor(xPosition / m_CellSizeX));
		cell.row = static_cast<int>(floor(yPosition / m_CellSizeY));
		return cell;
	}

	bool Grid::IsCellInbound(const CellLocation& cell) const
	{
		if (cell.row < 0 || cell.row >= rowQty || cell.col < 0 || cell.col >= colQty)
			return false;
		return true;
	}
	int Grid::GetCellValue(const CellLocation& cell) const
	{
		return m_Grid.at(cell.row).at(cell.col);
	}
	void Grid::SetCellValue(const CellLocation& cell, int value)
	{
		m_Grid.at(cell.row).at(cell.col) = value;
	}
}