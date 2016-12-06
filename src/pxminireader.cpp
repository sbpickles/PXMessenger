#include "pxminireader.h"

MessIniReader::MessIniReader()
{
    inisettings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "PXMessenger", "PXMessenger", NULL);
}
MessIniReader::~MessIniReader()
{
    delete inisettings;
}
bool MessIniReader::checkAllowMoreThanOne()
{
    if(inisettings->contains("config/AllowMoreThanOneInstance"))
    {
        return inisettings->value("config/AllowMoreThanOneInstance", false).toBool();
    }
    inisettings->setValue("config/AllowMoreThanOneInstance", false);
    return false;
}
void MessIniReader::setAllowMoreThanOne(bool value)
{
    inisettings->setValue("config/AllowMoreThanOneInstance", value);
}
int MessIniReader::getUUIDNumber()
{
    int i = 0;
    QString uuidStr = "uuid/";
    while(inisettings->value(uuidStr + QString::number(i), "") == "INUSE")
    {
        i++;
    }
    if(inisettings->value(uuidStr + QString::number(i), "") == "")
    {
        inisettings->setValue(uuidStr+QString::number(i), QUuid::createUuid());
    }
    return i;
}
QUuid MessIniReader::getUUID(int num, bool takeIt)
{
    if(inisettings->value("uuid/" + QString::number(num), "") == "")
    {
        inisettings->setValue("uuid/" + QString::number(num), QUuid::createUuid().toString());
    }
    QUuid uuid = inisettings->value("uuid/" + QString::number(num), "").toUuid();
    if(takeIt)
    {
        inisettings->setValue("uuid/" + QString::number(num), "INUSE");
    }
    return uuid;
}
int MessIniReader::resetUUID(int num, QUuid uuid)
{
    inisettings->setValue("uuid/" + QString::number(num), uuid.toString());
    return 1;
}
void MessIniReader::setPort(QString protocol, int portNumber)
{
    inisettings->setValue("port/" + protocol, portNumber);
}
unsigned short MessIniReader::getPort(QString protocol)
{
    unsigned short portNumber = inisettings->value("port/" + protocol, 0).toUInt();
    return portNumber;
    if( portNumber == 0)
    {
        if(protocol == "UDP")
            inisettings->setValue("port/" + protocol, 0);
        else
            inisettings->setValue("port/" + protocol, 0);
    }
    return 0;
}
void MessIniReader::setHostname(QString hostname)
{
    inisettings->setValue("hostname/hostname", hostname.left(MAX_HOSTNAME_LENGTH));
}
QString MessIniReader::getHostname(QString defaultHostname)
{
    QString hostname = inisettings->value("hostname/hostname", defaultHostname).toString();

    return hostname.left(MAX_HOSTNAME_LENGTH);
}
void MessIniReader::setWindowSize(QSize windowSize)
{
    if(windowSize.isValid())
        inisettings->setValue("WindowSize/QSize", windowSize);
}
QSize MessIniReader::getWindowSize(QSize defaultSize)
{
    QSize windowSize = inisettings->value("WindowSize/QSize", defaultSize).toSize();
    if(windowSize.isValid())
        return windowSize;
    else
    {
        windowSize = QSize(700, 500);
        inisettings->setValue("WindowSize/QSize", windowSize);
        return windowSize;
    }
}
void MessIniReader::setMute(bool mute)
{
    inisettings->setValue("config/Mute", mute);
}
bool MessIniReader::getMute()
{
    return inisettings->value("config/Mute", false).toBool();
}
void MessIniReader::setFocus(bool focus)
{
    inisettings->setValue("config/PreventFocus", focus);
}
bool MessIniReader::getFocus()
{
    return inisettings->value("config/PreventFocus", false).toBool();
}
QString MessIniReader::getFont()
{
    return inisettings->value("config/Font", "").toString();
}
void MessIniReader::setFont(QString font)
{
    inisettings->setValue("config/Font", font);
}
QString MessIniReader::getMulticastAddress()
{
    QString ipFull = inisettings->value("net/MulticastAddress", "").toString();
    if(ipFull.isEmpty())
    {
        return QString("");
    }
    QStringList ipList = ipFull.split(".");
    for(int i = 0; i < 4; i++)
    {
        if(ipList[i].toUInt() > 255)
            ipList[i] = "0";
    }

    return ipList.join("");
}
int MessIniReader::setMulticastAddress(QStringList ip)
{
    QString ipFull = QString();
    for(int i = 0; i < 4; i++)
    {
        if(ip[i].toUInt() > 255)
            return -1;
        ip.append(ip[i] + QString("."));
    }
    ipFull.chop(1);

    inisettings->setValue("net/MulticastAddress", ipFull);

    return 0;
}
