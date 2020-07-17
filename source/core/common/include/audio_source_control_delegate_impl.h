//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// audio_source_control_delegate_impl.h: Implementation declarations/definitions for ISpxAudioSourceControlDelegateImpl
//

// ROBCH: Introduced in AUDIO.V3

#pragma once
#include "spxcore_common.h"
#include "interface_delegate_helpers.h"

namespace Microsoft {
namespace CognitiveServices {
namespace Speech {
namespace Impl {

template <typename DelegateToHelperT = CSpxDelegateToSharedPtrHelper<ISpxAudioSourceControl>>
class ISpxAudioSourceControlDelegateImpl :
    public DelegateToHelperT,
    public ISpxAudioSourceControl
{
private:
    using I = ISpxAudioSourceControl;

protected:
    SPX_DELEGATE_ACCESSORS(Control, DelegateToHelperT, I)

public:
    void StartAudio(std::shared_ptr<ISpxAudioSourceNotifyMe> notify) override
    {
        InvokeOnDelegate(GetControlDelegate(), &I::StartAudio, notify);
    }

    void StopAudio() override
    {
        InvokeOnDelegate(GetControlDelegate(), &I::StopAudio);
    }
};


} } } } // Microsoft::CognitiveServices::Speech::Impl
