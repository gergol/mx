// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_API_TESTS

#include "mxtest/api/ApiTester.h"
#include "mxtest/file/MxFileTest.h"
#include "mxtest/file/MxFileTestGroup.h"
#include "mx/api/DocumentManager.h"
#include "cpul/cpulTestHarness.h"
#include "mx/api/ScoreData.h"
#include "mxtest/api/ApiTester.h"
#include "mxtest/api/ApiLy43eScoreData.h"

using namespace mx::api;

namespace mxtest
{
	constexpr const char* const testFileName = "ly43e_Multistaff_ClefDynamics.xml";
    
    class ApiLy43eScoreData : public ScoreDataCreator
    {
        virtual mx::api::ScoreData createScoreData() const override
        {
            return apiLy43eScoreData();
        }
    };
    
    class ApiLy43eScoreData;
    
    static const ApiTester ApiLy43eTest
    {
        ScoreDataCreatorPtr{ new ApiLy43eScoreData{} },
        MxFileRepository::getTestFile( testFileName ),
        __FILE__,
        __LINE__
    };
}

#endif


/*
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE score-partwise PUBLIC "-//Recordare//DTD MusicXML 1.0 Partwise//EN"
                                "http://www.musicxml.org/dtds/partwise.dtd">
<score-partwise>
  <identification>
    <miscellaneous>
      <miscellaneous-field name="description">A piano staff with dynamics and 
          clef changes, where each element (ffff, wedge and clef changes) 
          applies only to one voice or one staff, respectively.</miscellaneous-field>
    </miscellaneous>
  </identification>
  <part-list>
    <score-part id="P1">
      <part-name>MusicXML Part</part-name>
    </score-part>
  </part-list>
  <!--=========================================================-->
  <part id="P1">
    <measure number="1">
      <attributes>
        <divisions>8</divisions>
        <key>
          <fifths>0</fifths>
          <mode>major</mode>
        </key>
        <time symbol="common">
          <beats>4</beats>
          <beat-type>4</beat-type>
        </time>
        <staves>2</staves>
        <clef number="1">
          <sign>G</sign>
          <line>2</line>
        </clef>
        <clef number="2">
          <sign>F</sign>
          <line>4</line>
        </clef>
      </attributes>
      <direction placement="below">
        <direction-type>
          <dynamics>
            <ffff/>
          </dynamics>
        </direction-type>
        <staff>1</staff>
      </direction>
      <note>
        <pitch>
          <step>C</step>
          <octave>5</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>B</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>A</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <direction placement="below">
        <direction-type>
          <dynamics>
            <p/>
          </dynamics>
        </direction-type>
        <offset>1</offset>
        <staff>1</staff>
      </direction>
      <note>
        <pitch>
          <step>G</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <backup>
        <duration>32</duration>
      </backup>
      <direction placement="below">
        <direction-type>
          <wedge spread="0" type="crescendo"/>
        </direction-type>
        <staff>2</staff>
      </direction>
      <note>
        <pitch>
          <step>A</step>
          <octave>2</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>B</step>
          <octave>2</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <direction>
        <direction-type>
          <wedge spread="15" type="stop"/>
        </direction-type>
        <staff>2</staff>
      </direction>
      <note>
        <pitch>
          <step>C</step>
          <octave>3</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>D</step>
          <octave>3</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
    </measure>
    <!--=======================================================-->
    <measure number="2">
      <attributes>
        <key>
          <fifths>2</fifths>
          <mode>major</mode>
        </key>
        <clef number="2">
          <sign>G</sign>
          <line>2</line>
        </clef>
      </attributes>
      <note>
        <pitch>
          <step>A</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>B</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>C</step>
          <alter>1</alter>
          <octave>5</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>D</step>
          <octave>5</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <backup>
        <duration>32</duration>
      </backup>
      <note>
        <pitch>
          <step>F</step>
          <alter>1</alter>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>G</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>A</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>B</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
    </measure>
    <!--=======================================================-->
    <measure number="3">
      <attributes>
        <clef number="1">
          <sign>C</sign>
          <line>2</line>
        </clef>
      </attributes>
      <note>
        <pitch>
          <step>D</step>
          <octave>5</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>C</step>
          <alter>1</alter>
          <octave>5</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>B</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <note>
        <pitch>
          <step>A</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>1</voice>
        <type>quarter</type>
        <staff>1</staff>
      </note>
      <backup>
        <duration>32</duration>
      </backup>
      <note>
        <pitch>
          <step>A</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>B</step>
          <octave>4</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>C</step>
          <alter>1</alter>
          <octave>5</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
      <note>
        <pitch>
          <step>D</step>
          <octave>5</octave>
        </pitch>
        <duration>8</duration>
        <voice>2</voice>
        <type>quarter</type>
        <staff>2</staff>
      </note>
    </measure>
    <!--=======================================================-->
    <measure number="4">
      <note>
        <rest/>
        <duration>32</duration>
        <voice>1</voice>
        <staff>1</staff>
      </note>
      <backup>
        <duration>32</duration>
      </backup>
      <note>
        <rest/>
        <duration>32</duration>
        <voice>2</voice>
        <staff>2</staff>
      </note>
      <barline location="right">
        <bar-style>light-heavy</bar-style>
      </barline>
    </measure>
  </part>
  <!--=========================================================-->
</score-partwise>

*/
