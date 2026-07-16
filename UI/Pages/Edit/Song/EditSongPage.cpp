#include "EditSongPage.h"
#include <QHBoxLayout>
#include <QFileInfo>
#include <QDate>

EditSongPage::EditSongPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void EditSongPage::setupUI() {
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

    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *audioLayout = new QHBoxLayout;
    audioLayout->addWidget(audioFileLabel);
    audioLayout->addWidget(browseAudioButton);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(saveButton);
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


void EditSongPage::setupConnections() {
    connect(changeCoverButton, &QPushButton::clicked, this, &EditSongPage::changeCoverRequested);
    connect(browseAudioButton, &QPushButton::clicked, this, &EditSongPage::browseAudioRequested);
    connect(saveButton, &QPushButton::clicked, this, [this]() {
        clearError();
        if (!isValidFields()) return;

        emit saveRequested();
    });
    connect(cancelButton, &QPushButton::clicked, this, &EditSongPage::cancelRequested);
}


void EditSongPage::setSong(const Song &song) {
    clearError();

    coverPicture = song.getCoverPicture();
    coverLabel->setPixmap(getCover(coverPicture));

    titleEdit->setText(song.getTitle());
    genreEdit->setText(song.getGenre());

    releaseYearSpin->setValue(song.getReleaseYear());

    int index = albumCombo->findData(song.getAlbumID());
    albumCombo->setCurrentIndex(index != -1 ? index : 0);

    setAudioFile(song.getAudioFilePath());
}


void EditSongPage::setAlbums(const QVector<Album> &albums) {
    albumCombo->clear();

    albumCombo->addItem("--None--", 0);

    for (const auto &album: albums)
        albumCombo->addItem(album.getTitle(), album.getID());
}


void EditSongPage::setCoverPicture(const QByteArray &cover) {
    coverPicture = cover;
    coverLabel->setPixmap(getCover(coverPicture));
}


void EditSongPage::setAudioFile(const QString &path) {
    audioFilePath = path;
    audioFileLabel->setText(path.isEmpty() ? "No file selected" : QFileInfo(path).fileName());
}


void EditSongPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void EditSongPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}


QPixmap EditSongPage::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}


bool EditSongPage::isValidFields() {
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
