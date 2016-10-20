// MusicXML Class Library v0.3.0
// Copyright (c) 2015 - 2016 by Matthew James Briggs

#include "mx/impl/DirectionReader.h"
#include "mx/core/elements/AccordionRegistration.h"
#include "mx/core/elements/Bracket.h"
#include "mx/core/elements/Coda.h"
#include "mx/core/elements/Damp.h"
#include "mx/core/elements/DampAll.h"
#include "mx/core/elements/Dashes.h"
#include "mx/core/elements/Direction.h"
#include "mx/core/elements/DirectionType.h"
#include "mx/core/elements/Dynamics.h"
#include "mx/core/elements/EditorialVoiceDirectionGroup.h"
#include "mx/core/elements/Eyeglasses.h"
#include "mx/core/elements/Footnote.h"
#include "mx/core/elements/HarpPedals.h"
#include "mx/core/elements/Image.h"
#include "mx/core/elements/Level.h"
#include "mx/core/elements/Metronome.h"
#include "mx/core/elements/OctaveShift.h"
#include "mx/core/elements/Offset.h"
#include "mx/core/elements/OtherDirection.h"
#include "mx/core/elements/Pedal.h"
#include "mx/core/elements/Percussion.h"
#include "mx/core/elements/PrincipalVoice.h"
#include "mx/core/elements/Rehearsal.h"
#include "mx/core/elements/Scordatura.h"
#include "mx/core/elements/Segno.h"
#include "mx/core/elements/Sound.h"
#include "mx/core/elements/Staff.h"
#include "mx/core/elements/StringMute.h"
#include "mx/core/elements/Voice.h"
#include "mx/core/elements/Wedge.h"
#include "mx/core/elements/Words.h"
#include "mx/impl/MetronomeReader.h"
#include "mx/impl/PositionFunctions.h"
#include "mx/impl/PrintFunctions.h"

namespace mx
{
    namespace impl
    {
        DirectionReader::DirectionReader( const core::Direction& inDirection, const core::DirectionType& inDirectionType, Cursor inCursor )
        : myDirection{ inDirection }
        , myDirectionType{ inDirectionType }
        , myCursor{ inCursor }
        , myConverter{}
        , myIsMark{ false }
        , myIsSpanner{ false }
        , myIsSpecial{ false }
        , myIsInvalid{ false }
        , myOutMarkData{}
        , myStaffIndex{ 0 }
        {
            initialize();
        }
        
        
        bool DirectionReader::getIsMark() const
        {
            return myIsMark;
        }
        
        
        int DirectionReader::getStaffIndex() const
        {
            return myStaffIndex;
        }
        
        
        std::vector<api::MarkData> DirectionReader::getMarkData() const
        {
            return myOutMarkData;
        }
        
        
        void DirectionReader::initialize()
        {
            parseStaffIndex();
            
            switch ( myDirectionType.getChoice() )
            {
                case core::DirectionType::Choice::rehearsal:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::segno:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::words:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::coda:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::wedge:
                {
                    myIsSpanner = true;
                    break;
                }
                case core::DirectionType::Choice::dynamics:
                {
                    myIsMark = true;
                    parseDynamics();
                    break;
                }
                case core::DirectionType::Choice::dashes:
                {
                    myIsSpanner = true;
                    break;
                }
                case core::DirectionType::Choice::bracket:
                {
                    myIsSpanner = true;
                    break;
                }
                case core::DirectionType::Choice::pedal:
                {
                    myIsSpecial = true;
                    break;
                }
                case core::DirectionType::Choice::metronome:
                {
                    myIsSpecial = true;
                    parseMetronome( myDirectionType );
                    break;
                }
                case core::DirectionType::Choice::octaveShift:
                {
                    break;
                }
                case core::DirectionType::Choice::harpPedals:
                {
                    break;
                }
                case core::DirectionType::Choice::damp:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::dampAll:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::eyeglasses:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::stringMute:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::scordatura:
                {
                    myIsSpecial = true;
                    break;
                }
                case core::DirectionType::Choice::image:
                {
                    myIsSpecial = true;
                    break;
                }
                case core::DirectionType::Choice::principalVoice:
                {
                    myIsSpecial = true;
                    break;
                }
                case core::DirectionType::Choice::accordionRegistration:
                {
                    myIsSpecial = true;
                    break;
                }
                case core::DirectionType::Choice::percussion:
                {
                    myIsMark = true;
                    break;
                }
                case core::DirectionType::Choice::otherDirection:
                {
                    myIsMark = true;
                    break;
                }
                default:
                    myIsInvalid = true;
                    break;
            }
        }
        
        
        void DirectionReader::parseStaffIndex()
        {
            myStaffIndex = 0;
            if( myDirection.getHasStaff() )
            {
                myStaffIndex = myDirection.getStaff()->getValue().getValue() - 1;
            }
        }
        
#if 0
        void DirectionReader::getDirectionData( api::MeasureData& outMeasureData ) const
        {
            std::lock_guard<std::mutex> lock{ myMutex };
            myOutMeasureDataP = &outMeasureData;
            
            for( const auto& directionTypePtr : mySet )
            {
                const auto& directionType = *directionTypePtr;
                
                switch ( directionType.getChoice() )
                {
                    case core::DirectionType::Choice::rehearsal:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::segno:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::words:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::coda:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::wedge:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::dynamics:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::dashes:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::bracket:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::pedal:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::metronome:
                    {
                        parseMetronome( directionType );
                        break;
                    }
                    case core::DirectionType::Choice::octaveShift:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::harpPedals:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::damp:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::dampAll:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::eyeglasses:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::stringMute:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::scordatura:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::image:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::principalVoice:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::accordionRegistration:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::percussion:
                    {
                        break;
                    }
                    case core::DirectionType::Choice::otherDirection:
                    {
                        break;
                    }
                    default:
                        break;
                }
            }
        }
#endif
        
