// SPDX-FileCopyrightText: 2020 - 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "eyecomfortmodeapplet.h"
#include "constants.h"

#include <DSwitchButton>
#include <DBlurEffectWidget>
#include <DFontSizeManager>

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>

DWIDGET_USE_NAMESPACE

EyeComfortmodeApplet::EyeComfortmodeApplet(QWidget *parent)
    : QWidget(parent)
    , m_title(new DLabel(this))
    , m_switchBtn(new DSwitchButton(this))
    , m_settingButton(new JumpSettingButton(this))
    , m_themeView(new PluginListView(this))
    , m_themeItemModel(new QStandardItemModel(m_themeView))
    , m_lightTheme(new PluginItem(QIcon::fromTheme("theme-light"), tr("Light")))
    , m_darkTheme(new PluginItem(QIcon::fromTheme("theme-dark"), tr("Dark")))
    , m_autoTheme(new PluginItem(QIcon::fromTheme("theme-auto"), tr("Auto")))
    , m_gtkTheme(QString())
{
    initUi();
    initConnect();
}

void EyeComfortmodeApplet::initUi()
{
    m_switchBtn->setFocusPolicy(Qt::NoFocus);
    setFixedWidth(Dock::DOCK_POPUP_WIDGET_WIDTH);

    DFontSizeManager::instance()->bind(m_title, DFontSizeManager::T5);
    m_title->setForegroundRole(QPalette::BrightText);

    QHBoxLayout *appletLayout = new QHBoxLayout;
    appletLayout->setMargin(0);
    appletLayout->setSpacing(0);
    appletLayout->setContentsMargins(20, 0, 10, 0);
    appletLayout->addWidget(m_title);
    appletLayout->addStretch();
    appletLayout->addWidget(m_switchBtn);

    QVBoxLayout *themeLayout = new QVBoxLayout;
    themeLayout->setContentsMargins(10, 0, 10, 0);
    DLabel *titleLabel = new DLabel(tr("Theme"), this);
    titleLabel->setContentsMargins(10, 0, 0, 0);
    DFontSizeManager::instance()->bind(titleLabel, DFontSizeManager::T5);
    themeLayout->addWidget(titleLabel);

    m_themeView->setModel(m_themeItemModel);

    m_themeItemModel->appendRow(m_lightTheme);
    m_themeItemModel->appendRow(m_darkTheme);
    m_themeItemModel->appendRow(m_autoTheme);
    DFontSizeManager::instance()->bind(m_themeView, DFontSizeManager::T6);

    themeLayout->setSpacing(10);
    themeLayout->addWidget(m_themeView);
    m_themeView->setMinimumHeight(130);

    QHBoxLayout *settingLayout = new QHBoxLayout;
    settingLayout->addWidget(m_settingButton);
    settingLayout->setContentsMargins(10, 0, 10, 0);
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(appletLayout, 0);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(themeLayout, 0);
    mainLayout->addStretch();
    mainLayout->addLayout(settingLayout);
    mainLayout->setContentsMargins(0, 10, 0, 10);
    setLayout(mainLayout);
}

void EyeComfortmodeApplet::initConnect()
{
    connect(m_switchBtn, &DSwitchButton::checkedChanged, this, &EyeComfortmodeApplet::enableChanged);
    connect(m_settingButton, &JumpSettingButton::showPageRequestWasSended, this, &EyeComfortmodeApplet::requestHideApplet);
    connect(m_themeView, &PluginListView::clicked, this, &EyeComfortmodeApplet::onThemeListClicked);
}

void EyeComfortmodeApplet::setEnabled(bool enable)
{
    m_switchBtn->blockSignals(true);
    m_switchBtn->setChecked(enable);
    m_switchBtn->blockSignals(false);
}

void EyeComfortmodeApplet::setTitle(const QString &title)
{
    m_title->setText(title);
}

void EyeComfortmodeApplet::setIcon(const QIcon &icon)
{
    m_settingButton->setIcon(icon);
}

void EyeComfortmodeApplet::setDescription(const QString &description)
{
    m_settingButton->setDescription(description);
}

void EyeComfortmodeApplet::setDccPage(const QString &module, const QString &page)
{
    m_settingButton->setDccPage(module, page);
}

const QString EyeComfortmodeApplet::gtkTheme()
{
    return m_gtkTheme;
}

void EyeComfortmodeApplet::setGtkTheme(const QString &value)
{
    if (m_gtkTheme == value)
        return;

    m_gtkTheme = value;
    Q_EMIT gtkThemeChanged(value);
}

void EyeComfortmodeApplet::setEyeComfortVisible(bool visible)
{
    m_title->setVisible(visible);
    m_switchBtn->setVisible(visible);
    m_settingButton->setVisible(visible);
}

void EyeComfortmodeApplet::setHeight(int height)
{
    resize(width(), height);
}

void EyeComfortmodeApplet::onGtkThemeChanged(const QString & value)
{
    if (value == DEEPIN_LIGHT) {
        m_gtkTheme = DEEPIN_LIGHT;
        m_lightTheme->updateState(PluginItemState::ConnectedOnlyPrompt);
        m_darkTheme->updateState(PluginItemState::NoState);
        m_autoTheme->updateState(PluginItemState::NoState);
    } else if (value == DEEPIN_DARK) {
        m_gtkTheme = DEEPIN_DARK;
        m_lightTheme->updateState(PluginItemState::NoState);
        m_darkTheme->updateState(PluginItemState::ConnectedOnlyPrompt);
        m_autoTheme->updateState(PluginItemState::NoState);
    } else {
        m_gtkTheme = DEEPIN_AUTO;
        m_lightTheme->updateState(PluginItemState::NoState);
        m_darkTheme->updateState(PluginItemState::NoState);
        m_autoTheme->updateState(PluginItemState::ConnectedOnlyPrompt);
    }
}

void EyeComfortmodeApplet::onThemeListClicked(const QModelIndex &index)
{
    if (m_lightTheme == m_themeItemModel->itemFromIndex(index) && m_lightTheme->state() == NoState)
        setGtkTheme(DEEPIN_LIGHT);
    else if (m_darkTheme == m_themeItemModel->itemFromIndex(index) && m_darkTheme->state() == NoState)
        setGtkTheme(DEEPIN_DARK);
    else if (m_autoTheme == m_themeItemModel->itemFromIndex(index) && m_autoTheme->state() == NoState)
        setGtkTheme(DEEPIN_AUTO);
}
