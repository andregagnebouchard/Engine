#pragma once
#include <stdexcept>
#include <array>
#include <unordered_map>
using namespace std;
namespace Engine
{
  template <typename T, size_t SIZE>
  // The data contained in this array is contiguous in memory to improve cache hits
  class PackedArray
  {
  public:
    void Add(const T& data, int id)
    {
      if (m_TailIndex == SIZE - 1)
        throw runtime_error("PackedArray is full");
      if (m_IdToIndex.find(id) != m_IdToIndex.end())
        throw runtime_error("Cannot add the data in the packed array. The id already exist in the array");

      m_TailIndex++;
      m_Data.at(m_TailIndex) = data;
      m_IdToIndex.emplace(id, m_TailIndex);
      m_IndexToId.emplace(m_TailIndex, id);
    };

    void Delete(int id)
    {
      if (m_IdToIndex.find(id) == m_IdToIndex.end())
        throw runtime_error("Could not delete the data associated to the id in the packed array");
      const int deletedIndex = m_IdToIndex.at(id);
      const int tailId = m_IndexToId.at(m_TailIndex);
      m_Data.at(deletedIndex) = m_Data.at(m_TailIndex); // Copy tail data to new spot
      m_IdToIndex.at(tailId) = deletedIndex;
      m_IndexToId.at(deletedIndex) = tailId;
      m_TailIndex--; // Reset to tail
    };

    T* GetData(int id)
    {
      return &m_Data[m_IdToIndex.at(id)];
    };
  private:
    // I need hash maps on the stack
    unordered_map<int, int> m_IdToIndex;
    unordered_map<int, int> m_IndexToId;
    array<T, SIZE> m_Data;
    int m_TailIndex = -1;
  };
}