cmake_minimum_required(VERSION 4.0)
project(Spotify_Clone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "E:/Qt/6.11.1/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        Multimedia
        REQUIRED)

add_executable(Spotify_Clone main.cpp
        Database/DatabaseManager.cpp
        Database/DatabaseManager.h
        Entities/Account/Account.cpp
        Entities/Account/Account.h
        Entities/Listener/Listener.cpp
        Entities/Listener/Listener.h
        Entities/Artist/Artist.cpp
        Entities/Artist/Artist.h
        Entities/Song/Song.cpp
        Entities/Song/Song.h
        Entities/Playlist/Playlist.cpp
        Entities/Playlist/Playlist.h
        Entities/Album/Album.cpp
        Entities/Album/Album.h
        Repositories/AbstractRepository/AbstractRepository.h
        Repositories/AccountRepository/AccountRepository.h
        Repositories/ArtistRepository/ArtistRepository.cpp
        Repositories/ArtistRepository/ArtistRepository.h
        Repositories/ListenerRepository/ListenerRepository.cpp
        Repositories/ListenerRepository/ListenerRepository.h
        Repositories/AlbumRepository/AlbumRepository.cpp
        Repositories/AlbumRepository/AlbumRepository.h
        Repositories/SongRepository/SongRepository.cpp
        Repositories/SongRepository/SongRepository.h
        Repositories/PlaylistRepository/PlaylistRepository.cpp
        Repositories/PlaylistRepository/PlaylistRepository.h
        Services/AuthenticationService/AuthenticationService.cpp
        Services/AuthenticationService/AuthenticationService.h
        Services/AccountService/AccountService.cpp
        Services/AccountService/AccountService.h
        Services/ArtistService/ArtistService.cpp
        Services/ArtistService/ArtistService.h
        Services/ListenerService/ListenerService.cpp
        Services/ListenerService/ListenerService.h
        Services/SearchService/SearchService.cpp
        Services/SearchService/SearchService.h
        Services/PlayerService/PlayerService.cpp
        Services/PlayerService/PlayerService.h
        Services/BrowseService/BrowseService.cpp
        Services/BrowseService/BrowseService.h
        UI/MainWindow/MainWindow.cpp
        UI/MainWindow/MainWindow.h
        UI/Components/TopBar/TopBar.cpp
        UI/Components/TopBar/TopBar.h
        UI/Components/SideBar/SideBar.cpp
        UI/Components/SideBar/SideBar.h
        UI/Components/PlayerBar/PlayerBar.cpp
        UI/Components/PlayerBar/PlayerBar.h
        icon.qrc
        UI/Pages/Login/LoginPage.cpp
        UI/Pages/Login/LoginPage.h
        UI/Pages/Register/RegisterPage.cpp
        UI/Pages/Register/RegisterPage.h
        UI/Components/Cards/SongCard/SongCard.cpp
        UI/Components/Cards/SongCard/SongCard.h
        UI/Components/Cards/AlbumCard/AlbumCard.cpp
        UI/Components/Cards/AlbumCard/AlbumCard.h
        UI/Components/Cards/ArtistCard/ArtistCard.cpp
        UI/Components/Cards/ArtistCard/ArtistCard.h
        UI/Components/Cards/PlaylistCard/PlaylistCard.cpp
        UI/Components/Cards/PlaylistCard/PlaylistCard.h
        UI/Components/CardList/CardList.h
        UI/Components/CardGrid/CardGrid.h
        UI/Pages/Home/HomePage.cpp
        UI/Pages/Home/HomePage.h
        UI/Pages/Search/SearchPage.cpp
        UI/Pages/Search/SearchPage.h
        UI/Pages/Profile/ProfilePage.cpp
        UI/Pages/Profile/ProfilePage.h
        UI/Pages/Artist/ArtistPage.cpp
        UI/Pages/Artist/ArtistPage.h
        UI/Pages/Album/AlbumPage.cpp
        UI/Pages/Album/AlbumPage.h
        UI/Pages/PlayList/PlaylistPage.cpp
        UI/Pages/PlayList/PlaylistPage.h
        UI/Pages/ProfileEdit/ProfileEditPage.cpp
        UI/Pages/ProfileEdit/ProfileEditPage.h
        UI/Pages/Songs/SongsPage.cpp
        UI/Pages/Songs/SongsPage.h
        UI/Pages/Create/Song/CreateSongPage.cpp
        UI/Pages/Create/Song/CreateSongPage.h
        UI/Pages/Edit/Song/EditSongPage.cpp
        UI/Pages/Edit/Song/EditSongPage.h
        UI/Pages/Create/Album/CreateAlbumPage.cpp
        UI/Pages/Create/Album/CreateAlbumPage.h
        UI/Pages/Edit/Album/EditAlbumPage.cpp
        UI/Pages/Edit/Album/EditAlbumPage.h
        UI/Pages/Create/Playlist/CreatePlaylistPage.cpp
        UI/Pages/Create/Playlist/CreatePlaylistPage.h
        UI/Pages/Edit/Playlist/EditPlaylistPage.cpp
        UI/Pages/Edit/Playlist/EditPlaylistPage.h
        UI/Page.h
)
target_link_libraries(Spotify_Clone
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        Qt::Multimedia
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Sql Multimedia)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
