#include "stdafx.h"
#include "WorldGrid.h"

namespace Engine
{
	WorldGrid::WorldGrid(float cellSizeX, float cellSizeY) :
		m_CellSizeX(cellSizeX),
		m_CellSizeY(cellSizeY)
	{
		for (int row(0); row < rowQty; row++)
			for (int col(0); col < colQty; col++)
				m_Grid[row][col] = EmptyGridValue;
	};

	CellLocation WorldGrid::GetCellLocationFromPosition(float xPosition, float yPosition) const
	{
		CellLocation cell;
		cell.col = static_cast<int>(floor(xPosition / m_CellSizeX));
		cell.row = static_cast<int>(floor(yPosition / m_CellSizeY));
		return cell;
	}

	bool WorldGrid::IsCellInbound(const CellLocation& cell) const
	{
		if (cell.row < 0 || cell.row >= rowQty || cell.col < 0 || cell.col >= colQty)
			return false;
		return true;
	}
	int WorldGrid::GetCellValue(const CellLocation& cell) const
	{
		return m_Grid.at(cell.row).at(cell.col);
	}
	void WorldGrid::SetCellValue(const CellLocation& cell, int value)
	{
		m_Grid.at(cell.row).at(cell.col) = value;
	}
}