#include "textitem.h"
#include <QPainter>

TextItem::TextItem(QWidget *parent):
    QWidget (parent)
{

}

void TextItem::setMyText(const QString &text)
{
    m_text = text;
}


///
/// \brief GetTextByWidth 根据宽度得到文字
/// \param fm
/// \param text
/// \param width
/// \return
///
QString GetTextByWidth(const QFontMetrics& fm, const QString& text, int width)
{
    if(width <= 0)
        return QString();

    int offset = 0;
    QString subStr;
    do
    {
       subStr  = text.mid(0, text.length() - offset++);
    }while(!(fm.width(subStr,width) <= width));

    return subStr;
}

///
/// \brief GetTextLinesByRectSize 根据宽、高得到文字段落
/// \param fm
/// \param text
/// \param size
/// \return
///
QStringList GetTextLinesByRectSize(const QFontMetrics& fm, const QString& text, const QSize& size)
{
    QStringList splitLines = text.split('\n');
    QStringList result;
    if(size.width() <= 120)
    {
        int ab =0;
        ab++;
    }
    for(int i = 0; i < splitLines.count(); i++)
    {
        QString splitLine = splitLines[i];

        do
        {

            QString splitLineElidedText = GetTextByWidth(fm, splitLine, size.width());

            if(!splitLineElidedText.isEmpty())
                result.append(splitLineElidedText);



            splitLine = splitLine.mid(splitLineElidedText.length(), splitLine.length() - splitLineElidedText.length());
        }
        while(!splitLine.isEmpty());
    }

    return result;
}

///
/// \brief PaintStrokeText 画艺术字(硬发光)
/// \param painter
/// \param rect 所需要画的区域
/// \param text 文字
/// \param font 字体
/// \param strokeWidth 艺术字发光宽度
/// \param strokeColor 艺术字发光颜色
/// \param option 对齐方式
///
void PaintStrokeText(QPainter* painter,
                     const QRect& rect,
                     const QString& text,
                     const QFont& font,
                     int strokeWidth = 2,
                     const QColor& strokeColor=QColor(209, 209, 209),
                     const QTextOption& option = QTextOption()
                     )
{
    painter->save();
    painter->setFont(font);

    QPen oldPen = painter->pen();
    QPen strokePen = QPen(strokeColor,strokeWidth);

    QStringList textList = GetTextLinesByRectSize(painter->fontMetrics(), text, rect.size());
    int fontHeight = painter->fontMetrics().height();
    int lineHeight = painter->fontMetrics().lineSpacing();

    for(int i = 0; i < textList.count(); i++)
    {


        QString textLine = textList[i];
        QRect textLineBoundingRect = painter->fontMetrics().boundingRect(rect,option.flags(),textLine);
        QSize textLineSize = textLineBoundingRect.size();


        int offsetX = 0;
        int offsetY = i * lineHeight;

        //offset x
        if(option.alignment().testFlag(Qt::AlignLeft))
        {
            offsetX = 0;
        }
        if(option.alignment().testFlag(Qt::AlignRight))
        {
            offsetX = rect.width() - textLineBoundingRect.width();
        }
        if(option.alignment().testFlag(Qt::AlignHCenter))
        {
            offsetX = (rect.width() - textLineBoundingRect.width())/2;
        }

        //offset y
        if(option.alignment().testFlag(Qt::AlignTop))
        {
            //offsetY = 0;
        }
        if(option.alignment().testFlag(Qt::AlignBottom))
        {

            offsetY += rect.height() - textList.count() * lineHeight;
        }
        if(option.alignment().testFlag(Qt::AlignVCenter))
        {
            offsetY += (rect.height() - textList.count() * lineHeight)/2;
        }



        textLineBoundingRect.setLeft(rect.left() + offsetX);
        textLineBoundingRect.setRight(textLineBoundingRect.left() + textLineSize.width());
        textLineBoundingRect.setTop(rect.top() + offsetY);
        textLineBoundingRect.setBottom(textLineBoundingRect.top() + textLineSize.height());

        QPainterPath strokePath;
        strokePath.addText(textLineBoundingRect.bottomLeft(), font, textLine);
        painter->strokePath(strokePath, strokePen);
        //painter->drawPath(strokePath);//debug
        painter->fillPath(strokePath, QBrush(oldPen.color()));
    }

    //for .debug
    //painter->drawText(rect, text, option);
    painter->restore();
}


void TextItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //    QString text = QString(QStringLiteral("艺术字效果stroke text style"));
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    return PaintStrokeText(&painter,
                           rect(),
                           m_text,
                           font,
                           8,
                           QColor(252, 139, 121),
                           QTextOption(Qt::AlignCenter));
}

