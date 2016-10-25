#include <mess_textedit.h>


MessengerTextEdit::MessengerTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

/**
 * @brief 		This override allows us to send messages by pressing the return key
 *				while this widget has focus
 * @param event	Type of event, only one we care about is key() == Key_Return
 */
void MessengerTextEdit::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Return)
    {
        emit returnPressed();
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}
