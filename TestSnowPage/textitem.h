#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QWidget>

class TextItem : public QWidget
{
    Q_OBJECT
public:
    explicit TextItem(QWidget *parent = nullptr);

    void setMyText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_text;

};

#endif // TEXTITEM_H
