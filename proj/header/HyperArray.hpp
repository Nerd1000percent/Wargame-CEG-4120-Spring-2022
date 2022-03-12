#ifndef HyperArray_hpp
#define HyperArray_hpp

#include <vector>
#include "nlohmann/json.hpp"

/**
* @brief This is a data structure used to represent the game board.
* HyperArray objects are multi-dimensional arrays. They are internally stored as flat arrays so they can be indexed with either coordinates or just a single index value.
*/
template <class T>
class HyperArray
{

public:

  // Class constructor

  /**
  * Creates new HyperArray objects.
  * @param dimensions Vector that indicates the number of dimensions of the HyperArray object and the magnitude of each dimension.
  */
  HyperArray(const std::vector<size_t>& dimensions) : m_dimensions(dimensions)
  {
    auto num = _size();
    m_data = std::vector<T>(num);
  }

  // Attribute accessor methods

  /**
  * Gets the HyperArray's m_dimensions attribute.
  * @returns m_dimensions
  */
  std::vector<size_t> getDimensions() const
  {
    return m_dimensions;
  }

  /**
  * Gets the dimension stored at a particular index of the m_dimensions vector.
  * @param dim The index of the m_dimensions vector to be returned.
  * @returns Index dim of m_dimensions.
  */
  size_t getDimension(size_t dim) const
  {
    return m_dimensions.at(dim);
  }

  /**
  * Gets the number of values stored by the m_dimensions vector.
  * @returns The size of m_dimensions.
  */
  size_t getNumDimensions() const
  {
    return m_dimensions.size();
  }

  /**
  * Gets the size of the m_data vector.
  * @returns The size of m_data.
  */
  size_t size() const
  {
    return m_data.size();
  }

  /**
  * Gets the data stored in the HyperArray object.
  * @returns m_data
  */
  const std::vector<T>& getData() const
  {
      return m_data;
  }

  // Data structure interface

  /**
  * Gets the object stored at the index given by parameter.
  * @param index The index to have its corresponding object returned.
  * @returns The object stored at index.
  */
  T& at(size_t index)
  {
    return m_data.at(index);
  }

  /**
  * Gets the object stored at the multi-dimensional indices given by parameter.
  * @param coords A vector of indices for each dimension of the HyperArray.
  * @returns The object stored at index.
  */
  T& at(const std::vector<size_t>& coords)
  {
    return at(toIndex(coords));
  }

  /**
  * Converts multi-dimensional coordinates to the equivalent index value.
  * @param coords Vector of coordinates.
  * @returns Index equivalent to the coordinates passed in.
  */
  size_t toIndex(const std::vector<size_t>& coords) const
  {
    size_t index = 0;
    size_t skip = 1;
    for (size_t i = m_dimensions.size(); i > 0; i--)
    {
      index += skip * coords.at(i - 1);
      skip *= m_dimensions.at(i - 1);
    }
    return index;
  }

  /**
  * Converts index values to the equivalent multi-dimensional coordinates.
  * @param index Index value.
  * @returns Set of coordinates equivalent to the index value passed in.
  */
  std::vector<size_t> toCoords(size_t index) const
  {
    std::vector<size_t> coords(m_dimensions.size());
    for (size_t i = 0; i < m_dimensions.size(); i++)
    {
      auto& d = m_dimensions.at();
      coords[m_dimensions.size() - i - 1] = index % d;
      index /= d;
    }
    return coords;
  }

private:
  
  /**
  * This is a vector of dimensions for the HyperArray. The size of the vector is the number of dimensions and each value stored in the vector is the magnitude of a dimension.
  */
  std::vector<size_t> m_dimensions;

  /**
  * This is a multi-dimensional vector used to store the data of the HyperArray object.
  */
  std::vector<T> m_data;

  /**
  * Helper function for the class constructor that multiplies all the dimensions in m_dimensions together to get the size of the HyperArray object.
  */
  size_t _size() const
  {
    if (!m_dimensions.size())
      return 0;
    size_t num = 1;
    for (auto d : m_dimensions)
      num *= d;
    return num;
  }

}; // end HyperArray class

// Serializer methods

/**
* Writes the data from a HyperArray object to a JSON.
* @param j JSON to be written to.
* @param h HyperArray having its data written to a JSON.
*/
template <class T>
void to_json(nlohmann::json& j, const HyperArray<T>& h)
{
  j["dimensions"] = h.getDimensions();
  j["data"] = h.getData();
}

/**
* Reads values from a JSON into a HyperArray object.
* @param j JSON being read from.
* @param u HyperArray having values read in from the JSON.
*/
template <class T>
void from_json(const nlohmann::json& j, HyperArray<T>& h)
{
  std::vector<size_t> dimensions;
  j["dimensions"].get_to(dimensions);
  size_t num = 1;
  for (auto d : dimensions)
    num *= d;
  std::vector<T> data;
  j["data"].get_to(data);
  h = HyperArray<T>(dimensions);
  for (size_t i = 0; i < data.size(); i++)
    h.at(i) = data.at(i);
}

#endif
