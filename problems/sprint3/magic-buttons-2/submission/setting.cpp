#include "setting.h"
#include "ui_setting.h"

#include <prac/QInputDialog>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    auto OpenCustomUrlAction = [&]() {
        QString user_input = prac::QInputDialog::getText(this, "Введите URL", "URL:");
        OpenCustomUrl(user_input);
    };

    auto OpenCustomDirectoryAction = [&]() {
        QString user_input = prac::QInputDialog::getText(this, "Введите путь к папке", "Путь:");
        OpenCustomDirectory(user_input);
    };

    actions_.push_back({"Открыть URL", OpenCustomUrlAction});
    actions_.push_back({"Открыть папку", OpenCustomDirectoryAction});

    for (const auto& action : actions_) {
        ui->cb_action->addItem(action.name);
    }
}

Setting::~Setting() {
    delete ui;
}

void Setting::on_pb_save_clicked() {
    auto index = ui->cb_action->currentIndex();
    if (index < 0 || static_cast<size_t>(index) >= actions_.size() + 2) {
        return;
    }

    emit signalSetAction(current_button_idx_, actions_[index].name, actions_[index].action);
    ui->cb_action->setCurrentIndex(0);
    this->close();
}
