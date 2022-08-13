// SPDX-FileCopyrightText: 2022 Mikhail Zolotukhin <mail@gikari.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>
#include <QQuickItem>

#include <memory>

#include "config.hpp"

class CorePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

namespace PlasmaApi
{
class Api;
}

namespace Bismuth
{

class View;
class Engine;
class Controller;

class Core : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    Core(QQuickItem *parent = nullptr);

    /**
     * Initializes the Core. Acts like a constructor, but bypasses the
     * limitations of one.
     */
    Q_INVOKABLE void init();

private:
    QQmlEngine *m_qmlEngine; ///< Pointer to the engine, that is currently using the Core element

    std::unique_ptr<Bismuth::Controller> m_controller;
    std::unique_ptr<Bismuth::Config> m_config;
    std::unique_ptr<PlasmaApi::Api> m_plasmaApi;
    std::unique_ptr<Bismuth::Engine> m_engine;
    std::unique_ptr<Bismuth::View> m_view;
};

}
