#ifndef HyperArray_hpp
#define HyperArray_hpp

#include <vector>
#include "nlohmann/json.hpp"

template <class T>
class HyperArray
{
public:
  HyperArray(const std::vector<size_t>& dimensions) : m_dimensions(dimensions)
  {
    auto num = _size();
    m_data = std::vector<T>(num);
  }

  std::vector<size_t> getDimensions() const
  {
    return m_dimensions;
  }

  size_t getDimension(size_t dim) const
  {
    return m_dimensions.at(dim);
  }

  size_t getNumDimensions() const
  {
    return m_dimensions.size();
  }

  size_t size() const
  {
    return m_data.size();
  }

  T& at(size_t index)
  {
    return m_data.at(index);
  }

  T& at(const std::vector<size_t>& coords)
  {
    return at(toIndex(coords));
  }

  size_t toIndex(const std::vector<size_t>& coords) const {
    size_t index = 0;
    size_t skip = 1;
    for (size_t i = m_dimensions.size(); i > 0; i--)
    {
      index += skip * coords.at(i - 1);
      skip *= m_dimensions.at(i - 1);
    }
    return index;
  }

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

  const std::vector<T>& getData() const
  {
    return m_data;
  }

private:
  std::vector<size_t> m_dimensions;
  std::vector<T> m_data;

  size_t _size() const
  {
    if (!m_dimensions.size())
      return 0;
    size_t num = 1;
    for (auto d : m_dimensions)
      num *= d;
    return num;
  }
};

// serializers
template <class T>
void to_json(nlohmann::json& j, const HyperArray<T>& h)
{
  j["dimensions"] = h.getDimensions();
  j["data"] = h.getData();
}

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
