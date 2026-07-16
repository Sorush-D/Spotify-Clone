#include "ProfileEditPage.h"
#include <QHBoxLayout>

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


void ProfileEditPage::setArtist(const Artist &artist) {
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


QPixmap ProfileEditPage::getProfilePicture(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/user.png");
    return pixmap;
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
