#pragma once
#include <stdexcept>
#include <array>
#include <unordered_map>
template <typename T, std::size_t SIZE>
// The data contained in this array is contiguous in memory to improve cache hits
class PackedArray
{
public:
  void Add(const T &data, int id)
  {
    if (m_TailIndex == SIZE - 1)
      throw std::runtime_error("PackedArray is full");
    if (m_IdToDataIndex.find(id) != m_IdToDataIndex.end())
      throw std::runtime_error("Cannot add the data in the packed array. The id already exist in the array");

    m_TailIndex++;
    m_Data.at(m_TailIndex) = data;
    m_IdToDataIndex.emplace(id, m_TailIndex);
  };

  void Delete(int id)
  {
    if (m_IdToDataIndex.find(id) == m_IdToDataIndex.end())
      throw std::runtime_error("Could not delete the data associated to the id in the packed array");
    const int deletedIndex = m_IdToDataIndex.at(id);
    const int tailId = m_IdToDataIndex.at(m_TailIndex);
    m_Data.at(deletedIndex) = m_Data.at(m_TailIndex); // The data from the tail is copied to the deleted index
    m_IdToDataIndex.at(tailId) = deletedIndex; // Update the mapping of the tail entity to point to the deleted index
    m_TailIndex--; // Reset to tail
  };

  T* GetData(int id)
  { 
    return &m_Data[m_IdToDataIndex.at(id)];
  };
private:
  std::unordered_map<int, int> m_IdToDataIndex;
  std::array<T, SIZE> m_Data;
  int m_TailIndex = -1;
};