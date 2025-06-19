#pragma once

#include "common.h"
#include "formula.h"

#include <optional>
#include <unordered_set>

class Cell : public CellInterface {
public:
    // ����������� ��������� ������ �� ����, ����� ������ ����� �������� �������� ������ �����
    Cell(Sheet& sheet);
    ~Cell();

    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

    // ���������� ������ �����, ������� ��������������� ������������� � ������
    // �������. ������ ������������ �� ����������� � �� �������� �������������
    // �����. � ������ ��������� ������ ������ ����.
    std::vector<Position> GetReferencedCells() const override;

private:
    bool HasCircularDependency() const;
    void InvalidateCache();

    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;
    std::unique_ptr<Impl> impl_;

    Sheet& sheet_;
    // ����� �����, �� ������� ������� ��� (������ � �������)
    std::unordered_set<Cell*> ref_cells_;
    // ����� �����, ������� ������� �� ���� (�� ���� ��� ������� ��� ������ - �����������)
    std::unordered_set<Cell*> dependent_cells_;
    // ��� ������ (��� �������)
    mutable std::optional<FormulaInterface::Value> cache_;
};