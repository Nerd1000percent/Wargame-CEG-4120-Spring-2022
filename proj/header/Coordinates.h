#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinates {
private:
  size_t row;
  size_t column;
public:
  Coordinates();
  Coordinates(size_t row, size_t column);
  void setRow(size_t newRow);
  size_t getRow();
  void setColumn(size_t newColumn);
  size_t getColumn();
};

#endif
