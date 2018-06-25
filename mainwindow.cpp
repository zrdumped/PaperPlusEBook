#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "qrcode.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QLayout>
#include <QStackedLayout>
#include <QFileDialog>
#include <QLabel>
#include <QFrame>
#include <QDesktopWidget>
#include <QCursor>

//454545,3C3C3C
/*
 * Menu: QPushButton{background-color: rgb(179, 208, 255); border-radius: 20px;  border: 1px rgb(179, 208, 255);} minimum height: 40px
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window = NULL;
    QDesktopWidget *desktop = QApplication::desktop();
    int screen_count = desktop->screenCount();
    int width = desktop->width() / screen_count;
    //set QZxing side lengths
    ui->leftQZxing->setMinimumWidth(qzxingSideLength);
    ui->rightQZxing->setMinimumWidth(qzxingSideLength);
    ui->leftQZxing->setMinimumHeight(qzxingSideLength);
    ui->rightQZxing->setMinimumHeight(qzxingSideLength);
    ui->leftQZxing->setMaximumWidth(qzxingSideLength);
    ui->rightQZxing->setMaximumWidth(qzxingSideLength);
    ui->leftQZxing->setMaximumHeight(qzxingSideLength);
    ui->rightQZxing->setMaximumHeight(qzxingSideLength);
    //set Paddings
    ui->leftPadding->setMinimumWidth(sidePaddingWidth);
    ui->rightPadding->setMinimumWidth(sidePaddingWidth);
    ui->middleUpPadding->setMinimumWidth(middlePaddingWidth);
    ui->middlePadding->setMinimumWidth(middlePaddingWidth);
    ui->middlePadding->setMaximumWidth(middlePaddingWidth);
    ui->leftPadding->setMaximumWidth(sidePaddingWidth);
    ui->rightPadding->setMaximumWidth(sidePaddingWidth);
    ui->middleUpPadding->setMaximumWidth(middlePaddingWidth);
    //set UI icons and hide
    //imageConfigure
    QIcon icon = ui->imageConfigure->icon();
    ui->imageConfigure->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/imageConfigure.png"), QIcon::Normal);
    ui->imageConfigure->setIcon(icon);
    //ui->imageConfigure->setHidden(true);
    //book selector
    icon = ui->bookSelector->icon();
    ui->bookSelector->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/books.png"), QIcon::Normal);
    ui->bookSelector->setIcon(icon);
    ui->bookSelector->setHidden(true);
    //note selector
    icon = ui->noteSelector->icon();
    ui->noteSelector->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/notes.png"), QIcon::Normal);
    ui->noteSelector->setIcon(icon);
    ui->noteSelector->setHidden(true);
    //pen
    icon = ui->penUI->icon();
    ui->penUI->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/pencil.png"), QIcon::Normal, QIcon::Off);
    icon.addPixmap(QPixmap(":/icons/pencil.png"), QIcon::Normal, QIcon::On);
    ui->penUI->setIcon(icon);
    ui->penUI->setCheckable(true);
    ui->penUI->setChecked(false);
    ui->penUI->setHidden(true);
    //eraser
    icon = ui->eraserUI->icon();
    ui->eraserUI->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/eraser.png"), QIcon::Normal, QIcon::Off);
    icon.addPixmap(QPixmap(":/icons/eraser.png"), QIcon::Normal, QIcon::On);
    ui->eraserUI->setIcon(icon);
    ui->eraserUI->setCheckable(true);
    ui->eraserUI->setChecked(false);
    ui->eraserUI->setHidden(true);
    //page offset setter
    icon = ui->pageOffsetSetter->icon();
    ui->pageOffsetSetter->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/offset.png"), QIcon::Normal);
    ui->pageOffsetSetter->setIcon(icon);
    ui->pageOffsetSetter->setHidden(true);
    //day or night
    icon = ui->dayOrNight->icon();
    ui->dayOrNight->setIconSize(QSize(iconSideLength, iconSideLength));
    icon.addPixmap(QPixmap(":/icons/sun.png"), QIcon::Normal, QIcon::On);
    icon.addPixmap(QPixmap(":/icons/moon.png"), QIcon::Normal, QIcon::Off);
    ui->dayOrNight->setCheckable(true);
    ui->dayOrNight->setIcon(icon);
    ui->dayOrNight->setHidden(true);
    //hide bookname
    ui->bookName->setHidden(true);
    ui->bookName->setMinimumWidth(200);
    //testQRCode(ui->label);
    //generateQRCodes(100);
    //for now, for debug...
    //showAllUIs();
    //bookMenu
    bookMenu = new Menu(this, entryPerPage);
    //noteMenu
    noteMenu = new Menu(this, entryPerPage);
    //penStyle
    penStyle = new ArrowWidget(this);
    penStyle->setHidden(true);
    //choosebookpage
    choosebookpage = new ChooseBookPage(this);
    QObject::connect(choosebookpage->addBookBtn(), &QPushButton::clicked, this, &MainWindow::createNewBook);
    //choosenotepage
    choosenotepage = new ChooseNotePage(this);
    QObject::connect(choosenotepage->addNoteBtn(), &QPushButton::clicked, this, &MainWindow::createNewNote);
    QObject::connect(choosenotepage->returnBtn(), &QPushButton::clicked, this, &MainWindow::backToSelectBook);
    //empty book
    emptybookpage = new EmptyBook(this);
    QObject::connect(emptybookpage->addBookBtn(), &QPushButton::clicked, this, &MainWindow::createNewBook);
    //empty note
    emptynotepage = new EmptyNote(this);
    QObject::connect(emptynotepage->addNoteBtn(), &QPushButton::clicked, this, &MainWindow::createNewNote);
    //pages
    leftPage = new SinglePage(this);
    rightPage = new SinglePage(this);
    //fix page and ui bar size

    int pageWidth = (width - middlePaddingWidth - sidePaddingWidth * 2) / 2;
    ui->leftPage->setMinimumWidth(pageWidth);
    ui->rightPage->setMinimumWidth(pageWidth);
     ui->leftFrame->setMinimumWidth(pageWidth);
     ui->rightFrame->setMinimumWidth(pageWidth);
    ui->leftUpBar->setMinimumHeight(qzxingSideLength);
    ui->rightUpBar->setMinimumHeight(qzxingSideLength);
    //setup page layout
    ui->leftPage->setLayout(new QStackedLayout(ui->leftPage));
    ui->rightPage->setLayout(new QStackedLayout(ui->rightPage));
    leftPageStack = (QStackedLayout *)ui->leftPage->layout();
    leftPageStack->setMargin(0);
    leftPageStack->addWidget(choosebookpage);
    leftPageStack->addWidget(choosenotepage);
    leftPageStack->addWidget(leftPage);
    rightPageStack = (QStackedLayout *)ui->rightPage->layout();
    rightPageStack->setMargin(0);
    rightPageStack->addWidget(emptybookpage);
    rightPageStack->addWidget(emptynotepage);
    rightPageStack->addWidget(rightPage);
    rightPageStack->addWidget(bookMenu);
    rightPageStack->addWidget(noteMenu);

    //rightPGLayout->addWidget(choosebookpage);
    //ui->leftPage->setLayout(leftPGLayout);
    //eraserStyle
    //eraserStyle = new ArrowWidget(this);
    //offsetSetter
    //offsetSetter = new ArrowWidget(this);
    //white panel
    whitePanel = new QPushButton(this);
    whitePanel->setStyleSheet("background-color:rgb(255,255,255,100)");
    whitePanel->setHidden(true);
    QObject::connect(whitePanel, &QPushButton::clicked, this, &MainWindow::backToRead);
    //6 modals
    bookentrymodal = new bookEntryModal(this);
    noteentrymodal = new noteEntryModal(this);
    bookentryuppermodal = new bookEntryUpperModal(this);
    noteentryuppermodal = new noteEntryUpperModal(this);
    noteentryedit = new noteEntryEdit(this);
    noteentryeditupper = new noteEntryEditUpper(this);
    bookentrymodal->setHidden(true);
    noteentrymodal->setHidden(true);
    bookentryuppermodal->setHidden(true);
    noteentryuppermodal->setHidden(true);
    noteentryedit->setHidden(true);
    noteentryeditupper->setHidden(true);
    QPushButton *cancel = bookentrymodal->cancelButton();
    QObject::connect(cancel, &QPushButton::clicked, this, &MainWindow::backToRead);
    cancel = noteentrymodal->cancelButton();
    QObject::connect(cancel, &QPushButton::clicked, this, &MainWindow::backToRead);
    cancel = bookentryuppermodal->cancelButton();
    QObject::connect(cancel, &QPushButton::clicked, this, &MainWindow::backToRead);
    cancel = noteentryuppermodal->cancelButton();
    QObject::connect(cancel, &QPushButton::clicked, this, &MainWindow::backToRead);
    cancel = noteentryedit->cancelButton();
    QObject::connect(cancel, &QPushButton::clicked, this, &MainWindow::backToRead);
    cancel = noteentryeditupper->cancelButton();
    QObject::connect(cancel, &QPushButton::clicked, this, &MainWindow::backToRead);
    QPushButton *confirm = bookentrymodal->confirmButton();
    QObject::connect(confirm, &QPushButton::clicked, this, &MainWindow::selectBook);
    confirm = bookentryuppermodal->confirmButton();
    QObject::connect(confirm, &QPushButton::clicked, this, &MainWindow::selectBook);
    confirm = noteentrymodal->confirmButton();
    QObject::connect(confirm, &QPushButton::clicked, this, &MainWindow::selectNote);
    confirm = noteentryuppermodal->confirmButton();
    QObject::connect(confirm, &QPushButton::clicked, this, &MainWindow::selectNote);
    confirm = noteentryedit->confirmButton();
    QObject::connect(confirm, &QPushButton::clicked, this, &MainWindow::addNote);
    confirm = noteentryeditupper->confirmButton();
    QObject::connect(confirm, &QPushButton::clicked, this, &MainWindow::addNoteUp);
    //set daymode Lighting
    changeLightingMode();
    //set up left page
    leftPageStack->setCurrentWidget(choosebookpage);
    //load book menu
    loadAllBookEntries();
    this->showFullScreen();
usePen();

}

MainWindow::~MainWindow()
{
    bookmanager.closeBook();
    autoSaveNote();
    delete ui;
}

void MainWindow::normalWarning(QString msg){
    QMessageBox msgBox(QMessageBox::Warning, tr("警告"), msg, 0, this);
    msgBox.addButton(tr("确认"), QMessageBox::AcceptRole);
    msgBox.setModal(false);
    msgBox.exec();
}

void MainWindow::normalInformation(QString msg){
    QMessageBox msgBox(QMessageBox::Information, tr("提示"), msg, 0, this);
    msgBox.addButton(tr("确认"), QMessageBox::AcceptRole);
    msgBox.setModal(false);
    msgBox.exec();
}

bool MainWindow::normalDecision(QString msg){
    QMessageBox msgBox(QMessageBox::Information, tr("提示"), msg, 0, this);
    msgBox.addButton(tr("确认"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("取消"), QMessageBox::RejectRole);
    msgBox.setModal(false);
    if(msgBox.exec() == QMessageBox::AcceptRole){
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::createNewBook(){
    QString fileName = QFileDialog::getOpenFileName(this, NULL, NULL, "*.txt");
    if (fileName == NULL) return;
    if(bookmanager.addBook(fileName, QFileInfo(fileName).fileName().split("."+QFileInfo(fileName).suffix())[0]) < 0){
        normalInformation("该书已存在。");
    }
    else{
        addBookBtn(bookmanager.getBookName());
        rightPageStack->setCurrentWidget(bookMenu);
    }
}

void MainWindow::OpenImageConfigureWindow(){
    window = new ImageConfig(this);
    window->show();
}

void MainWindow::showAllUIs(){
    ui->bookName->setHidden(false);
    ui->dayOrNight->setHidden(false);
    ui->bookSelector->setHidden(false);
    ui->noteSelector->setHidden(false);
    ui->eraserUI->setHidden(false);
    ui->penUI->setHidden(false);
    ui->pageOffsetSetter->setHidden(false);
    ui->imageConfigure->setHidden(false);
}

void MainWindow::hideAllUIs(){
    ui->bookName->setHidden(true);
    ui->dayOrNight->setHidden(true);
    ui->bookSelector->setHidden(true);
    ui->noteSelector->setHidden(true);
    ui->eraserUI->setHidden(true);
    ui->penUI->setHidden(true);
    ui->pageOffsetSetter->setHidden(true);
    //ui->imageConfigure->setHidden(true);
}

void MainWindow::changeLightingMode(){
    isDayLighting = !isDayLighting;
    ui->dayOrNight->setChecked(!isDayLighting);
    if(isDayLighting){
        ui->leftPage->setStyleSheet(dayLightStyle);
        ui->rightPage->setStyleSheet(dayLightStyle);
        ui->leftUIBar->setStyleSheet(dayLightStyle);
        ui->rightUIBar->setStyleSheet(dayLightStyle);
        ui->bookName->setStyleSheet(dayLightStyle);
        ui->middlePadding->setStyleSheet(dayLightStyle);
        ui->middleUpPadding->setStyleSheet(dayLightStyle);
        QIcon icon = ui->imageConfigure->icon();
        icon.addPixmap(QPixmap(":/icons/imageConfigure.png"), QIcon::Normal);
        ui->imageConfigure->setIcon(icon);
        //book selector
        icon = ui->bookSelector->icon();
        icon.addPixmap(QPixmap(":/icons/books.png"), QIcon::Normal);
        ui->bookSelector->setIcon(icon);
        //note selector
        icon = ui->noteSelector->icon();
        icon.addPixmap(QPixmap(":/icons/notes.png"), QIcon::Normal);
        ui->noteSelector->setIcon(icon);
        //pen
        icon = ui->penUI->icon();
        icon.addPixmap(QPixmap(":/icons/pencil.png"), QIcon::Normal, QIcon::Off);
        icon.addPixmap(QPixmap(":/icons/pencil.png"), QIcon::Normal, QIcon::On);
        ui->penUI->setIcon(icon);
        //eraser
        icon = ui->eraserUI->icon();
        icon.addPixmap(QPixmap(":/icons/eraser.png"), QIcon::Normal, QIcon::Off);
        icon.addPixmap(QPixmap(":/icons/eraser.png"), QIcon::Normal, QIcon::On);
        ui->eraserUI->setIcon(icon);
        //page offset setter
        icon = ui->pageOffsetSetter->icon();
        icon.addPixmap(QPixmap(":/icons/offset.png"), QIcon::Normal);
        ui->pageOffsetSetter->setIcon(icon);
    }
    else{
        ui->leftPage->setStyleSheet(nightLightStyle);
        ui->rightPage->setStyleSheet(nightLightStyle);
        ui->leftUIBar->setStyleSheet(nightLightStyle);
        ui->rightUIBar->setStyleSheet(nightLightStyle);
        ui->bookName->setStyleSheet(nightLightStyle);
        ui->middlePadding->setStyleSheet(nightLightStyle);
        ui->middleUpPadding->setStyleSheet(nightLightStyle);

        QIcon icon = ui->imageConfigure->icon();
        icon.addPixmap(QPixmap(":/icons/imageConfigure-n.png"), QIcon::Normal);
        ui->imageConfigure->setIcon(icon);
        //book selector
        icon = ui->bookSelector->icon();
        icon.addPixmap(QPixmap(":/icons/books-n.png"), QIcon::Normal);
        ui->bookSelector->setIcon(icon);
        //note selector
        icon = ui->noteSelector->icon();
        icon.addPixmap(QPixmap(":/icons/notes-n.png"), QIcon::Normal);
        ui->noteSelector->setIcon(icon);
        //pen
        icon = ui->penUI->icon();
        icon.addPixmap(QPixmap(":/icons/pencil-n.png"), QIcon::Normal, QIcon::Off);
        icon.addPixmap(QPixmap(":/icons/pencil-n.png"), QIcon::Normal, QIcon::On);
        ui->penUI->setIcon(icon);
        //eraser
        icon = ui->eraserUI->icon();
        icon.addPixmap(QPixmap(":/icons/eraser-n.png"), QIcon::Normal, QIcon::Off);
        icon.addPixmap(QPixmap(":/icons/eraser-n.png"), QIcon::Normal, QIcon::On);
        ui->eraserUI->setIcon(icon);
        //page offset setter
        icon = ui->pageOffsetSetter->icon();
        icon.addPixmap(QPixmap(":/icons/offset-n.png"), QIcon::Normal);
        ui->pageOffsetSetter->setIcon(icon);
    }
}

void MainWindow::loadAllBookEntries(){
    std::vector<Book*> books = bookmanager.getAllBooks();
    if(books.size() == 0){
        rightPageStack->setCurrentWidget(emptybookpage);
        return;
    }
    for(Book* book : books){
        addBookBtn(book->getName());
    }
    rightPageStack->setCurrentWidget(bookMenu);
}

void MainWindow::loadAllNoteEntries(){
    std::vector<Note> notes = bookmanager.getAllNotes();
    if(notes.size() == 0){
        rightPageStack->setCurrentWidget(emptynotepage);
        return;
    }
    noteMenu->resetEntries();
    for(Note note : notes){
        addNoteBtn(note.getNoteName());
    }
    rightPageStack->setCurrentWidget(noteMenu);
}

void MainWindow::addBookBtn(QString bookName){
    QPushButton *btn = new QPushButton(this);
    btn->setText(bookName);
    btn->setStyleSheet("QPushButton{background-color: rgb(179, 208, 255); border-radius: 20px;  border: 1px rgb(179, 208, 255);}");
    btn->setMinimumHeight(40);
    btn->setMaximumHeight(40);
    btn->setFont(QFont("Microsoft YaHei", 16, 55));
    QObject::connect(btn, &QPushButton::clicked, this, &MainWindow::showBookInfoModal);
    bookMenu->addEntry(btn);
}

void MainWindow::addNoteBtn(QString noteName){
    QPushButton *btn = new QPushButton(this);
    btn->setText(noteName);
    btn->setStyleSheet("QPushButton{background-color: rgb(179, 208, 255); border-radius: 20px;  border: 1px rgb(179, 208, 255);}");
    btn->setMinimumHeight(40);
    btn->setMaximumHeight(40);
    btn->setFont(QFont("Microsoft YaHei", 16, 55));
    QObject::connect(btn, &QPushButton::clicked, this, &MainWindow::showNoteInfoModal);
    noteMenu->addEntry(btn);
}

void MainWindow::backToRead(){
    whitePanel->setHidden(true);
    currentActive->setHidden(true);
    if(currentActive == noteentryedit){
        if(noteMenu == 0){
            rightPageStack->setCurrentWidget(emptynotepage);
        }
    }
    currentActive = NULL;
    currentActiveName = "";
}

void MainWindow::leaveReading(QString name, QWidget *widget){
    whitePanel->setMinimumHeight(this->size().height());
    whitePanel->setMinimumWidth(this->size().width());
    whitePanel->setHidden(false);
    widget->setHidden(false);
    currentActive = widget;
    currentActiveName = name;
}

void MainWindow::selectBook(){
    autoSaveNote();
    leftPage->clearNote();
    rightPage->clearNote();
    bookmanager.switchBook(currentActiveName);
    leftPageNumPhysical = 0;
    backToRead();
    choosenotepage->setBookName(currentActiveName);
    leftPageStack->setCurrentWidget(choosenotepage);
    loadAllNoteEntries();
}

void MainWindow::selectNote(){
    bookmanager.selectNote(currentActiveName);
    backToRead();
    leftPageStack->setCurrentWidget(leftPage);
    rightPageStack->setCurrentWidget(rightPage);
    startReading();
}

void MainWindow::createNewNote(){
    if(noteMenu->getCount() == 0)
        rightPageStack->setCurrentWidget(noteMenu);
    QPushButton *btn = new QPushButton(this);
    btn->setStyleSheet("QPushButton{background-color: rgb(179, 208, 255); border-radius: 20px;  border: 1px rgb(179, 208, 255);}");
    btn->setMinimumHeight(40);
    btn->setMaximumHeight(40);
   // QRect rect = noteMenu->getNextGeometry(btn, this);
    if(noteMenu->getCount() % entryPerPage > (entryPerPage / 2)){
        noteentryeditupper->reset();
        leaveReading("", noteentryeditupper);
    }
    else{
        //noteentryedit->setGeometry(rect.x() - margin, rect.y() - margin, rect.width() + margin, rect.height());

        noteentryedit->reset();
        leaveReading("", noteentryedit);
    }
}

void MainWindow::addNote(){
    if(noteentryedit->getName() == ""){
        normalInformation("笔记名不得为空");
        return;
    }
    if(bookmanager.addNote(noteentryedit->getName(), noteentryedit->getIntroduction()) < 0)
        normalInformation("笔记已存在");
    else
       addNoteBtn(noteentryedit->getName());
    backToRead();
}

void MainWindow::addNoteUp(){
    if(noteentryeditupper->getName() == ""){
        normalInformation("笔记名不得为空");
        return;
    }
    if(bookmanager.addNote(noteentryeditupper->getName(), noteentryeditupper->getIntroduction()) < 0)
        normalInformation("笔记已存在");
    else
       addNoteBtn(noteentryedit->getName());
    backToRead();
}

void MainWindow::showBookInfoModal(){
    QPushButton *sender = (QPushButton *)this->sender();
    Book *book = bookmanager.getSingleBook(sender->text());
    if(bookMenu->isTopHalf(sender)){
        BookMetadata meta = book->getBookMetaData();
        bookentrymodal->setName(book->getName());
        bookentrymodal->setFont(QFont("Microsoft YaHei", 16, 55));
        bookentrymodal->setTime(meta.getLastReadTime());
        bookentrymodal->setPage(meta.getLastReadPage(), meta.getBookPageCount());
        bookentrymodal->setGeometry(sender->mapTo(this, sender->pos()).x() - margin, sender->mapTo(this, sender->pos()).y() -margin, sender->width() + margin, bookentrymodal->height());
        QString sample = bookmanager.fetchLastReadFromBook(book->getName(), meta.getLastReadPage());
        sample = sample.left(sampleNumber);
        sample += "......";
        bookentrymodal->setLastRead(sample);
        leaveReading(book->getName(), bookentrymodal);
    }
    else{
        BookMetadata meta = book->getBookMetaData();
        bookentryuppermodal->setName(book->getName());
        bookentryuppermodal->setTime(meta.getLastReadTime());
        bookentryuppermodal->setPage(meta.getLastReadPage(), meta.getBookPageCount());
        bookentrymodal->setGeometry(sender->mapTo(this, sender->pos()).x() - margin, sender->mapTo(this, sender->pos()).y() + bookentrymodal->height() - margin, sender->width() + margin, bookentrymodal->height());
        leaveReading(book->getName(), bookentryuppermodal);
    }
}

void MainWindow::showNoteInfoModal(){
    QPushButton *sender = (QPushButton *)this->sender();
    Note note = bookmanager.getSingleNote(sender->text());
    if(noteMenu->isTopHalf(sender)){
        noteentrymodal->setName(note.getNoteName());
        QString intro = note.getIntroduction();
        if(intro == "")
            intro = tr("None");
        noteentrymodal->setIntroduction(intro);
        noteentrymodal->setTime(note.getLastModifiedTime());
        bookentrymodal->setFont(QFont("Microsoft YaHei", 16, 55));

        noteentrymodal->setGeometry(sender->mapTo(this, sender->pos()).x() - margin, sender->mapTo(this, sender->pos()).y() - margin, sender->width() + margin, noteentrymodal->height());
        leaveReading(note.getNoteName(), noteentrymodal);
    }
    else{
        noteentryuppermodal->setName(note.getNoteName());
        noteentryuppermodal->setIntroduction(note.getIntroduction());
        noteentryuppermodal->setTime(note.getLastModifiedTime());
        noteentrymodal->setGeometry(sender->mapTo(this, sender->pos()).x() - margin, sender->mapTo(this, sender->pos()).y() + noteentrymodal->height() - margin, sender->width() + margin, noteentrymodal->height());
        leaveReading(note.getNoteName(), noteentryuppermodal);
    }
}

void MainWindow::backToSelectBook(){
    hideAllUIs();
    QDesktopWidget *desktop = QApplication::desktop();
    int screen_count = desktop->screenCount();
    if(screen_count > 1){
    this->showNormal();
    this->setGeometry(desktop->screenGeometry(1).x(), desktop->screenGeometry(1).y(), this->width(), this->height());
    this->showFullScreen();
    }
    bookmanager.closeBook();
    leftPageStack->setCurrentWidget(choosebookpage);
    rightPageStack->setCurrentWidget(bookMenu);
}

void MainWindow::backToSelectNote(){
    hideAllUIs();
    QDesktopWidget *desktop = QApplication::desktop();
    int screen_count = desktop->screenCount();
    if(screen_count > 1){
    this->showNormal();
    this->setGeometry(desktop->screenGeometry(1).x(), desktop->screenGeometry(1).y(), this->width(), this->height());
    this->showFullScreen();
    }
    leftPageStack->setCurrentWidget(choosenotepage);
    rightPageStack->setCurrentWidget(noteMenu);
}

void MainWindow::startReading(){
    //leftPage->setContent();
    showAllUIs();
    if(!isCalibration){
        isCalibration = 1;

        OpenImageConfigureWindow();
    }
    ui->bookName->setText(bookmanager.getBookName());
    int p = bookmanager.getLastRead();
    baseOffset = p;
    p += leftPageNumPhysical - 1;
    leftPage->setContent(bookmanager.getBookPageWithPageNumber(p), p, bookmanager.getPageCount());
    leftPage->setNote(bookmanager.getNotePageWithPageNumber(p));
    rightPage->setContent(bookmanager.getBookPageWithPageNumber(p+1), p+1, bookmanager.getPageCount());
    rightPage->setNote(bookmanager.getNotePageWithPageNumber(p+1));
    leftPageStack->setCurrentWidget(leftPage);
    rightPageStack->setCurrentWidget(rightPage);
    this->showNormal();
    QDesktopWidget *desktop = QApplication::desktop();
    int screen_count = desktop->screenCount();
    if(screen_count > 1){
        this->setGeometry(desktop->screenGeometry(0).x()+9, desktop->screenGeometry(0).y()+9, this->width(), this->height());
    }
    this->showFullScreen();
}

void MainWindow::turnToPageWithLeftPageNumber(int p){
    if(rightPageStack && rightPageStack->currentWidget() == rightPage){
        if(p <= 0 || p >bookmanager.getPageCount()){
           return;
        }
        std::cout<<"pageno: "<<p<<std::endl;
        if(leftPageNumPhysical == p)
            return;
        autoSaveNote();
        leftPageNumPhysical = p;
        int index = p - 1 + baseOffset;
        std::cout<<"gonna read index: "<<index<<std::endl;
        bookmanager.setLastRead(index);
        std::cout<<"left ok: "<<index<<std::endl;
        leftPage->setContent(bookmanager.getBookPageWithPageNumber(index), index, bookmanager.getPageCount());
        std::cout<<bookmanager.getBookPageWithPageNumber(index).toStdString()<<std::endl;
        std::cout<<"left ok: "<<index<<std::endl;
        leftPage->setNote(bookmanager.getNotePageWithPageNumber(index));
        std::cout<<"left ok: "<<index<<std::endl;

        rightPage->setContent(bookmanager.getBookPageWithPageNumber(index+1), index+1, bookmanager.getPageCount());
        rightPage->setNote(bookmanager.getNotePageWithPageNumber(index+1));
         std::cout<<"right ok: "<<index<<std::endl;
    }
}

void MainWindow::autoSaveNote(){
    int index = leftPageNumPhysical - 1 + baseOffset;
    if(index <= 0)
        return;
    std::cout<<"savewithindex: "<<index<<std::endl;
    QImage img = leftPage->getNote();
    if(!img.isNull())
        bookmanager.storeNotePage(img, index);
    img = rightPage->getNote();
    if(!img.isNull())
        bookmanager.storeNotePage(img, index + 1);
}

void MainWindow::usePen(){
    ui->penUI->setChecked(true);

    ui->eraserUI->setChecked(false);
    leftPage->setPainter(penColor, penWidth);
    rightPage->setPainter(penColor, penWidth);
}

void MainWindow::useEraser(){
    ui->eraserUI->setChecked(true);
     ui->penUI->setChecked(false);
    leftPage->setPainter(Qt::transparent, eraserWidth);
    rightPage->setPainter(Qt::transparent, eraserWidth);
}

void MainWindow::simulateClick(int x, int y){
   std::cout<<"tryclick x: "<<x<<"y: "<<y<<std::endl;
    QPoint pos;
    x += sidePaddingWidth;
    pos.setY(y - qzxingSideLength);
    QMouseEvent *mEvnPress;
    QMouseEvent *mEvnRelease;
    QDesktopWidget *desktop = QApplication::desktop();
    int width = desktop->screenGeometry(1).width();
    int pageWidth = (width - middlePaddingWidth - sidePaddingWidth * 2) / 2;
    std::cout<<"width"<<width<<"pagewidth"<<pageWidth<<std::endl;
    if(x > sidePaddingWidth && x < sidePaddingWidth + pageWidth){
        x -= sidePaddingWidth;
        pos.setX(x );
        mEvnPress = new QMouseEvent(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(leftPage, mEvnPress);
        mEvnRelease = new QMouseEvent(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(leftPage, mEvnRelease);
    }
    else if(x > width - (sidePaddingWidth + pageWidth) && x < width - sidePaddingWidth){
        x -= width - (sidePaddingWidth + pageWidth);
        pos.setX(x );
        mEvnPress = new QMouseEvent(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(rightPage, mEvnPress);
        mEvnRelease = new QMouseEvent(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(rightPage, mEvnRelease);
    }
   // std::cout<<QWidget::focusWidget()->mapToGlobal(QPoint(0,0)).x()<<std::endl;


}

void MainWindow::simulateFly(){
    leftPage->cleanDotHistory();
    rightPage->cleanDotHistory();
}
