// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "ActionPaletteItem.h"
#include <LibraryResources.h>

#include "ActionPaletteItem.g.cpp"

using namespace winrt;
using namespace winrt::TerminalApp;
using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::System;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Microsoft::Terminal::Settings::Model;

namespace winrt::TerminalApp::implementation
{
    ActionPaletteItem::ActionPaletteItem(Microsoft::Terminal::Settings::Model::Command const& command) :
        _Command(command)
    {
        Name(command.Name());
        KeyChordText(KeyChordSerialization::ToString(command.Keys()));
        Icon(command.IconPath());

        _commandChangedRevoker = command.PropertyChanged(winrt::auto_revoke, [weakThis{ get_weak() }](auto& sender, auto& e) {
            auto item{ weakThis.get() };
            auto senderCommand{ sender.try_as<Microsoft::Terminal::Settings::Model::Command>() };

            if (item && senderCommand)
            {
                auto changedProperty = e.PropertyName();
                if (changedProperty == L"Name")
                {
                    item->Name(senderCommand.Name());
                }
                else if (changedProperty == L"KeyChordText")
                {
                    item->KeyChordText(KeyChordSerialization::ToString(senderCommand.Keys()));
                }
                else if (changedProperty == L"IconPath")
                {
                    item->Icon(senderCommand.IconPath());
                }
            }
        });
    }
}
