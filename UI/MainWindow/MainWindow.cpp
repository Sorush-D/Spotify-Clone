#include "MainWindow.h"
#include "../../Repositories/ArtistRepository/ArtistRepository.h"
#include "../../Repositories/SongRepository/SongRepository.h"
#include "../../Services/ArtistService/ArtistService.h"
#include "../../Services/AuthenticationService/AuthenticationService.h"
#include "../../Services/ListenerService/ListenerService.h"
#include "../../Services/SearchService/SearchService.h"
#include "../Pages/Album/AlbumPage.h"
#include "../Pages/Home/HomePage.h"
#include "../Pages/Artist/ArtistPage.h"
#include "../Pages/Create/Album/CreateAlbumPage.h"
#include "../Pages/Create/Playlist/CreatePlaylistPage.h"
#include "../Pages/Create/Song/CreateSongPage.h"
#include "../Pages/Edit/Album/EditAlbumPage.h"
#include "../Pages/Edit/Playlist/EditPlaylistPage.h"
#include "../Pages/Edit/Song/EditSongPage.h"
#include "../Pages/Songs/SongsPage.h"
#include "../Pages/Login/LoginPage.h"
#include "../Pages/PlayList/PlaylistPage.h"
#include "../Pages/Profile/ProfilePage.h"
#include "../Pages/ProfileEdit/ProfileEditPage.h"
#include "../Pages/Register/RegisterPage.h"
#include "../Pages/Search/SearchPage.h"
#include "../../Repositories/AlbumRepository/AlbumRepository.h"
#include "../../Repositories/ListenerRepository/ListenerRepository.h"
#include "../../Repositories/PlaylistRepository/PlaylistRepository.h"
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupPages();
    switchPage(Page::Home);
    setupConnections();
}


void MainWindow::setupUI() {
    topBar = new TopBar;
    sideBar = new SideBar;
    playerBar = new PlayerBar;

    contentStack = new QStackedWidget;

    auto *central = new QWidget(this);
    setCentralWidget(central);

    auto layoutBody = new QHBoxLayout;
    layoutBody->addWidget(sideBar);
    layoutBody->addWidget(contentStack);

    auto layoutMain = new QVBoxLayout(central);
    layoutMain->addWidget(topBar);
    layoutMain->addLayout(layoutBody);
    layoutMain->addWidget(playerBar);
}


void MainWindow::setupPages() {
    loginPage = new LoginPage;
    registerPage = new RegisterPage;
    contentStack->addWidget(loginPage);
    contentStack->addWidget(registerPage);

    homePage = new HomePage;
    searchPage = new SearchPage;
    contentStack->addWidget(homePage);
    contentStack->addWidget(searchPage);

    playlistPage = new PlaylistPage;
    albumPage = new AlbumPage;
    songsPage = new SongsPage;
    contentStack->addWidget(playlistPage);
    contentStack->addWidget(albumPage);
    contentStack->addWidget(songsPage);

    profilePage = new ProfilePage;
    profileEditPage = new ProfileEditPage;
    contentStack->addWidget(profilePage);
    contentStack->addWidget(profileEditPage);

    artistProfilePage = new ArtistPage;
    contentStack->addWidget(artistProfilePage);

    createAlbumPage = new CreateAlbumPage;
    editAlbumPage = new EditAlbumPage;
    contentStack->addWidget(createAlbumPage);
    contentStack->addWidget(editAlbumPage);

    createPlaylistPage = new CreatePlaylistPage;
    editPlaylistPage = new EditPlaylistPage;
    contentStack->addWidget(createPlaylistPage);
    contentStack->addWidget(editPlaylistPage);

    createSongPage = new CreateSongPage;
    editSongPage = new EditSongPage;
    contentStack->addWidget(createSongPage);
    contentStack->addWidget(editSongPage);
}


void MainWindow::setupConnections() {
    setupTopBarConnections();
    setupSideBarConnections();
    setupPlayerBarConnections();

    setupLoginPageConnections();
    setupRegisterPageConnections();

    setupHomePageConnections();
    setupSearchPageConnections();

    setupPlaylistPageConnections();
    setupAlbumPageConnections();
    setupSongsPageConnections();

    setupProfilePageConnections();
    setupProfileEditPageConnections();

    setupArtistProfileConnections();

    setupCreateAlbumConnections();
    setupEditAlbumConnections();

    setupCreatePlaylistConnections();
    setupEditPlaylistConnections();

    setupCreateSongConnections();
    setupEditSongConnections();

    switchPage(Page::Home);
}


