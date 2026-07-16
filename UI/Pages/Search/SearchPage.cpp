#include "SearchPage.h"
#include <QMenu>

SearchPage::SearchPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupMenus();
}


void SearchPage::setupUI() {
    sortButton = new QToolButton(this);
    sortButton->setText("Sort");

    filterButton = new QToolButton(this);
    filterButton->setText("Filter");

    songsList = new CardList<SongCard, Song>("Songs", this);
    albumsList = new CardList<AlbumCard, Album>("Albums", this);
    artistsList = new CardList<ArtistCard, Artist>("Artists", this);

    auto *toolsLayout = new QHBoxLayout;
    toolsLayout->addWidget(filterButton);
    toolsLayout->addWidget(sortButton);
    toolsLayout->addStretch();

    auto *layout = new QVBoxLayout(this);

    layout->addLayout(toolsLayout);

    layout->addWidget(songsList);
    layout->addWidget(albumsList);
    layout->addWidget(artistsList);
}


void SearchPage::setupMenus() {
    auto *sortMenu = new QMenu(this);

    auto *titleAsc = sortMenu->addAction("Title ↑");
    auto *titleDesc = sortMenu->addAction("Title ↓");
    auto *yearAsc = sortMenu->addAction("Release Year ↑");
    auto *yearDesc = sortMenu->addAction("Release Year ↓");

    connect(titleAsc, &QAction::triggered, this, [this] {
        emit sortSongsRequested(SongSort::Title, SortOrder::Ascending);
    });
    connect(titleDesc, &QAction::triggered, this, [this] {
        emit sortSongsRequested(SongSort::Title, SortOrder::Descending);
    });
    connect(yearAsc, &QAction::triggered, this, [this] {
        emit sortSongsRequested(SongSort::ReleaseYear, SortOrder::Ascending);
    });
    connect(yearDesc, &QAction::triggered, this, [this] {
        emit sortSongsRequested(SongSort::ReleaseYear, SortOrder::Descending);
    });

    sortButton->setMenu(sortMenu);
    sortButton->setPopupMode(QToolButton::InstantPopup);


    auto *filterMenu = new QMenu(this);

    filterMenu->addAction("Coming soon");

    filterButton->setMenu(filterMenu);
    filterButton->setPopupMode(QToolButton::InstantPopup);
}


void SearchPage::setAlbums(const QVector<Album> &albums) {
    albumsList->setItems(albums);
}


void SearchPage::setArtists(const QVector<Artist> &artists) {
    artistsList->setItems(artists);
}


void SearchPage::setSongs(const QVector<Song> &songs) {
    songsList->setItems(songs);
}
