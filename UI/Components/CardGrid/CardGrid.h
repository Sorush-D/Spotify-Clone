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
    explicit CardGrid(const QString &title,const QVector<DataType> &,QWidget *parent = nullptr);

    void setItems(const QVector<DataType> &items);
};


template<typename CardType, typename DataType>
CardGrid<CardType, DataType>::CardGrid(
    const QString &title,
    const QVector<DataType> &items,
    QWidget *parent
) : QWidget(parent) {
    titleLabel = new QLabel(title, this);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    container = new QWidget(scrollArea);
    cardsLayout = new QGridLayout(container);

    scrollArea->setWidget(container);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(scrollArea);

    setItems(items);
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


#endif
