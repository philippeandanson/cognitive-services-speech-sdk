//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// audio_source_buffer_data_writer_delegate_impl.h: Implementation declarations/definitions for ISpxAudioSourceBufferDataWriterDelegateImpl
//

// ROBCH: Introduced in AUDIO.V3

#pragma once
#include "spxcore_common.h"
#include "interface_delegate_helpers.h"

namespace Microsoft {
namespace CognitiveServices {
namespace Speech {
namespace Impl {

template <typename DelegateToHelperT = CSpxDelegateToSharedPtrHelper<ISpxAudioSourceBufferDataWriter>>
class ISpxAudioSourceBufferDataWriterDelegateImpl :
    public DelegateToHelperT,
    public ISpxAudioSourceBufferDataWriter
{
private:
    using I = ISpxAudioSourceBufferDataWriter;
protected:
    SPX_DELEGATE_ACCESSORS(Writer, DelegateToHelperT, I)
public:

    void Write(uint8_t* buffer, uint32_t size) override
    {
        InvokeOnDelegate(GetWriterDelegate(), &I::Write, buffer, size);
    }
};

} } } } // Microsoft::CognitiveServices::Speech::Impl
