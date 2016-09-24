// MusicXML Class Library v0.3.0
// Copyright (c) 2015 - 2016 by Matthew James Briggs

#pragma once

#include "mx/core/ForwardDeclare.h"
#include "mx/core/ElementInterface.h"
#include "mx/core/Strings.h"
#include "mx/core/elements/MidiDeviceAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( MidiDeviceAttributes )
        MX_FORWARD_DECLARE_ELEMENT( MidiDevice )

        inline MidiDevicePtr makeMidiDevice() { return std::make_shared<MidiDevice>(); }
		inline MidiDevicePtr makeMidiDevice( const XsString& value ) { return std::make_shared<MidiDevice>( value ); }
		inline MidiDevicePtr makeMidiDevice( XsString&& value ) { return std::make_shared<MidiDevice>( std::move( value ) ); }

        class MidiDevice : public ElementInterface
        {
        public:
            MidiDevice();
            MidiDevice( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MidiDeviceAttributesPtr getAttributes() const;
            void setAttributes( const MidiDeviceAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            MidiDeviceAttributesPtr myAttributes;
        };
    }
}