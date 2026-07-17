#ifndef SPOTIFY_CLONE_CARDGRID_H
#define SPOTIFY_CLONE_CARDGRID_H
#include <qgridlayout.h>
#include <QLabel>
#include <QScrollArea>


template<typename CardType, typename DataType>
class CardGrid : public QWidget {
    QLabel *titleLabel;

    QScrollArea *scrollArea;
    QWidget *container;
    QGridLayout *cardsLayout;

    void clear();

public:
    explicit CardGrid(const QString &title, QWidget *parent = nullptr);

    void setItems(const QVector<DataType> &items);

    void setTitle(const QString &title);
};


template<typename CardType, typename DataType>
CardGrid<CardType, DataType>::CardGrid(
    const QString &title,
    QWidget *parent
) : QWidget(parent) {
    titleLabel = new QLabel(title, this);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    container = new QWidget;
    cardsLayout = new QGridLayout(container);

    scrollArea->setWidget(container);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(scrollArea);
}


template<typename CardType, typename DataType>
void CardGrid<CardType, DataType>::setItems(const QVector<DataType> &items) {
    clear();

    constexpr int COLUMNS = 6;

    for (int i = 0; i < items.size(); ++i) {
        int row = i / COLUMNS;
        int col = i % COLUMNS;

        cardsLayout->addWidget(new CardType(items[i], container), row, col);
    }
}


template<typename CardType, typename DataType>
void CardGrid<CardType, DataType>::clear() {
    while (cardsLayout->count() > 0) {
        auto *item = cardsLayout->takeAt(0);
        if (item->widget() != nullptr) delete item->widget();
        delete item;
    }
}


template<typename CardType, typename DataType>
void CardGrid<CardType, DataType>::setTitle(const QString &title) {
    titleLabel->setText(title);
}


#endif
