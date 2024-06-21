/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DBusClientManager -p dbusclientmanager dde-dock-ClientManager.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUSCLIENTMANAGER_H_1465195317
#define DBUSCLIENTMANAGER_H_1465195317

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface dde.dock.ClientManager
 */
class DBusClientManager: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage& msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count())
            return;
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName != "dde.dock.ClientManager")
            return;
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        const QMetaObject *self = metaObject();
        auto iter = changedProps.begin();
        while (iter != changedProps.end()) {
            for (int i = self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() != iter.key()) {
                    Q_EMIT p.notifySignal().invoke(this);
                }
            }
            iter++;
        }
    }

public:
    static inline const char *staticInterfaceName() { return "dde.dock.ClientManager"; }

public:
    explicit DBusClientManager(QObject *parent = 0);

    ~DBusClientManager() override;

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<bool> ActivateWindow(uint in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("ActivateWindow"), argumentList);
    }

    inline QDBusPendingReply<bool> CloseWindow(uint in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("CloseWindow"), argumentList);
    }

    inline QDBusPendingReply<uint> CurrentActiveWindow()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("CurrentActiveWindow"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void ActiveWindowChanged(uint activeWinId);
// begin property changed signals
};

namespace dde {
  namespace dock {
    typedef ::DBusClientManager ClientManager;
  }
}
#endif
