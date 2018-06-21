#include "menu.h"
#include "ui_menu.h"
#include <QLayout>
#include <iostream>
Menu::Menu(QWidget *parent, int entriesNumPerPage) :
    QFrame(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    QIcon icon = ui->first->icon();
    icon.addPixmap(QPixmap(":/icons/first.png"), QIcon::Normal);
    icon.addPixmap(QPixmap(":/icons/firstgrey.png"), QIcon::Disabled);
    ui->first->setIcon(icon);
    icon = ui->last->icon();
    icon.addPixmap(QPixmap(":/icons/last.png"), QIcon::Normal);
    icon.addPixmap(QPixmap(":/icons/lastgrey.png"), QIcon::Disabled);
    ui->last->setIcon(icon);
    icon = ui->prev->icon();
    icon.addPixmap(QPixmap(":/icons/prev.png"), QIcon::Normal);
    icon.addPixmap(QPixmap(":/icons/prevgrey.png"), QIcon::Disabled);
    ui->prev->setIcon(icon);
    icon = ui->next->icon();
    icon.addPixmap(QPixmap(":/icons/next.png"), QIcon::Normal);
    icon.addPixmap(QPixmap(":/icons/nextgrey.png"), QIcon::Disabled);
    ui->next->setIcon(icon);
    //ui->mostLeft->setPixmap(QPixmap(":/icons/books.png"));
    QLayout *entryLayout = new QVBoxLayout();
    entryLayout->setMargin(0);
    ui->entryTable->setLayout(entryLayout);
    entriesPerPage = entriesNumPerPage;
}

Menu::~Menu()
{
    delete ui;
}

void Menu::addEntry(QWidget *newEntry){
    entries.push_back(newEntry);
    pages = (entries.size() + entriesPerPage - 1) / entriesPerPage;
    if(currentPageIndex != pages - 1){
        newEntry->setHidden(true);
    }
    QLayout *tablelayout = ui->entryTable->layout();
    tablelayout->addWidget(newEntry);
    changeUI();
}

void Menu::addEntries(std::vector<QWidget *> newEntries){
    int appended = entriesPerPage - (entries.size() % entriesPerPage);
    appended %= entriesPerPage;
    entries.insert(entries.end(), newEntries.begin(), newEntries.end());
    if(currentPageIndex != pages - 1){
        for(auto newEntry : newEntries){
            newEntry->setHidden(true);
        }
    }
    else{
        int i, end = newEntries.size();
        appended = (end < appended) ? end : appended;
        for(i = 0; i < appended; i++){
            newEntries[i]->setHidden(false);
        }
        for(; i < end; i ++){
            newEntries[i]->setHidden(true);
        }
    }
    pages = (entries.size() + entriesPerPage - 1) / entriesPerPage;
    QLayout *tablelayout = ui->entryTable->layout();
    for(auto newEntry : newEntries){
        tablelayout->addWidget(newEntry);
    }
    changeUI();
}

void Menu::removeEntry(QWidget *newEntry){
    QLayout *tablelayout = ui->entryTable->layout();
    tablelayout->removeWidget(newEntry);
}

void Menu::changeUI(){
    if(currentPageIndex == 0){
        ui->first->setDisabled(true);
        ui->prev->setDisabled(true);
    }
    else if(currentPageIndex > 0){
        ui->first->setEnabled(true);
        ui->prev->setEnabled(true);
    }
    if(currentPageIndex == pages - 1){
        ui->last->setDisabled(true);
        ui->next->setDisabled(true);
    }
    else if(currentPageIndex < pages - 1){
        ui->last->setEnabled(true);
        ui->next->setEnabled(true);
    }
    ui->currentPage->setText(tr("%1 / %2").arg(QString::number(currentPageIndex + 1), QString::number(pages)));
}

void Menu::gotoNextPage(){
    if(currentPageIndex < pages - 1){
        int end = (pages == currentPageIndex + 2) ? entries.size() : (currentPageIndex + 2) * entriesPerPage;
        int start = (currentPageIndex + 1) * entriesPerPage;
        int i;
        for(i = currentPageIndex * entriesPerPage; i < start; i ++){
            entries[i]->setHidden(true);
        }
        for(i = start; i < end; i ++){
            entries[i]->setHidden(false);
        }
        currentPageIndex ++;
        changeUI();
    }
}

void Menu::gotoPrevPage(){
    if(currentPageIndex > 0){
        int end = (pages == currentPageIndex + 1) ? entries.size() : (currentPageIndex + 1) * entriesPerPage;
        int start = currentPageIndex * entriesPerPage;
        currentPageIndex --;
        int i;
        for(i = start; i < end; i ++){
            entries[i]->setHidden(true);
        }
        for(i = currentPageIndex * entriesPerPage; i < start; i ++){
            entries[i]->setHidden(false);
        }
        changeUI();
    }
}

void Menu::gotoFirstPage(){
    if(currentPageIndex > 0){
        int end = (pages == currentPageIndex + 1) ? entries.size() : (currentPageIndex + 1) * entriesPerPage;
        int start = currentPageIndex * entriesPerPage;
        currentPageIndex = 0;
        int i;
        for(i = start; i < end; i ++){
            entries[i]->setHidden(true);
        }
        end = entriesPerPage;
        for(i = 0; i < end; i ++){
            entries[i]->setHidden(false);
        }
        changeUI();
    }
}

void Menu::gotoLastPage(){
    if(currentPageIndex < pages - 1){
        int end = (currentPageIndex + 1) * entriesPerPage;
        int i;
        for(i = currentPageIndex * entriesPerPage; i < end; i ++){
            entries[i]->setHidden(true);
        }
        end = entries.size();
        currentPageIndex = pages - 1;
        for(i = currentPageIndex * entriesPerPage; i < end; i ++){
            entries[i]->setHidden(false);
        }
        changeUI();
    }
}
