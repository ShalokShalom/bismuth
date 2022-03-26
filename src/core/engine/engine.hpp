// SPDX-FileCopyrightText: 2022 Mikhail Zolotukhin <mail@gikari.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "plasma-api/client.hpp"
#include "windows_list.hpp"

namespace Bismuth
{
class Engine
{
public:
    Engine();

    void addWindow(PlasmaApi::Client);

private:
    WindowsList m_windows{};
};
}
