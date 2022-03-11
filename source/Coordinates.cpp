#include "Coordinates.h"
using namespace std;
Coordinates::Coordinates() {
    this.column = 0;
    this.row = 0;
}

Coordinates::Coordinates(auto column, auto row) {
    this.column = column;
    this.row = row;
}

auto Coordinates::setColumn(auto newColumn) {
    this.column = newColumn;
}

auto Coordinates::getColumn () {
    auto c = this.column;
    return c;
}

auto Coordinates::setRow(auto newRow) {
    this.row = newRow;
}

auto Coordinates::getRow() {
    auto r = this.row;
    return r;
}