#include "CreateAlbumPage.h"
#include <QDate>
#include <QHBoxLayout>

CreateAlbumPage::CreateAlbumPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void CreateAlbumPage::setupUI() {
    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(200, 200);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));

    changeCoverButton = new QPushButton("Change Cover", this);

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Title");

    releaseYearSpin = new QSpinBox(this);
    releaseYearSpin->setRange(1900, QDate::currentDate().year());
    releaseYearSpin->setValue(QDate::currentDate().year());

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    createButton = new QPushButton("Create", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(createButton);
    buttonsLayout->addWidget(cancelButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(coverLabel, 0, Qt::AlignCenter);
    layout->addWidget(changeCoverButton, 0, Qt::AlignCenter);

    layout->addWidget(titleEdit);
    layout->addWidget(releaseYearSpin);
    layout->addWidget(errorLabel);

    layout->addLayout(buttonsLayout);
    layout->addStretch();
}


void CreateAlbumPage::setupConnections() {
    connect(changeCoverButton, &QPushButton::clicked, this, &CreateAlbumPage::changeCoverRequested);
    connect(createButton, &QPushButton::clicked, this, [this] {
        clearError();
        if (!isValidFields()) return;

        emit createRequested();
    });
    connect(cancelButton, &QPushButton::clicked, this, &CreateAlbumPage::cancelRequested);
}


bool CreateAlbumPage::isValidFields() {
    if (titleEdit->text().trimmed().isEmpty()) {
        setError("Title cannot be empty.");
        return false;
    }

    return true;
}


QPixmap CreateAlbumPage::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}


void CreateAlbumPage::setCoverPicture(const QByteArray &cover) {
    coverPicture = cover;
    coverLabel->setPixmap(getCover(coverPicture));
}


void CreateAlbumPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void CreateAlbumPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}
