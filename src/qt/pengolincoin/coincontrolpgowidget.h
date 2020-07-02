// Copyright (c) 2019 The PENGOLINCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINCONTROLPGOWIDGET_H
#define COINCONTROLPGOWIDGET_H

#include <QDialog>

namespace Ui {
class CoinControlPgoWidget;
}

class CoinControlPgoWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlPgoWidget(QWidget *parent = nullptr);
    ~CoinControlPgoWidget();

private:
    Ui::CoinControlPgoWidget *ui;
};

#endif // COINCONTROLPGOWIDGET_H