void MainWindow::switchPage(Page page) {
    contentStack->setCurrentIndex(static_cast<int>(page));
}


void MainWindow::setupTopBarConnections() {
    connect(topBar, &TopBar::homeClicked, this, [this] {
        homePage->setSongs(SearchService::instance().searchSongs(""));
        homePage->setAlbums(SearchService::instance().searchAlbums(""));
        homePage->setArtists(SearchService::instance().searchArtists(""));
        switchPage(Page::Home);
    });

    connect(topBar, &TopBar::searchRequested, this, [this](const QString &text) {
        searchPage->setSongs(SearchService::instance().searchSongs(text));
        searchPage->setAlbums(SearchService::instance().searchAlbums(text));
        searchPage->setArtists(SearchService::instance().searchArtists(text));
        switchPage(Page::Search);
    });

    connect(topBar, &TopBar::loginClicked, this, [this] { switchPage(Page::Login); });
    connect(topBar, &TopBar::registerClicked, this, [this] { switchPage(Page::Register); });

    connect(topBar, &TopBar::profileClicked, this, [this] {
        switchPage(Page::Profile);

        auto &auth = AuthenticationService::instance();
        if (auth.currentArtist())
            profilePage->setArtist(auth.currentArtist().value());
        else if (auth.currentListener())
            profilePage->setListener(auth.currentListener().value());
    });

    connect(topBar, &TopBar::editProfileClicked, this, [this] {
        switchPage(Page::ProfileEdit);

        auto &auth = AuthenticationService::instance();
        if (auth.currentArtist())
            profileEditPage->setArtist(auth.currentArtist().value());
        else if (auth.currentListener())
            profileEditPage->setListener(auth.currentListener().value());
    });

    connect(topBar, &TopBar::logoutClicked, this, [this] {
        AuthenticationService::instance().logout();

        topBar->refreshUserState();
        sideBar->refreshUserState();
        playerBar->refresh();

        switchPage(Page::Login);
    });
}


void MainWindow::setupSideBarConnections() {
    connect(sideBar, &SideBar::likedSongsClicked, this, [this] {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::LikedSongs,
            ListenerService::instance().favoriteSongs()
        );
    });

    connect(sideBar, &SideBar::playlistsClicked, this, [this] {
        switchPage(Page::Playlist);
        playlistPage->setPlaylists(ListenerService::instance().playlists());
        playlistPage->showEDButtons();
    });

    connect(sideBar, &SideBar::mySongsClicked, this, [this] {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::MySongs,
            ArtistService::instance().mySongs()
        );
    });

    connect(sideBar, &SideBar::mySinglesClicked, this, [this] {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::MySingles,
            ArtistService::instance().mySingleSongs()
        );
    });

    connect(sideBar, &SideBar::myAlbumsClicked, this, [this] {
        switchPage(Page::Album);
        albumPage->setAlbums(ArtistService::instance().myAlbums());
        albumPage->showEDButtons();
    });

    connect(sideBar, &SideBar::createSongClicked, this, [this] {
        createSongPage->setAlbums(ArtistService::instance().myAlbums());
        switchPage(Page::CreateSong);
    });

    connect(sideBar, &SideBar::createAlbumClicked, this, [this] { switchPage(Page::CreateAlbum); });

    connect(sideBar, &SideBar::createPlaylistClicked, this, [this] {
        createPlaylistPage->setSongs(SearchService::instance().searchSongs(""));
        switchPage(Page::CreatePlaylist);
    });
}