        void DirectionReader::parseRehearsal( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseSegno( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseWords( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseCoda( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseWedge( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseDynamics()
        {
            for( const auto& dynamic : myDirectionType.getDynamicsSet() )
            {
                parseDynamic( *dynamic );
            }
        }
        
        
        void DirectionReader::parseDynamic( const core::Dynamics& dynamic )
        {
            const auto& attr = *dynamic.getAttributes();
            auto markData = api::MarkData{};
            markData.tickTimePosition = myCursor.tickTimePosition;
            markData.positionData = getPositionData( attr );
            markData.printData = getPrintData( attr );
            const auto valueObject = dynamic.getValue();
            
            if( myDirection.getAttributes()->hasPlacement )
            {
                if( markData.positionData.placement == api::Placement::unspecified )
                {
                    markData.positionData.placement = myConverter.convert( myDirection.getAttributes()->placement );
                }
            }
            
            markData.markType = myConverter.convertDynamic( valueObject.getValue() );
            markData.name = valueObject.getValueString();
            if( valueObject.getValue() == core::DynamicsEnum::otherDynamics )
            {
                auto codePoint = api::Smufl::findCodepoint( markData.name );
                if( codePoint > 0 )
                {
                    markData.smuflCodepoint = codePoint;
                    markData.smuflName = markData.name;
                }
            }
            else
            {
                markData.smuflName = api::MarkSmufl::getName( markData.markType, markData.positionData.placement );
                markData.smuflCodepoint = api::MarkSmufl::getCodepoint( markData.markType, markData.positionData.placement );
            }
            myOutMarkData.emplace_back( std::move( markData ) );
        }
        
        
        void DirectionReader::parseDashes( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseBracket( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parsePedal( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseMetronome( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
            //const auto& metronome = *directionType.getMetronome();
            //MetronomeReader reader{ metronome };
            //myOutMeasureDataP->tempos.emplace_back( reader.getTempoData() );
        }
        
        
        void DirectionReader::parseOctaveShift( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseHarpPedals( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseDamp( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseDampAll( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseEyeglasses( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseStringMute( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseScordatura( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseImage( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parsePrincipalVoice( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseAccordionRegistration( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parsePercussion( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseOtherDirection( const core::DirectionType& directionType ) const
        {
            MX_UNUSED( directionType );
        }
    }
}
