// Copyright (c) 2017-2019 The PENGOLINCOIN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZPGOCONTROLDIALOG_H
#define ZPGOCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zpgo/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZPgoControlDialog;
}

class CZPgoControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZPgoControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZPgoControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZPgoControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZPgoControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZPgoControlDialog(QWidget *parent);
    ~ZPgoControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZPgoControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZPgoControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZPGOCONTROLDIALOG_H
