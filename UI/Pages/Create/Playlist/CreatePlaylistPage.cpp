#include "CreatePlaylistPage.h"
#include <QAbstractItemView>
#include <QHBoxLayout>

CreatePlaylistPage::CreatePlaylistPage(QWidget *parent): QWidget(parent) {
    setupUI();
    setupConnections();
}


void CreatePlaylistPage::setupUI() {
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Title");

    songsLabel = new QLabel("Select Songs", this);

    songsList = new QListWidget(this);
    songsList->setSelectionMode(QAbstractItemView::MultiSelection);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    createButton = new QPushButton("Create", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(createButton);
    buttonsLayout->addWidget(cancelButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(titleEdit);
    layout->addWidget(songsLabel);
    layout->addWidget(songsList);

    layout->addWidget(errorLabel);

    layout->addLayout(buttonsLayout);
    layout->addStretch();
}


void CreatePlaylistPage::setupConnections() {
    connect(createButton, &QPushButton::clicked, this, [this] {
        clearError();
        if (!isValidFields()) return;

        emit createRequested();
    });
    connect(cancelButton, &QPushButton::clicked,this, &CreatePlaylistPage::cancelRequested);
}


void CreatePlaylistPage::setSongs(const QVector<Song> &songs) {
    songsList->clear();

    for (const auto &song: songs) {
        auto *item = new QListWidgetItem(song.getTitle());
        item->setData(Qt::UserRole, song.getID());

        songsList->addItem(item);
    }
}


QVector<int> CreatePlaylistPage::selectedSongIDs() const {
    QVector<int> ids;

    for (int i = 0; i < songsList->count(); i++) {
        auto *item = songsList->item(i);

        if (item->isSelected())
            ids.append(item->data(Qt::UserRole).toInt());
    }

    return ids;
}


void CreatePlaylistPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void CreatePlaylistPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}


bool CreatePlaylistPage::isValidFields() {
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
