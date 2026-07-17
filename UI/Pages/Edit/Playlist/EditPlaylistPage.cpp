#include "EditPlaylistPage.h"
#include <QAbstractItemView>
#include <QHBoxLayout>
#include "../../../../Repositories/SongRepository/SongRepository.h"

EditPlaylistPage::EditPlaylistPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void EditPlaylistPage::setupUI() {
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Title");

    songsLabel = new QLabel("Select Songs", this);

    songsList = new QListWidget(this);
    songsList->setSelectionMode(QAbstractItemView::MultiSelection);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(titleEdit);
    layout->addWidget(songsLabel);
    layout->addWidget(songsList);

    layout->addWidget(errorLabel);

    layout->addLayout(buttonsLayout);
    layout->addStretch();
}


void EditPlaylistPage::setupConnections() {
    connect(saveButton, &QPushButton::clicked, this, [this] {
        clearError();
        if (!isValidFields()) return;

        emit saveRequested();
    });
    connect(cancelButton, &QPushButton::clicked, this, &EditPlaylistPage::cancelRequested);
}


void EditPlaylistPage::setPlaylist(const Playlist &playlist) {
    currentPlaylist = playlist;

    clearError();

    titleEdit->setText(playlist.getTitle());

    QVector<Song> playlistSongs = SongRepository::instance().getByPlaylist(playlist.getID());
    QSet<int> playlistSongIDs;
    for (const auto &song: playlistSongs)
        playlistSongIDs.insert(song.getID());

    for (int i = 0; i < songsList->count(); ++i) {
        auto *item = songsList->item(i);
        int songID = item->data(Qt::UserRole).toInt();

        item->setSelected(playlistSongIDs.contains(songID));
    }
}


Playlist EditPlaylistPage::playlist() const {
    if (!currentPlaylist) throw std::runtime_error("Want playlist but it's empty");
    Playlist playlist = *currentPlaylist;

    playlist.setTitle(titleEdit->text().trimmed());

    return playlist;
}


void EditPlaylistPage::setSongs(const QVector<Song> &songs) {
    songsList->clear();

    for (const auto &song: songs) {
        auto *item = new QListWidgetItem(song.getTitle());
        item->setData(Qt::UserRole, song.getID());

        songsList->addItem(item);
    }
}


QVector<int> EditPlaylistPage::selectedSongIDs() const {
    QVector<int> ids;

    for (int i = 0; i < songsList->count(); i++) {
        auto *item = songsList->item(i);

        if (item->isSelected())
            ids.append(item->data(Qt::UserRole).toInt());
    }

    return ids;
}


void EditPlaylistPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void EditPlaylistPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}


bool EditPlaylistPage::isValidFields() {
    if (titleEdit->text().trimmed().isEmpty()) {
        setError("Title cannot be empty.");
        return false;
    }

    if (selectedSongIDs().isEmpty()) {
        setError("Please select at least one song.");
        return false;
    }

    return true;
}


void EditPlaylistPage::clearFields() {
    currentPlaylist.reset();
    titleEdit->clear();

    for (int i = 0; i < songsList->count(); i++)
        songsList->item(i)->setSelected(false);

    clearError();
}
