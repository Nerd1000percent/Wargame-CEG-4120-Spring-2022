#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinates {
private:
  size_t m_row = 0;
  size_t m_column = 0;
public:
  Coordinates() = default;
  Coordinates(size_t row, size_t column);
  void setRow(size_t row);
  size_t getRow();
  void setColumn(size_t column);
  size_t getColumn();
};

#endif
