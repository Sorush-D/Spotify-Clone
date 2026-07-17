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
        songs = BrowseService::instance().sortSongs(songs, SongSort::Title, SortOrder::Ascending);
        albums = BrowseService::instance().sortAlbums(albums, SortOrder::Ascending);
        setSongs(songs);
        setAlbums(albums);
    });
    connect(titleDesc, &QAction::triggered, this, [this] {
        songs = BrowseService::instance().sortSongs(songs,SongSort::Title, SortOrder::Descending);
        albums = BrowseService::instance().sortAlbums(albums, SortOrder::Descending);
        setSongs(songs);
        setAlbums(albums);
    });
    connect(yearAsc, &QAction::triggered, this, [this] {
        songs = BrowseService::instance().sortSongs(songs,SongSort::ReleaseYear, SortOrder::Ascending);
        setSongs(songs);
    });
    connect(yearDesc, &QAction::triggered, this, [this] {
        songs = BrowseService::instance().sortSongs(songs,SongSort::ReleaseYear, SortOrder::Descending);
        setSongs(songs);
    });

    sortButton->setMenu(sortMenu);
    sortButton->setPopupMode(QToolButton::InstantPopup);


    auto *filterMenu = new QMenu(this);

    filterMenu->addAction("Coming soon");

    filterButton->setMenu(filterMenu);
    filterButton->setPopupMode(QToolButton::InstantPopup);
}


void SearchPage::setAlbums(const QVector<Album> &newAlbums) {
    albums = newAlbums;
    albumsList->setItems(albums);

    const auto cards = findChildren<AlbumCard *>();
    for (auto *card: cards)
        connect(card, &AlbumCard::clicked, this, &SearchPage::albumClicked);
}


void SearchPage::setArtists(const QVector<Artist> &newArtists) {
    artists = newArtists;
    artistsList->setItems(artists);

    const auto cards = findChildren<ArtistCard *>();
    for (auto *card: cards)
        connect(card, &ArtistCard::clicked, this, &SearchPage::artistClicked);
}


void SearchPage::setSongs(const QVector<Song> &newSongs) {
    songs = newSongs;
    songsList->setItems(songs);

    const auto cards = findChildren<SongCard *>();
    for (auto *card: cards) {
        connect(card, &SongCard::clicked, this, &SearchPage::songClicked);
        connect(card, &SongCard::playRequested, this, &SearchPage::songPlayRequested);
        connect(card, &SongCard::likeRequested, this, &SearchPage::songLikeRequested);
    }
}
