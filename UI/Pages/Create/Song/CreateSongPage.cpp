#include "CreateSongPage.h"
#include <QHBoxLayout>
#include <QFileInfo>
#include <QDate>

#include "../../../../Services/AuthenticationService/AuthenticationService.h"

CreateSongPage::CreateSongPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void CreateSongPage::setupUI() {
    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(200, 200);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));

    changeCoverButton = new QPushButton("Change Cover", this);

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Title");

    genreEdit = new QLineEdit(this);
    genreEdit->setPlaceholderText("Genre");

    releaseYearSpin = new QSpinBox(this);
    releaseYearSpin->setRange(1900, QDate::currentDate().year());
    releaseYearSpin->setValue(QDate::currentDate().year());

    albumCombo = new QComboBox(this);
    albumCombo->addItem("--None--", 0);

    audioFileLabel = new QLabel("No file selected", this);

    browseAudioButton = new QPushButton("Browse Audio", this);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    createButton = new QPushButton("Create", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *audioLayout = new QHBoxLayout;
    audioLayout->addWidget(audioFileLabel);
    audioLayout->addWidget(browseAudioButton);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(createButton);
    buttonsLayout->addWidget(cancelButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(coverLabel, 0, Qt::AlignCenter);
    layout->addWidget(changeCoverButton, 0, Qt::AlignCenter);

    layout->addWidget(titleEdit);
    layout->addWidget(genreEdit);
    layout->addWidget(releaseYearSpin);
    layout->addWidget(albumCombo);

    layout->addLayout(audioLayout);

    layout->addWidget(errorLabel);

    layout->addLayout(buttonsLayout);
    layout->addStretch();
}


void CreateSongPage::setupConnections() {
    connect(changeCoverButton, &QPushButton::clicked, this, &CreateSongPage::changeCoverRequested);
    connect(browseAudioButton, &QPushButton::clicked, this, &CreateSongPage::browseAudioRequested);
    connect(createButton, &QPushButton::clicked, this, [this]() {
        clearError();
        if (!isValidFields()) return;

        emit createRequested();
    });
    connect(cancelButton, &QPushButton::clicked, this, &CreateSongPage::cancelRequested);
}


Song CreateSongPage::song() const {
    Song song;

    song.setTitle(titleEdit->text().trimmed());
    song.setGenre(genreEdit->text().trimmed());

    song.setReleaseYear(releaseYearSpin->value());

    song.setAlbumID(albumCombo->currentData().toInt());
    song.setArtistID(AuthenticationService::instance().currentArtist()->getID());

    song.setCoverPicture(coverPicture);
    song.setAudioFilePath(audioFilePath);

    return song;
}


void CreateSongPage::setAlbums(const QVector<Album> &albums) {
    albumCombo->clear();

    albumCombo->addItem("--None--", 0);

    for (const auto &album: albums)
        albumCombo->addItem(album.getTitle(), album.getID());

    albumCombo->setCurrentIndex(0);
}


void CreateSongPage::setCoverPicture(const QByteArray &cover) {
    coverPicture = cover;
    coverLabel->setPixmap(getCover(coverPicture));
}


void CreateSongPage::setAudioFile(const QString &path) {
    audioFilePath = path;
    audioFileLabel->setText(path.isEmpty() ? "No file selected" : QFileInfo(path).fileName());
}


void CreateSongPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void CreateSongPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}


QPixmap CreateSongPage::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}


bool CreateSongPage::isValidFields() {
    if (titleEdit->text().trimmed().isEmpty()) {
        setError("Title cannot be empty.");
        return false;
    }

    if (genreEdit->text().trimmed().isEmpty()) {
        setError("Genre cannot be empty.");
        return false;
    }

    if (audioFilePath.isEmpty()) {
        setError("Please select an audio file.");
        return false;
    }

    return true;
}


void CreateSongPage::clearFields() {
    titleEdit->clear();
    genreEdit->clear();

    releaseYearSpin->setValue(QDate::currentDate().year());

    albumCombo->setCurrentIndex(0);

    coverPicture.clear();
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));

    audioFilePath.clear();
    audioFileLabel->setText("No file selected");

    clearError();
}
