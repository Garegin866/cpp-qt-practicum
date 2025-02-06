#pragma once

#ifdef PRAC_TESTS
#include "../tests/model.h"
#include "../tests/view.h"
#else
#include "model.h"
#include "view.h"
#endif

class Controller {
public:

    Controller() {
        auto move_callback = [this](size_t x, size_t y) {
            auto symbol = model_.DoMove(x, y);
            if (symbol == Symbol::kEmpty) {
                return;
            }

            view_.UpdateCell(x, y, ToQString(symbol));
            if (model_.GetWinner().has_value()) {
                if (model_.GetWinner().value() == Symbol::kEmpty) {
                    view_.SetStatus("Ничья");
                    view_.SetStatusStyle("red", true);
                } else {
                    view_.SetStatus("Выиграл " + ToQString(model_.GetWinner().value()));
                    view_.SetStatusStyle("green", true);
                    for (auto [x, y] : model_.GetWinnerPath()) {
                        view_.SetCellStyle(x, y, "green", true);
                    }
                }
            } else {
                view_.SetStatus("Ход игрока " + ToQString(model_.GetNextPlayer()));
                view_.SetStatusStyle("black", false);
            }
        };
        view_.SetMoveCallback(move_callback);

        auto newgame_callback = [this](size_t size_x, size_t size_y) {
            model_.Reset(size_x, size_y);
            view_.SetupField(size_x, size_y);
            view_.SetStatus("Ход игрока " + ToQString(model_.GetNextPlayer()));
            view_.SetStatusStyle("black", false);
        };
        view_.SetNewgameCallback(newgame_callback);

        view_.show();
        newgame_callback(3, 3);
    }

private:
    Model model_;
    View view_;
};