void MainWindow::setupPlayerBarConnections() {
    connect(playerBar, &PlayerBar::previousClicked, [] { PlayerService::instance().previous(); });
    connect(playerBar, &PlayerBar::nextClicked, [] { PlayerService::instance().next(); });
    connect(playerBar, &PlayerBar::shuffleClicked, [] { PlayerService::instance().shuffle(); });
    connect(playerBar, &PlayerBar::loopClicked, [] { PlayerService::instance().cycleLoopCondition(); });
    connect(playerBar, &PlayerBar::likeClicked, [] { PlayerService::instance().toggleLike(); });
    connect(playerBar, &PlayerBar::positionChanged, [](qint64 pos) { PlayerService::instance().seek(pos); });
    connect(playerBar, &PlayerBar::volumeChanged, [](float volume) { PlayerService::instance().setVolume(volume); });

    connect(playerBar, &PlayerBar::playPauseClicked, [] {
        auto &player = PlayerService::instance();

        if (player.isPlaying())
            player.pause();
        else
            player.resume();
    });


    auto &player = PlayerService::instance();

    connect(&player, &PlayerService::currentSongChanged, playerBar, &PlayerBar::setSong);
    connect(&player, &PlayerService::likeChanged, playerBar, &PlayerBar::setLiked);
    connect(&player, &PlayerService::muteChanged, playerBar, &PlayerBar::setMute);
    connect(&player, &PlayerService::volumeChanged, playerBar, &PlayerBar::setVolume);
    connect(&player, &PlayerService::positionChanged, playerBar, &PlayerBar::setPosition);
    connect(&player, &PlayerService::durationChanged, playerBar, &PlayerBar::setDuration);
    connect(&player, &PlayerService::loopConditionChanged, playerBar, &PlayerBar::setLoopMode);

    connect(&player, &PlayerService::playbackStateChanged, playerBar, [this](QMediaPlayer::PlaybackState state) {
        playerBar->setPlaying(state == QMediaPlayer::PlayingState);
    });
}


void MainWindow::setupLoginPageConnections() {
    connect(loginPage, &LoginPage::signupRequested, this, [this] { switchPage(Page::Register); });

    connect(loginPage, &LoginPage::loginRequested, this, [this](const QString &username, const QString &password) {
        if (!AuthenticationService::instance().login(username, password)) {
            loginPage->setError("Invalid username or password.");
            return;
        }

        loginPage->clearFields();

        topBar->refreshUserState();
        sideBar->refreshUserState();
        playerBar->refresh();

        switchPage(Page::Home);
    });
}


void MainWindow::setupRegisterPageConnections() {
    connect(registerPage, &RegisterPage::loginPageRequested, this, [this] { switchPage(Page::Login); });

    connect(registerPage, &RegisterPage::signupRequested, this, [this](
        Role role,
        const QString &fullName,
        const QString &username,
        const QString &password
    ) {
                bool success = false;

                if (role == Role::Artist) {
                    Artist artist;
                    artist.setFullName(fullName);
                    artist.setUserName(username);
                    artist.setPassword(password);

                    success = AuthenticationService::instance().registerArtist(artist);
                } else {
                    Listener listener;
                    listener.setFullName(fullName);
                    listener.setUserName(username);
                    listener.setPassword(password);

                    success = AuthenticationService::instance().registerListener(listener);
                }

                if (!success) {
                    registerPage->setError("Username already exists.");
                    return;
                }

                registerPage->clearFields();
                switchPage(Page::Login);
            }
    );
}


