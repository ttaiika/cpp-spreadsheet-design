#pragma once

#include "common.h"
#include "formula.h"

#include <optional>
#include <unordered_set>

class Cell : public CellInterface {
public:
    //  онструктор принимает ссылку на лист, чтобы €чейка могла получать значени€ других €чеек
    Cell(Sheet& sheet);
    ~Cell();

    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

    // ¬озвращает список €чеек, которые непосредственно задействованы в данной
    // формуле. —писок отсортирован по возрастанию и не содержит повтор€ющихс€
    // €чеек. ¬ случае текстовой €чейки список пуст.
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
    // Ќабор €чеек, от которых зависит эта (ссылки в формуле)
    std::unordered_set<Cell*> ref_cells_;
    // Ќабор €чеек, которые завис€т от этой (то есть дл€ которых эта €чейка - зависимость)
    std::unordered_set<Cell*> dependent_cells_;
    //  эш €чейки (дл€ формулы)
    mutable std::optional<FormulaInterface::Value> cache_;
};