#include "ProfileEditPage.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>

ProfileEditPage::ProfileEditPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}


void ProfileEditPage::setupUI() {
    pictureLabel = new QLabel(this);
    pictureLabel->setFixedSize(200, 200);
    pictureLabel->setScaledContents(true);
    pictureLabel->setPixmap(QPixmap(":/Icons/user.png"));

    changePictureButton = new QPushButton("Change Picture", this);

    fullNameEdit = new QLineEdit(this);
    fullNameEdit->setPlaceholderText("Full Name");

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText("Confirm Password");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);

    bioEdit = new QTextEdit(this);
    bioEdit->setPlaceholderText("Biography");

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(cancelButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(pictureLabel, 0, Qt::AlignCenter);
    layout->addWidget(changePictureButton, 0, Qt::AlignCenter);

    layout->addWidget(fullNameEdit);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(confirmPasswordEdit);
    layout->addWidget(bioEdit);
    layout->addWidget(errorLabel);

    layout->addLayout(buttonsLayout);
    layout->addStretch();

    connect(changePictureButton, &QPushButton::clicked, this, &ProfileEditPage::changePictureRequested);
    connect(saveButton, &QPushButton::clicked, this, [this] {
        clearError();
        if (!isValidPasswordFields()) return;

        emit saveRequested();
    });
    connect(cancelButton, &QPushButton::clicked, this, &ProfileEditPage::cancelRequested);
}


void ProfileEditPage::setProfilePicture(const QByteArray &image) {
    profilePicture = image;
    pictureLabel->setPixmap(getProfilePicture(image));
}


void ProfileEditPage::setArtist(const Artist &artist) {
    currentArtist = artist;
    currentListener.reset();

    clearError();

    profilePicture = artist.getProfilePicture();
    pictureLabel->setPixmap(getProfilePicture(profilePicture));

    fullNameEdit->setText(artist.getFullName());
    usernameEdit->setText(artist.getUserName());

    passwordEdit->clear();
    confirmPasswordEdit->clear();

    bioEdit->setPlainText(artist.getBiography());
    bioEdit->show();
}


void ProfileEditPage::setListener(const Listener &listener) {
    currentListener = listener;
    currentArtist.reset();

    clearError();

    profilePicture = listener.getProfilePicture();
    pictureLabel->setPixmap(getProfilePicture(profilePicture));

    fullNameEdit->setText(listener.getFullName());
    usernameEdit->setText(listener.getUserName());

    passwordEdit->clear();
    confirmPasswordEdit->clear();

    bioEdit->clear();
    bioEdit->hide();
}


Artist ProfileEditPage::artist() const {
    if (!currentArtist) throw std::runtime_error("Want artist but its\'s empty");
    Artist artist = *currentArtist;

    artist.setFullName(fullNameEdit->text().trimmed());
    artist.setUserName(usernameEdit->text().trimmed());

    if (!passwordEdit->text().isEmpty()) artist.setPassword(passwordEdit->text());

    artist.setBiography(bioEdit->toPlainText().trimmed());
    artist.setProfilePicture(profilePicture);

    return artist;
}


Listener ProfileEditPage::listener() const {
    if (!currentListener) throw std::runtime_error("Want listener but its\'s empty");
    Listener listener = *currentListener;

    listener.setFullName(fullNameEdit->text().trimmed());
    listener.setUserName(usernameEdit->text().trimmed());

    if (!passwordEdit->text().isEmpty()) listener.setPassword(passwordEdit->text());

    listener.setProfilePicture(profilePicture);

    return listener;
}


QPixmap ProfileEditPage::getProfilePicture(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/user.png");

    QPixmap result = pixmap.scaled(
        pictureLabel->size(),
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
    );

    QBitmap mask(result.size());
    mask.fill(Qt::color0);

    QPainter painter(&mask);
    painter.setBrush(Qt::color1);
    painter.drawEllipse(mask.rect());

    result.setMask(mask);

    return result;
}


void ProfileEditPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void ProfileEditPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}


bool ProfileEditPage::isValidPasswordFields() {
    if (passwordEdit->text().isEmpty() && confirmPasswordEdit->text().isEmpty()) return true;

    if (passwordEdit->text().isEmpty()) {
        setError("Password cannot be empty.");
        return false;
    }

    if (passwordEdit->text() != confirmPasswordEdit->text()) {
        setError("Passwords don't match.");
        return false;
    }

    return true;
}
