#include "EditAlbumPage.h"
#include <QHBoxLayout>

EditAlbumPage::EditAlbumPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void EditAlbumPage::setupUI() {
    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(200, 200);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));

    changeCoverButton = new QPushButton("Change Cover", this);

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Title");

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(coverLabel, 0, Qt::AlignCenter);
    layout->addWidget(changeCoverButton, 0, Qt::AlignCenter);

    layout->addWidget(titleEdit);
    layout->addWidget(errorLabel);

    layout->addLayout(buttonsLayout);
    layout->addStretch();
}


void EditAlbumPage::setupConnections() {
    connect(changeCoverButton, &QPushButton::clicked, this, &EditAlbumPage::changeCoverRequested);
    connect(saveButton, &QPushButton::clicked, this, [this] {
        clearError();
        if (!isValidFields()) return;

        emit saveRequested();
    });
    connect(cancelButton, &QPushButton::clicked, this, &EditAlbumPage::cancelRequested);
}


void EditAlbumPage::setAlbum(const Album &album) {
    clearError();

    coverPicture = album.getCoverPicture();
    coverLabel->setPixmap(getCover(coverPicture));

    titleEdit->setText(album.getTitle());
}


bool EditAlbumPage::isValidFields() {
    if (titleEdit->text().trimmed().isEmpty()) {
        setError("Title cannot be empty.");
        return false;
    }

    return true;
}


QPixmap EditAlbumPage::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}


void EditAlbumPage::setCoverPicture(const QByteArray &cover) {
    coverPicture = cover;
    coverLabel->setPixmap(getCover(coverPicture));
}


void EditAlbumPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void EditAlbumPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}
