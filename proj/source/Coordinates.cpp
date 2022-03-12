#include "Coordinates.h"
using namespace std;

Coordinates::Coordinates(size_t column, size_t row) {
  m_column = column;
  m_row = row;
}

void Coordinates::setColumn(size_t column) {
  m_column = column;
}

size_t Coordinates::getColumn() {
  return m_column;
}

void Coordinates::setRow(size_t row) {
  m_row = row;
}

size_t Coordinates::getRow() {
  return m_row;
}
