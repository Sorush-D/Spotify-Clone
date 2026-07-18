#ifndef SPOTIFY_CLONE_CARDLIST_H
#define SPOTIFY_CLONE_CARDLIST_H
#include <QLabel>
#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>


template<typename CardType, typename DataType>
class CardList : public QWidget {
    QLabel *titleLabel;

    QScrollArea *scrollArea;
    QWidget *container;
    QHBoxLayout *cardsLayout;

    QLabel *emptyLabel;

    void clear();

public:
    explicit CardList(const QString &title, QWidget *parent = nullptr);

    void setItems(const QVector<DataType> &items);
};


template<typename CardType, typename DataType>
CardList<CardType, DataType>::CardList(
    const QString &title,
    QWidget *parent
) : QWidget(parent) {
    titleLabel = new QLabel(title, this);

    scrollArea = new QScrollArea;
    scrollArea->setMaximumHeight(220);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    container = new QWidget;
    cardsLayout = new QHBoxLayout(container);

    scrollArea->setWidget(container);

    emptyLabel = new QLabel("Nothing found.", this);
    emptyLabel->setAlignment(Qt::AlignCenter);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(scrollArea);
    layout->addWidget(emptyLabel);

    scrollArea->hide();
}


template<typename CardType, typename DataType>
void CardList<CardType, DataType>::setItems(const QVector<DataType> &items) {
    clear();

    if (items.isEmpty()) {
        scrollArea->hide();
        emptyLabel->show();
        return;
    }

    emptyLabel->hide();
    scrollArea->show();

    for (const auto &item: items)
        cardsLayout->addWidget(new CardType(item, container));

    cardsLayout->addStretch();
}


template<typename CardType, typename DataType>
void CardList<CardType, DataType>::clear() {
    while (cardsLayout->count() > 0) {
        auto *item = cardsLayout->takeAt(0);
        if (item->widget() != nullptr) delete item->widget();
        delete item;
    }
}


#endif
