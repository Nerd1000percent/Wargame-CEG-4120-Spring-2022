#ifndef COORDINATES-H
#define COORDINATES-H
#pragma once

class Coordinates {
    private:
        auto row;
        auto column;
    public:
        Coordinates ();
        Coordinates (row, column);
        auto setRow(auto newRow);
        auto getRow();
        auto setColumn(auto newColumn)
        auto getColumn();
        
}