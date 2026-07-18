#ifndef SPOTIFY_CLONE_MAINWINDOW_H
#define SPOTIFY_CLONE_MAINWINDOW_H
#include "../Components/TopBar/TopBar.h"
#include "../Components/SideBar/SideBar.h"
#include "../Components/PlayerBar/PlayerBar.h"
#include <QMainWindow>
#include <QStackedWidget>
#include "../Page.h"


class LoginPage;
class RegisterPage;

class HomePage;
class SearchPage;

class PlaylistPage;
class AlbumPage;
class SongsPage;

class ProfilePage;
class ProfileEditPage;

class ArtistPage;

class CreateAlbumPage;
class EditAlbumPage;

class CreatePlaylistPage;
class EditPlaylistPage;

class CreateSongPage;
class EditSongPage;


class MainWindow : public QMainWindow {
    Q_OBJECT

    TopBar *topBar;
    SideBar *sideBar;
    PlayerBar *playerBar;

    QStackedWidget *contentStack;

    LoginPage *loginPage;
    RegisterPage *registerPage;

    HomePage *homePage;
    SearchPage *searchPage;

    PlaylistPage *playlistPage;
    AlbumPage *albumPage;
    SongsPage *songsPage;

    ProfilePage *profilePage;
    ProfileEditPage *profileEditPage;

    ArtistPage *artistProfilePage;

    CreateAlbumPage *createAlbumPage;
    EditAlbumPage *editAlbumPage;

    CreatePlaylistPage *createPlaylistPage;
    EditPlaylistPage *editPlaylistPage;

    CreateSongPage *createSongPage;
    EditSongPage *editSongPage;

    void setupUI();

    void setupPages();

    void setupConnections();

    void loadHomePage();

    void switchPage(Page page);

    void setupTopBarConnections();

    void setupSideBarConnections();

    void setupPlayerBarConnections();

    void setupLoginPageConnections();

    void setupRegisterPageConnections();

    void setupHomePageConnections();

    void setupSearchPageConnections();

    void setupPlaylistPageConnections();

    void setupAlbumPageConnections();

    void setupSongsPageConnections();

    void setupProfilePageConnections();

    void setupProfileEditPageConnections();

    void setupArtistProfileConnections();

    void setupCreateAlbumConnections();

    void setupEditAlbumConnections();

    void setupCreatePlaylistConnections();

    void setupEditPlaylistConnections();

    void setupCreateSongConnections();

    void setupEditSongConnections();

public:
    explicit MainWindow(QWidget *parent = nullptr);
};


#endif