void MainWindow::setupHomePageConnections() {
    connect(homePage, &HomePage::albumClicked, this, [this](int albumId) {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::AlbumSongs,
            SongRepository::instance().getByAlbum(albumId)
        );
    });

    connect(homePage, &HomePage::artistClicked, this, [this](int artistId) {
        std::optional<Artist> artist = ArtistRepository::instance().search(artistId);
        if (!artist.has_value()) return;

        artistProfilePage->setArtist(artist.value());
        artistProfilePage->setSongs(ArtistService::instance().songs(artistId));
        artistProfilePage->setAlbums(ArtistService::instance().albums(artistId));
        switchPage(Page::ArtistProfile);
    });

    connect(homePage, &HomePage::songClicked, this, [](int songId) {
        //todo song page
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(homePage, &HomePage::songPlayRequested, this, [](int songId) {
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(homePage, &HomePage::songLikeRequested, this, [](int songId) {
        ListenerService::instance().toggleLike(songId);
    });
}


void MainWindow::setupSearchPageConnections() {
    connect(searchPage, &SearchPage::albumClicked, this, [this](int albumId) {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::AlbumSongs,
            SongRepository::instance().getByAlbum(albumId)
        );
    });

    connect(searchPage, &SearchPage::artistClicked, this, [this](int artistId) {
        std::optional<Artist> artist = ArtistRepository::instance().search(artistId);
        if (!artist.has_value()) return;

        artistProfilePage->setArtist(artist.value());
        artistProfilePage->setSongs(ArtistService::instance().songs(artistId));
        artistProfilePage->setAlbums(ArtistService::instance().albums(artistId));
        switchPage(Page::ArtistProfile);
    });

    connect(searchPage, &SearchPage::songClicked, this, [](int songId) {
        //todo song page
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(searchPage, &SearchPage::songPlayRequested, this, [](int songId) {
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(searchPage, &SearchPage::songLikeRequested, this, [](int songId) {
        ListenerService::instance().toggleLike(songId);
    });
}


void MainWindow::setupPlaylistPageConnections() {
    connect(playlistPage, &PlaylistPage::playlistClicked, this, [this](int playlistId) {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::PlaylistSongs,
            SongRepository::instance().getByPlaylist(playlistId)
        );
    });

    connect(playlistPage, &PlaylistPage::playlistEditRequested, this, [this](int playlistId) {
        auto playlist = PlaylistRepository::instance().search(playlistId);
        if (!playlist.has_value()) return;

        editPlaylistPage->setSongs(SearchService::instance().searchSongs(""));
        editPlaylistPage->setPlaylist(playlist.value());
        switchPage(Page::EditPlaylist);
    });

    connect(playlistPage, &PlaylistPage::playlistDeleteRequested, this, [this](int playlistId) {
        if (QMessageBox::question(
                this,
                "Delete Playlist",
                "Are you sure you want to delete this playlist?"
            ) != QMessageBox::Yes)
            return;

        PlaylistRepository::instance().remove(playlistId);
        playlistPage->setPlaylists(ListenerService::instance().playlists());
        playlistPage->showEDButtons();
    });
}


void MainWindow::setupAlbumPageConnections() {
    connect(albumPage, &AlbumPage::albumClicked, this, [this](int albumId) {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::AlbumSongs,
            SongRepository::instance().getByAlbum(albumId)
        );
    });

    connect(albumPage, &AlbumPage::albumEditRequested, this, [this](int albumId) {
        auto album = AlbumRepository::instance().search(albumId);
        if (!album.has_value()) return;

        editAlbumPage->setAlbum(album.value());
        switchPage(Page::EditAlbum);
    });

    connect(albumPage, &AlbumPage::albumDeleteRequested, this, [this](int albumId) {
        if (QMessageBox::question(
                this,
                "Delete Album",
                "Are you sure you want to delete this album?"
            ) != QMessageBox::Yes)
            return;

        AlbumRepository::instance().remove(albumId);
        albumPage->setAlbums(ArtistService::instance().myAlbums());
        albumPage->showEDButtons();
    });
}


void MainWindow::setupSongsPageConnections() {
    connect(songsPage, &SongsPage::songClicked, this, [](int songId) {
        //todo song page
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(songsPage, &SongsPage::songPlayRequested, this, [](int songId) {
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(songsPage, &SongsPage::songLikeRequested, this, [](int songId) {
        ListenerService::instance().toggleLike(songId);
    });

    connect(songsPage, &SongsPage::songEditRequested, this, [this](int songId) {
        auto albums = ArtistService::instance().myAlbums();
        auto song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        editSongPage->setAlbums(albums);
        editSongPage->setSong(song.value());
        switchPage(Page::EditSong);
    });

    connect(songsPage, &SongsPage::songDeleteRequested, this, [this](int songId) {
        if (QMessageBox::question(
                this,
                "Delete Song",
                "Are you sure you want to delete this song?"
            ) != QMessageBox::Yes)
            return;

        SongRepository::instance().remove(songId);
        switchPage(Page::Home);
    });
}


void MainWindow::setupProfilePageConnections() {
    connect(profilePage, &ProfilePage::editProfileRequested, this, [this]() {
        switchPage(Page::ProfileEdit);

        auto &auth = AuthenticationService::instance();
        if (auth.currentArtist())
            profileEditPage->setArtist(auth.currentArtist().value());
        else
            profileEditPage->setListener(auth.currentListener().value());
    });
}


void MainWindow::setupProfileEditPageConnections() {
    connect(profileEditPage, &ProfileEditPage::changePictureRequested, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Profile Picture",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)"
        );
        if (filePath.isEmpty()) return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) return;

        QByteArray image = file.readAll();
        profileEditPage->setProfilePicture(image);
    });

    connect(profileEditPage, &ProfileEditPage::saveRequested, this, [this]() {
        auto &auth = AuthenticationService::instance();

        if (auth.currentArtist()) {
            Artist artist = profileEditPage->artist();

            ArtistRepository::instance().save(artist);
            auth.updateCurrentArtist(artist);

            profilePage->setArtist(auth.currentArtist().value());
        } else if (auth.currentListener()) {
            Listener listener = profileEditPage->listener();

            ListenerRepository::instance().save(listener);
            auth.updateCurrentListener(listener);

            profilePage->setListener(auth.currentListener().value());
        }

        topBar->refreshUserState();
        sideBar->refreshUserState();
        playerBar->refresh();
        switchPage(Page::Profile);
    });

    connect(profileEditPage, &ProfileEditPage::cancelRequested, this, [this]() {
        switchPage(Page::Profile);

        auto &auth = AuthenticationService::instance();
        if (auth.currentArtist())
            profilePage->setArtist(auth.currentArtist().value());
        else if (auth.currentListener())
            profilePage->setListener(auth.currentListener().value());
    });
}


void MainWindow::setupArtistProfileConnections() {
    connect(artistProfilePage, &ArtistPage::albumClicked, this, [this](int albumId) {
        switchPage(Page::Songs);
        songsPage->showSongs(
            SongsPageMode::AlbumSongs,
            SongRepository::instance().getByAlbum(albumId)
        );
    });

    connect(artistProfilePage, &ArtistPage::songClicked, this, [](int songId) {
        //todo song page
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(artistProfilePage, &ArtistPage::songPlayRequested, this, [](int songId) {
        std::optional<Song> song = SongRepository::instance().search(songId);
        if (!song.has_value()) return;

        PlayerService::instance().setQueue({song.value()});
        PlayerService::instance().play(0);
    });

    connect(artistProfilePage, &ArtistPage::songLikeRequested, this, [](int songId) {
        ListenerService::instance().toggleLike(songId);
    });
}


void MainWindow::setupCreateAlbumConnections() {
    connect(createAlbumPage, &CreateAlbumPage::changeCoverRequested, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Album Cover",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)"
        );
        if (filePath.isEmpty()) return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) return;

        createAlbumPage->setCoverPicture(file.readAll());
    });

    connect(createAlbumPage, &CreateAlbumPage::createRequested, this, [this]() {
        Album album = createAlbumPage->album();

        AlbumRepository::instance().save(album);

        createAlbumPage->clearFields();

        artistProfilePage->setArtist(AuthenticationService::instance().currentArtist().value());
        artistProfilePage->setSongs(ArtistService::instance().mySongs());
        artistProfilePage->setAlbums(ArtistService::instance().myAlbums());
        switchPage(Page::ArtistProfile);
    });

    connect(createAlbumPage, &CreateAlbumPage::cancelRequested, this, [this]() {
        createAlbumPage->clearFields();
        switchPage(Page::ArtistProfile);
    });
}


void MainWindow::setupEditAlbumConnections() {
    connect(editAlbumPage, &EditAlbumPage::changeCoverRequested, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Album Cover",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)"
        );
        if (filePath.isEmpty()) return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) return;

        editAlbumPage->setCoverPicture(file.readAll());
    });

    connect(editAlbumPage, &EditAlbumPage::saveRequested, this, [this]() {
        Album album = editAlbumPage->album();

        AlbumRepository::instance().save(album);

        editAlbumPage->clearFields();

        artistProfilePage->setArtist(AuthenticationService::instance().currentArtist().value());
        artistProfilePage->setSongs(ArtistService::instance().mySongs());
        artistProfilePage->setAlbums(ArtistService::instance().myAlbums());
        switchPage(Page::ArtistProfile);
    });

    connect(editAlbumPage, &EditAlbumPage::cancelRequested, this, [this]() {
        editAlbumPage->clearFields();
        switchPage(Page::ArtistProfile);
    });
}


void MainWindow::setupCreatePlaylistConnections() {
    connect(createPlaylistPage, &CreatePlaylistPage::createRequested, this, [this]() {
        Playlist playlist = createPlaylistPage->playlist();

        PlaylistRepository::instance().save(playlist);

        for (int songId: createPlaylistPage->selectedSongIDs())
            PlaylistRepository::instance().insertSong(playlist.getID(), songId);

        createPlaylistPage->clearFields();

        profilePage->setListener(AuthenticationService::instance().currentListener().value());
        switchPage(Page::Profile);
    });

    connect(createPlaylistPage, &CreatePlaylistPage::cancelRequested, this, [this]() {
        createPlaylistPage->clearFields();
        switchPage(Page::Profile);
    });
}


void MainWindow::setupEditPlaylistConnections() {
    connect(editPlaylistPage, &EditPlaylistPage::saveRequested, this, [this]() {
        Playlist playlist = editPlaylistPage->playlist();

        PlaylistRepository::instance().save(playlist);

        PlaylistRepository::instance().clearSongs(playlist.getID());
        for (int songId: editPlaylistPage->selectedSongIDs())
            PlaylistRepository::instance().insertSong(playlist.getID(), songId);

        editPlaylistPage->clearFields();

        profilePage->setListener(AuthenticationService::instance().currentListener().value());
        switchPage(Page::Profile);
    });

    connect(editPlaylistPage, &EditPlaylistPage::cancelRequested, this, [this]() {
        editPlaylistPage->clearFields();
        switchPage(Page::Profile);
    });
}


void MainWindow::setupCreateSongConnections() {
    connect(createSongPage, &CreateSongPage::changeCoverRequested, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Song Cover",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)"
        );
        if (filePath.isEmpty()) return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) return;

        createSongPage->setCoverPicture(file.readAll());
    });

    connect(createSongPage, &CreateSongPage::browseAudioRequested, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Audio File",
            "",
            "Audio (*.mp3 *.wav *.flac *.ogg *.m4a)"
        );
        if (filePath.isEmpty()) return;

        createSongPage->setAudioFile(filePath);
    });

    connect(createSongPage, &CreateSongPage::createRequested, this, [this]() {
        Song song = createSongPage->song();

        SongRepository::instance().save(song);

        createSongPage->clearFields();

        artistProfilePage->setArtist(AuthenticationService::instance().currentArtist().value());
        artistProfilePage->setSongs(ArtistService::instance().mySongs());
        artistProfilePage->setAlbums(ArtistService::instance().myAlbums());
        switchPage(Page::ArtistProfile);
    });

    connect(createSongPage, &CreateSongPage::cancelRequested, this, [this]() {
        createSongPage->clearFields();
        switchPage(Page::ArtistProfile);
    });
}


void MainWindow::setupEditSongConnections() {
    connect(editSongPage, &EditSongPage::changeCoverRequested, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Song Cover",
            "",
            "Images (*.png *.jpg *.jpeg *.bmp)"
        );
        if (filePath.isEmpty()) return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) return;

        editSongPage->setCoverPicture(file.readAll());
    });

    connect(editSongPage, &EditSongPage::browseAudioRequested, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Select Audio File",
            "",
            "Audio (*.mp3 *.wav *.flac *.ogg *.m4a)"
        );
        if (filePath.isEmpty()) return;

        editSongPage->setAudioFile(filePath);
    });

    connect(editSongPage, &EditSongPage::saveRequested, this, [this]() {
        Song song = editSongPage->song();

        SongRepository::instance().save(song);

        editSongPage->clearFields();

        artistProfilePage->setArtist(AuthenticationService::instance().currentArtist().value());
        artistProfilePage->setSongs(ArtistService::instance().mySongs());
        artistProfilePage->setAlbums(ArtistService::instance().myAlbums());
        switchPage(Page::ArtistProfile);
    });

    connect(editSongPage, &EditSongPage::cancelRequested, this, [this]() {
        editSongPage->clearFields();
        switchPage(Page::ArtistProfile);
    });
}
