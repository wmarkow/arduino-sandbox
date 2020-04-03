<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="bike_computer">
<packages>
<package name="STEPPER_GAUGE">
<wire x1="4.25" y1="15.25" x2="-4.25" y2="15.25" width="0.1524" layer="21"/>
<wire x1="-14.5" y1="-15.25" x2="14.5" y2="-15.25" width="0.1524" layer="21"/>
<wire x1="6.75" y1="-9" x2="6.75" y2="-6" width="0.1524" layer="21"/>
<wire x1="8.25" y1="-7.5" x2="5.25" y2="-7.5" width="0.1524" layer="21"/>
<wire x1="-12" y1="4.75" x2="-11.25" y2="8" width="0.1524" layer="21"/>
<wire x1="12" y1="4.75" x2="11.25" y2="8" width="0.1524" layer="21"/>
<wire x1="-4.25" y1="15.25" x2="-11.25" y2="8" width="0.1524" layer="21" curve="92.045408"/>
<wire x1="4.25" y1="15.25" x2="11.25" y2="8" width="0.1524" layer="21" curve="-92.045408"/>
<circle x="12.25" y="2.5" radius="2.26384375" width="0.1524" layer="45"/>
<circle x="-12.25" y="2.5" radius="2.25" width="0.1524" layer="45"/>
<wire x1="-2.25" y1="-10.25" x2="-2.25" y2="-8.25" width="0.1524" layer="21"/>
<wire x1="-3.25" y1="-9.25" x2="-1.25" y2="-9.25" width="0.1524" layer="21"/>
<circle x="-2.25" y="-9.25" radius="1.5" width="0.1524" layer="45"/>
<circle x="6.75" y="-7.5" radius="3.04138125" width="0.1524" layer="21"/>
<circle x="6.75" y="-7.5" radius="2" width="0.1524" layer="21"/>
<wire x1="14.5" y1="-15.25" x2="14.5" y2="2.5" width="0.1524" layer="21"/>
<wire x1="-14.5" y1="-15.25" x2="-14.5" y2="-11.75" width="0.1524" layer="21"/>
<wire x1="-14.5" y1="-11.75" x2="-14.5" y2="-4.75" width="0.1524" layer="21"/>
<wire x1="-14.5" y1="-4.75" x2="-14.5" y2="2.5" width="0.1524" layer="21"/>
<wire x1="-14.5" y1="-11.75" x2="-5.5" y2="-11.75" width="0.1524" layer="21"/>
<wire x1="-14.5" y1="-4.75" x2="-5.5" y2="-4.75" width="0.1524" layer="21"/>
<wire x1="4.75" y1="6.25" x2="-5.75" y2="6.25" width="0.1524" layer="21"/>
<wire x1="3.5" y1="13" x2="-7" y2="13" width="0.1524" layer="21"/>
<wire x1="4.75" y1="5" x2="-5.75" y2="5" width="0.1524" layer="21"/>
<wire x1="3.5" y1="11.75" x2="-7" y2="11.75" width="0.1524" layer="21"/>
<wire x1="4" y1="6.75" x2="4" y2="4.5" width="0.1524" layer="21"/>
<wire x1="2.75" y1="13.5" x2="2.75" y2="11.25" width="0.1524" layer="21"/>
<wire x1="-5" y1="6.75" x2="-5" y2="4.5" width="0.1524" layer="22"/>
<wire x1="-6.25" y1="13.5" x2="-6.25" y2="11.25" width="0.1524" layer="22"/>
<smd name="P$1" x="-11.75" y="-4.75" dx="5.08" dy="2.54" layer="1"/>
<smd name="P$2" x="-6.75" y="-4.75" dx="5.08" dy="2.54" layer="1"/>
<smd name="P$3" x="-11.75" y="-11.75" dx="5.08" dy="2.54" layer="1"/>
<smd name="P$4" x="-6.75" y="-11.75" dx="5.08" dy="2.54" layer="1"/>
<smd name="P$5" x="1.75" y="12" dx="6.4516" dy="3.2512" layer="1"/>
<smd name="P$6" x="-4.5" y="12" dx="6.4516" dy="3.2512" layer="1"/>
<smd name="P$7" x="2.5" y="5" dx="6.4516" dy="3.2512" layer="1"/>
<smd name="P$8" x="-3.75" y="5" dx="6.4516" dy="3.2512" layer="1"/>
</package>
<package name="OLED_0.9">
<pad name="SDA" x="-15.24" y="3.81" drill="0.6" shape="octagon"/>
<pad name="SCL" x="-15.24" y="1.27" drill="0.6" shape="octagon"/>
<pad name="VCC" x="-15.24" y="-1.27" drill="0.6" shape="octagon"/>
<wire x1="-17.78" y1="6.35" x2="-17.78" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="-6.35" x2="17.78" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="17.78" y1="-6.35" x2="17.78" y2="6.35" width="0.1524" layer="21"/>
<wire x1="17.78" y1="6.35" x2="-17.78" y2="6.35" width="0.1524" layer="21"/>
<pad name="GND" x="-15.24" y="-3.81" drill="0.6" shape="square"/>
<wire x1="-11.43" y1="5.08" x2="-11.43" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="-5.08" x2="15.24" y2="-5.08" width="0.1524" layer="21"/>
<wire x1="15.24" y1="-5.08" x2="15.24" y2="5.08" width="0.1524" layer="21"/>
<wire x1="15.24" y1="5.08" x2="-11.43" y2="5.08" width="0.1524" layer="21"/>
</package>
<package name="DRV8255_BOARD">
<pad name="P$1" x="-6.35" y="8.89" drill="0.6" shape="octagon"/>
<pad name="P$2" x="-6.35" y="6.35" drill="0.6" shape="octagon"/>
<pad name="P$3" x="-6.35" y="3.81" drill="0.6" shape="octagon"/>
<pad name="P$4" x="-6.35" y="1.27" drill="0.6" shape="octagon"/>
<pad name="P$5" x="-6.35" y="-1.27" drill="0.6" shape="octagon"/>
<pad name="P$6" x="-6.35" y="-3.81" drill="0.6" shape="octagon"/>
<pad name="P$7" x="-6.35" y="-6.35" drill="0.6" shape="octagon"/>
<pad name="P$8" x="-6.35" y="-8.89" drill="0.6" shape="octagon"/>
<pad name="P$9" x="6.35" y="8.89" drill="0.6" shape="octagon"/>
<pad name="P$10" x="6.35" y="6.35" drill="0.6" shape="octagon"/>
<pad name="P$11" x="6.35" y="3.81" drill="0.6" shape="octagon"/>
<pad name="P$12" x="6.35" y="1.27" drill="0.6" shape="octagon"/>
<pad name="P$13" x="6.35" y="-1.27" drill="0.6" shape="octagon"/>
<pad name="P$14" x="6.35" y="-3.81" drill="0.6" shape="octagon"/>
<pad name="P$15" x="6.35" y="-6.35" drill="0.6" shape="octagon"/>
<pad name="P$16" x="6.35" y="-8.89" drill="0.6" shape="octagon"/>
<wire x1="-7.62" y1="10.16" x2="7.62" y2="10.16" width="0.1524" layer="21"/>
<wire x1="7.62" y1="10.16" x2="7.62" y2="-10.16" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-10.16" x2="-7.62" y2="-10.16" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-10.16" x2="-7.62" y2="10.16" width="0.1524" layer="21"/>
<text x="-3.81" y="7.62" size="1.778" layer="25">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="STEPPER_GAUGE">
<pin name="B2" x="-17.78" y="2.54" length="middle"/>
<pin name="B1" x="-17.78" y="-2.54" length="middle"/>
<pin name="A2" x="-2.54" y="-17.78" length="middle" rot="R90"/>
<pin name="A1" x="2.54" y="-17.78" length="middle" rot="R90"/>
<circle x="0" y="0" radius="12.951509375" width="0.1524" layer="94"/>
<circle x="0" y="0" radius="1.27" width="0.1524" layer="94"/>
<wire x1="-1.016" y1="0.762" x2="6.35" y2="9.906" width="0.1524" layer="94"/>
<wire x1="6.35" y1="9.906" x2="1.016" y2="-0.762" width="0.1524" layer="94"/>
</symbol>
<symbol name="OLED_0.9">
<pin name="SCL" x="-22.86" y="2.54" length="middle"/>
<pin name="SDA" x="-22.86" y="5.08" length="middle"/>
<pin name="VCC" x="-22.86" y="-2.54" length="middle"/>
<pin name="GND" x="-22.86" y="-5.08" length="middle"/>
<wire x1="-17.78" y1="7.62" x2="-17.78" y2="-7.62" width="0.1524" layer="94"/>
<wire x1="-17.78" y1="-7.62" x2="12.7" y2="-7.62" width="0.1524" layer="94"/>
<wire x1="12.7" y1="-7.62" x2="12.7" y2="7.62" width="0.1524" layer="94"/>
<wire x1="12.7" y1="7.62" x2="-17.78" y2="7.62" width="0.1524" layer="94"/>
<wire x1="-10.16" y1="5.08" x2="10.16" y2="5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="5.08" x2="10.16" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="-10.16" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="-10.16" y1="-5.08" x2="-10.16" y2="5.08" width="0.1524" layer="94"/>
</symbol>
<symbol name="DRV8825_BOARD">
<pin name="ENABLE" x="-15.24" y="5.08" length="middle" function="dot"/>
<pin name="M0" x="-15.24" y="2.54" length="middle" direction="in"/>
<pin name="M1" x="-15.24" y="0" length="middle"/>
<pin name="M2" x="-15.24" y="-2.54" length="middle"/>
<pin name="RESET" x="-15.24" y="-5.08" length="middle" function="dot"/>
<pin name="SLEEP" x="-15.24" y="-7.62" length="middle" function="dot"/>
<pin name="STEP" x="-15.24" y="-10.16" length="middle"/>
<pin name="DIR" x="-15.24" y="-12.7" length="middle"/>
<pin name="VMOT" x="15.24" y="15.24" length="middle" rot="R180"/>
<pin name="GNDMOT" x="15.24" y="12.7" length="middle" rot="R180"/>
<pin name="B2" x="15.24" y="2.54" length="middle" direction="out" rot="R180"/>
<pin name="B1" x="15.24" y="0" length="middle" direction="out" rot="R180"/>
<pin name="A2" x="15.24" y="-2.54" length="middle" direction="out" rot="R180"/>
<pin name="A1" x="15.24" y="-5.08" length="middle" direction="out" rot="R180"/>
<pin name="FAIL" x="15.24" y="-12.7" length="middle" direction="out" function="dot" rot="R180"/>
<pin name="GNDLOGIC" x="15.24" y="10.16" length="middle" rot="R180"/>
<wire x1="-10.16" y1="-15.24" x2="10.16" y2="-15.24" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-15.24" x2="10.16" y2="17.78" width="0.1524" layer="94"/>
<wire x1="10.16" y1="17.78" x2="-10.16" y2="17.78" width="0.1524" layer="94"/>
<wire x1="-10.16" y1="17.78" x2="-10.16" y2="-15.24" width="0.1524" layer="94"/>
<text x="-7.62" y="-17.78" size="1.778" layer="95">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="STEPPER_GAUGE">
<gates>
<gate name="G$1" symbol="STEPPER_GAUGE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="STEPPER_GAUGE">
<connects>
<connect gate="G$1" pin="A1" pad="P$3 P$4"/>
<connect gate="G$1" pin="A2" pad="P$1 P$2"/>
<connect gate="G$1" pin="B1" pad="P$7 P$8"/>
<connect gate="G$1" pin="B2" pad="P$5 P$6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="OLED_0.9">
<gates>
<gate name="OLED_0.9" symbol="OLED_0.9" x="0" y="0"/>
</gates>
<devices>
<device name="" package="OLED_0.9">
<connects>
<connect gate="OLED_0.9" pin="GND" pad="GND"/>
<connect gate="OLED_0.9" pin="SCL" pad="SCL"/>
<connect gate="OLED_0.9" pin="SDA" pad="SDA"/>
<connect gate="OLED_0.9" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DRV8825_BOARD">
<gates>
<gate name="G$1" symbol="DRV8825_BOARD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DRV8255_BOARD">
<connects>
<connect gate="G$1" pin="A1" pad="P$14"/>
<connect gate="G$1" pin="A2" pad="P$13"/>
<connect gate="G$1" pin="B1" pad="P$12"/>
<connect gate="G$1" pin="B2" pad="P$11"/>
<connect gate="G$1" pin="DIR" pad="P$8"/>
<connect gate="G$1" pin="ENABLE" pad="P$1"/>
<connect gate="G$1" pin="FAIL" pad="P$15"/>
<connect gate="G$1" pin="GNDLOGIC" pad="P$16"/>
<connect gate="G$1" pin="GNDMOT" pad="P$10"/>
<connect gate="G$1" pin="M0" pad="P$2"/>
<connect gate="G$1" pin="M1" pad="P$3"/>
<connect gate="G$1" pin="M2" pad="P$4"/>
<connect gate="G$1" pin="RESET" pad="P$5"/>
<connect gate="G$1" pin="SLEEP" pad="P$6"/>
<connect gate="G$1" pin="STEP" pad="P$7"/>
<connect gate="G$1" pin="VMOT" pad="P$9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ArduinoNanoV30">
<packages>
<package name="ARDUINO_NANO">
<description>&lt;b&gt;Arduino Nano V3.0&lt;/b&gt;&lt;br&gt;
&lt;p&gt;The Nano was designed and is being produced by Gravitech.&lt;br&gt;

&lt;a href="http://www.gravitech.us/arna30wiatp.html"&gt;Gravitech Arduino Nano V3.0&lt;/a&gt;&lt;/p&gt;</description>
<hole x="-22.86" y="-7.62" drill="1.778"/>
<pad name="1" x="-20.32" y="-7.62" drill="0.8" shape="square"/>
<pad name="2" x="-17.78" y="-7.62" drill="0.8"/>
<pad name="3" x="-15.24" y="-7.62" drill="0.8"/>
<pad name="4" x="-12.7" y="-7.62" drill="0.8"/>
<pad name="5" x="-10.16" y="-7.62" drill="0.8"/>
<pad name="6" x="-7.62" y="-7.62" drill="0.8"/>
<pad name="7" x="-5.08" y="-7.62" drill="0.8"/>
<pad name="8" x="-2.54" y="-7.62" drill="0.8"/>
<pad name="9" x="0" y="-7.62" drill="0.8"/>
<pad name="10" x="2.54" y="-7.62" drill="0.8"/>
<pad name="11" x="5.08" y="-7.62" drill="0.8"/>
<pad name="12" x="7.62" y="-7.62" drill="0.8"/>
<pad name="13" x="10.16" y="-7.62" drill="0.8"/>
<pad name="14" x="12.7" y="-7.62" drill="0.8"/>
<pad name="15" x="15.24" y="-7.62" drill="0.8"/>
<pad name="16" x="15.24" y="7.62" drill="0.8"/>
<pad name="17" x="12.7" y="7.62" drill="0.8"/>
<pad name="18" x="10.16" y="7.62" drill="0.8"/>
<pad name="19" x="7.62" y="7.62" drill="0.8"/>
<pad name="20" x="5.08" y="7.62" drill="0.8"/>
<pad name="21" x="2.54" y="7.62" drill="0.8"/>
<pad name="22" x="0" y="7.62" drill="0.8"/>
<pad name="23" x="-2.54" y="7.62" drill="0.8"/>
<pad name="24" x="-5.08" y="7.62" drill="0.8"/>
<pad name="25" x="-7.62" y="7.62" drill="0.8"/>
<pad name="26" x="-10.16" y="7.62" drill="0.8"/>
<pad name="27" x="-12.7" y="7.62" drill="0.8"/>
<pad name="28" x="-15.24" y="7.62" drill="0.8"/>
<pad name="29" x="-17.78" y="7.62" drill="0.8"/>
<pad name="30" x="-20.32" y="7.62" drill="0.8"/>
<hole x="-22.86" y="7.62" drill="1.778"/>
<hole x="17.78" y="7.62" drill="1.778"/>
<hole x="17.78" y="-7.62" drill="1.778"/>
<wire x1="-24.13" y1="8.89" x2="19.05" y2="8.89" width="0.127" layer="21"/>
<wire x1="19.05" y1="8.89" x2="19.05" y2="3.81" width="0.127" layer="21"/>
<wire x1="19.05" y1="3.81" x2="19.05" y2="-3.81" width="0.127" layer="21"/>
<wire x1="19.05" y1="-3.81" x2="19.05" y2="-8.89" width="0.127" layer="21"/>
<wire x1="19.05" y1="-8.89" x2="-24.13" y2="-8.89" width="0.127" layer="21"/>
<wire x1="-24.13" y1="-8.89" x2="-24.13" y2="2.54" width="0.127" layer="21"/>
<wire x1="-24.13" y1="2.54" x2="-24.13" y2="8.89" width="0.127" layer="21"/>
<wire x1="-24.13" y1="2.54" x2="-25.4" y2="2.54" width="0.127" layer="21"/>
<wire x1="-25.4" y1="2.54" x2="-25.4" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-2.54" x2="-19.05" y2="2.54" width="0.127" layer="21"/>
<wire x1="-19.05" y1="2.54" x2="-24.13" y2="2.54" width="0.127" layer="21"/>
<wire x1="-19.05" y1="-2.54" x2="-25.4" y2="-2.54" width="0.127" layer="21"/>
<text x="-17.78" y="0" size="1.27" layer="21" font="vector">&gt;NAME</text>
<text x="-17.78" y="-2.54" size="1.27" layer="21" font="vector">&gt;VALUE</text>
<circle x="0" y="0" radius="1.79605" width="0.127" layer="21"/>
<text x="3.81" y="-1.27" size="0.8128" layer="21" font="vector" rot="R90">Reset</text>
<text x="-20.32" y="-6.35" size="1.016" layer="21" font="vector">1</text>
<text x="-17.78" y="3.81" size="0.6096" layer="21" font="vector" rot="R180">Mini-B USB</text>
<wire x1="19.05" y1="3.81" x2="13.97" y2="3.81" width="0.127" layer="21"/>
<wire x1="13.97" y1="3.81" x2="13.97" y2="-3.81" width="0.127" layer="21"/>
<wire x1="13.97" y1="-3.81" x2="19.05" y2="-3.81" width="0.127" layer="21"/>
<circle x="17.78" y="-2.54" radius="0.8" width="0.127" layer="21"/>
<circle x="17.78" y="0" radius="0.8" width="0.127" layer="21"/>
<circle x="17.78" y="2.54" radius="0.8" width="0.127" layer="21"/>
<circle x="15.24" y="2.54" radius="0.8" width="0.127" layer="21"/>
<circle x="17.78" y="0" radius="0.8" width="0.127" layer="21"/>
<circle x="15.24" y="0" radius="0.8" width="0.127" layer="21"/>
<circle x="15.24" y="-2.54" radius="0.8" width="0.127" layer="21"/>
<text x="12.7" y="1.27" size="0.8128" layer="21" font="vector" rot="SR270">ICSP</text>
</package>
</packages>
<symbols>
<symbol name="ARDUINO_NANO">
<description>&lt;b&gt;Arduino Nano V3.0&lt;/b&gt;&lt;br&gt;&lt;br&gt;

&lt;b&gt;Overview:&lt;/b&gt;&lt;br&gt;

The Arduino Nano is a small, complete, and breadboard-friendly board based on the ATmega328 (Arduino Nano 3.x) or ATmega168 (Arduino Nano 2.x). It has more or less the same functionality of the Arduino Duemilanove, but in a different package. It lacks only a DC power jack, and works with a Mini-B USB cable instead of a standard one.&lt;br&gt;
The Nano was designed and is being produced by Gravitech.&lt;br&gt;&lt;br&gt;

&lt;b&gt;Specifications:&lt;/b&gt;
&lt;table border="1" style="width:auto"&gt;
  &lt;tr&gt;
    &lt;td&gt;Microcontroller&lt;/td&gt;
    &lt;td&gt;Atmel ATmega168 or ATmega328&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Operating Voltage (logic level)&lt;/td&gt;
    &lt;td&gt;5 V&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Input Voltage (recommended)&lt;/td&gt;
    &lt;td&gt;7-12 V&lt;/td&gt;
  &lt;tr&gt;
    &lt;td&gt;Input Voltage (limits)&lt;/td&gt;
    &lt;td&gt;6-20 V&lt;/td&gt;		
  &lt;tr&gt;
    &lt;td&gt;Digital I/O Pins&lt;/td&gt;
    &lt;td&gt;14 (of which 6 provide PWM output)&lt;/td&gt;		
  &lt;tr&gt;
    &lt;td&gt;Analog Input Pins&lt;/td&gt;
    &lt;td&gt;8&lt;/td&gt;
  &lt;tr&gt;
    &lt;td&gt;DC Current per I/O Pin&lt;/td&gt;
    &lt;td&gt;40 mA&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Flash Memory&lt;/td&gt;
    &lt;td&gt;16 KB (ATmega168) or 32 KB (ATmega328) of which 2 KB used by bootloader&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;SRAM&lt;/td&gt;
    &lt;td&gt;1 KB (ATmega168) or 2 KB (ATmega328)&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;EEPROM&lt;/td&gt;
    &lt;td&gt;512 bytes (ATmega168) or 1 KB (ATmega328)&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Clock Speed&lt;/td&gt;
    &lt;td&gt;16 MHz&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Dimensions&lt;/td&gt;
    &lt;td&gt;0.73" x 1.70"&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Length&lt;/td&gt;
    &lt;td&gt;45 mm&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Width&lt;/td&gt;
    &lt;td&gt;18 mm&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Weigth&lt;/td&gt;
    &lt;td&gt;5 g&lt;/td&gt;
  &lt;/tr&gt;
&lt;/table&gt;
&lt;br&gt;&lt;br&gt;

&lt;b&gt;Power:&lt;/b&gt;&lt;br&gt;

The Arduino Nano can be powered via the Mini-B USB connection, 6-20V unregulated external power supply (pin 30), or 5V regulated external power supply (pin 27).&lt;br&gt;
The power source is automatically selected to the highest voltage source.&lt;br&gt;&lt;br&gt;

&lt;b&gt;Memory:&lt;/b&gt;&lt;br&gt;

The ATmega168 has 16 KB of flash memory for storing code (of which 2 KB is used for the bootloader); the ATmega328 has 32 KB, (also with 2 KB used for the bootloader).&lt;br&gt;
The ATmega168 has 1 KB of SRAM and 512 bytes of EEPROM (which can be read and written with the EEPROM library); the ATmega328 has 2 KB of SRAM and 1 KB of EEPROM.&lt;br&gt;&lt;br&gt;

&lt;b&gt;Input and Output:&lt;/b&gt;&lt;br&gt;

Each of the 14 digital pins on the Nano can be used as an input or output, using pinMode(), digitalWrite(), and digitalRead() functions.&lt;br&gt;
They operate at 5 volts.&lt;br&gt;
Each pin can provide or receive a maximum of 40 mA and has an internal pull-up resistor (disconnected by default) of 20-50 kOhms. In addition, some pins have specialized functions.&lt;br&gt;&lt;br&gt;

&lt;a href="https://www.arduino.cc/en/Main/ArduinoBoardNano"&gt;Visit Arduino - ArduinoBoardNano&lt;/a&gt;</description>
<wire x1="-15.24" y1="-25.4" x2="-15.24" y2="15.24" width="0.254" layer="94"/>
<wire x1="-15.24" y1="15.24" x2="-5.08" y2="15.24" width="0.254" layer="94"/>
<wire x1="-5.08" y1="15.24" x2="5.08" y2="15.24" width="0.254" layer="94"/>
<wire x1="5.08" y1="15.24" x2="15.24" y2="15.24" width="0.254" layer="94"/>
<wire x1="15.24" y1="15.24" x2="15.24" y2="-25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="-25.4" x2="-15.24" y2="-25.4" width="0.254" layer="94"/>
<pin name="TX1" x="-20.32" y="12.7" length="middle"/>
<pin name="RX0" x="-20.32" y="10.16" length="middle"/>
<pin name="!RESET@1" x="-20.32" y="7.62" length="middle" direction="in" function="dot"/>
<pin name="GND@1" x="-20.32" y="5.08" length="middle" direction="pwr"/>
<pin name="D2" x="-20.32" y="2.54" length="middle"/>
<pin name="D3" x="-20.32" y="0" length="middle"/>
<pin name="D4" x="-20.32" y="-2.54" length="middle"/>
<pin name="D5" x="-20.32" y="-5.08" length="middle"/>
<pin name="D6" x="-20.32" y="-7.62" length="middle"/>
<pin name="D7" x="-20.32" y="-10.16" length="middle"/>
<pin name="D8" x="-20.32" y="-12.7" length="middle"/>
<pin name="D9" x="-20.32" y="-15.24" length="middle"/>
<pin name="D10" x="-20.32" y="-17.78" length="middle"/>
<pin name="D11" x="-20.32" y="-20.32" length="middle"/>
<pin name="D12" x="-20.32" y="-22.86" length="middle"/>
<pin name="D13" x="20.32" y="-22.86" length="middle" rot="R180"/>
<pin name="3V3" x="20.32" y="-20.32" length="middle" direction="out" rot="R180"/>
<pin name="AREF" x="20.32" y="-17.78" length="middle" direction="in" rot="R180"/>
<pin name="A0" x="20.32" y="-15.24" length="middle" rot="R180"/>
<pin name="A1" x="20.32" y="-12.7" length="middle" rot="R180"/>
<pin name="A2" x="20.32" y="-10.16" length="middle" rot="R180"/>
<pin name="A3" x="20.32" y="-7.62" length="middle" rot="R180"/>
<pin name="A4" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="A5" x="20.32" y="-2.54" length="middle" rot="R180"/>
<pin name="A6" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="A7" x="20.32" y="2.54" length="middle" rot="R180"/>
<pin name="5V" x="20.32" y="5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="!RESET@2" x="20.32" y="7.62" length="middle" direction="in" function="dot" rot="R180"/>
<pin name="GND@2" x="20.32" y="10.16" length="middle" direction="pwr" rot="R180"/>
<pin name="VIN" x="20.32" y="12.7" length="middle" direction="pwr" rot="R180"/>
<wire x1="2.54" y1="-20.32" x2="-2.54" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-20.32" x2="-2.54" y2="-26.67" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-26.67" x2="2.54" y2="-26.67" width="0.254" layer="94"/>
<wire x1="2.54" y1="-26.67" x2="2.54" y2="-20.32" width="0.254" layer="94"/>
<text x="-2.54" y="-17.78" size="1.4224" layer="94" font="vector">Mini-B
 USB</text>
<circle x="0" y="0" radius="2.54" width="0.254" layer="94"/>
<text x="-2.54" y="-7.62" size="1.4224" layer="94" font="vector">RESET
BUTTON</text>
<text x="-15.24" y="-30.48" size="1.778" layer="95">&gt;NAME</text>
<text x="-15.24" y="-33.02" size="1.778" layer="96">&gt;VALUE</text>
<wire x1="-5.08" y1="15.24" x2="-5.08" y2="10.16" width="0.254" layer="94"/>
<wire x1="-5.08" y1="10.16" x2="5.08" y2="10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="10.16" x2="5.08" y2="15.24" width="0.254" layer="94"/>
<text x="-2.54" y="7.62" size="1.6764" layer="94" font="vector">ICSP</text>
<circle x="-2.54" y="11.43" radius="0.762" width="0.254" layer="94"/>
<circle x="0" y="13.97" radius="0.762" width="0.254" layer="94"/>
<circle x="2.54" y="13.97" radius="0.762" width="0.254" layer="94"/>
<circle x="-2.54" y="13.97" radius="0.762" width="0.254" layer="94"/>
<circle x="2.54" y="11.43" radius="0.762" width="0.254" layer="94"/>
<circle x="0" y="11.43" radius="0.762" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="ARDUINO_NANO" prefix="ARDUINO_NANO" uservalue="yes">
<description>&lt;b&gt;Arduino Nano V3.0&lt;/b&gt;&lt;br&gt;&lt;br&gt;

&lt;b&gt;Overview:&lt;/b&gt;&lt;br&gt;

&lt;p&gt;The Arduino Nano is a small, complete, and breadboard-friendly board based on the ATmega328 (Arduino Nano 3.x) or ATmega168 (Arduino Nano 2.x). &lt;br&gt;It has more or less the same functionality of the Arduino Duemilanove, but in a different package.&lt;br&gt;
It lacks only a DC power jack, and works with a Mini-B USB cable instead of a standard one.&lt;br&gt;
The Nano was designed and is being produced by Gravitech.&lt;/p&gt;&lt;br&gt;

&lt;b&gt;Specifications:&lt;/b&gt;
&lt;table border="1" style="width:auto"&gt;
  &lt;tr&gt;
    &lt;td&gt;Microcontroller&lt;/td&gt;
    &lt;td&gt;Atmel ATmega168 or ATmega328&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Operating Voltage (logic level)&lt;/td&gt;
    &lt;td&gt;5 V&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Input Voltage (recommended)&lt;/td&gt;
    &lt;td&gt;7-12 V&lt;/td&gt;
  &lt;tr&gt;
    &lt;td&gt;Input Voltage (limits)&lt;/td&gt;
    &lt;td&gt;6-20 V&lt;/td&gt;		
  &lt;tr&gt;
    &lt;td&gt;Digital I/O Pins&lt;/td&gt;
    &lt;td&gt;14 (of which 6 provide PWM output)&lt;/td&gt;		
  &lt;tr&gt;
    &lt;td&gt;Analog Input Pins&lt;/td&gt;
    &lt;td&gt;8&lt;/td&gt;
  &lt;tr&gt;
    &lt;td&gt;DC Current per I/O Pin&lt;/td&gt;
    &lt;td&gt;40 mA&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Flash Memory&lt;/td&gt;
    &lt;td&gt;16 KB (ATmega168) or 32 KB (ATmega328) of which 2 KB used by bootloader&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;SRAM&lt;/td&gt;
    &lt;td&gt;1 KB (ATmega168) or 2 KB (ATmega328)&lt;/td&gt;		
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;EEPROM&lt;/td&gt;
    &lt;td&gt;512 bytes (ATmega168) or 1 KB (ATmega328)&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Clock Speed&lt;/td&gt;
    &lt;td&gt;16 MHz&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Dimensions&lt;/td&gt;
    &lt;td&gt;0.73" x 1.70"&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Length&lt;/td&gt;
    &lt;td&gt;45 mm&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Width&lt;/td&gt;
    &lt;td&gt;18 mm&lt;/td&gt;
  &lt;/tr&gt;
  &lt;tr&gt;
    &lt;td&gt;Weigth&lt;/td&gt;
    &lt;td&gt;5 g&lt;/td&gt;
  &lt;/tr&gt;
&lt;/table&gt;
&lt;br&gt;&lt;br&gt;

&lt;b&gt;Power:&lt;/b&gt;&lt;br&gt;

&lt;p&gt;The Arduino Nano can be powered via the Mini-B USB connection, 6-20V unregulated external power supply (pin 30), or 5V regulated external power supply (pin 27).&lt;br&gt;
The power source is automatically selected to the highest voltage source.&lt;/p&gt;&lt;br&gt;

&lt;b&gt;Memory:&lt;/b&gt;&lt;br&gt;

&lt;p&gt;The ATmega168 has 16 KB of flash memory for storing code (of which 2 KB is used for the bootloader); the ATmega328 has 32 KB, (also with 2 KB used for the bootloader).&lt;br&gt;
The ATmega168 has 1 KB of SRAM and 512 bytes of EEPROM (which can be read and written with the EEPROM library); the ATmega328 has 2 KB of SRAM and 1 KB of EEPROM.&lt;/p&gt;&lt;br&gt;

&lt;b&gt;Input and Output:&lt;/b&gt;&lt;br&gt;

&lt;p&gt;Each of the 14 digital pins on the Nano can be used as an input or output, using pinMode(), digitalWrite(), and digitalRead() functions.&lt;br&gt;
They operate at 5 volts.&lt;br&gt;
Each pin can provide or receive a maximum of 40 mA and has an internal pull-up resistor (disconnected by default) of 20-50 kOhms. In addition, some pins have specialized functions.&lt;/p&gt;&lt;br&gt;

&lt;a href="https://www.arduino.cc/en/Main/ArduinoBoardNano"&gt;Visit Arduino - ArduinoBoardNano&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="ARDUINO_NANO" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ARDUINO_NANO">
<connects>
<connect gate="G$1" pin="!RESET@1" pad="18"/>
<connect gate="G$1" pin="!RESET@2" pad="13"/>
<connect gate="G$1" pin="3V3" pad="2"/>
<connect gate="G$1" pin="5V" pad="12"/>
<connect gate="G$1" pin="A0" pad="4"/>
<connect gate="G$1" pin="A1" pad="5"/>
<connect gate="G$1" pin="A2" pad="6"/>
<connect gate="G$1" pin="A3" pad="7"/>
<connect gate="G$1" pin="A4" pad="8"/>
<connect gate="G$1" pin="A5" pad="9"/>
<connect gate="G$1" pin="A6" pad="10"/>
<connect gate="G$1" pin="A7" pad="11"/>
<connect gate="G$1" pin="AREF" pad="3"/>
<connect gate="G$1" pin="D10" pad="28"/>
<connect gate="G$1" pin="D11" pad="29"/>
<connect gate="G$1" pin="D12" pad="30"/>
<connect gate="G$1" pin="D13" pad="1"/>
<connect gate="G$1" pin="D2" pad="20"/>
<connect gate="G$1" pin="D3" pad="21"/>
<connect gate="G$1" pin="D4" pad="22"/>
<connect gate="G$1" pin="D5" pad="23"/>
<connect gate="G$1" pin="D6" pad="24"/>
<connect gate="G$1" pin="D7" pad="25"/>
<connect gate="G$1" pin="D8" pad="26"/>
<connect gate="G$1" pin="D9" pad="27"/>
<connect gate="G$1" pin="GND@1" pad="19"/>
<connect gate="G$1" pin="GND@2" pad="14"/>
<connect gate="G$1" pin="RX0" pad="17"/>
<connect gate="G$1" pin="TX1" pad="16"/>
<connect gate="G$1" pin="VIN" pad="15"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2" urn="urn:adsk.eagle:library:372">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="+05V" urn="urn:adsk.eagle:symbol:26987/1" library_version="2">
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="0.635" x2="0" y2="1.905" width="0.1524" layer="94"/>
<circle x="0" y="1.27" radius="1.27" width="0.254" layer="94"/>
<text x="-1.905" y="3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="+12V" urn="urn:adsk.eagle:symbol:26985/1" library_version="2">
<wire x1="0" y1="1.905" x2="0" y2="0.635" width="0.1524" layer="94"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="94"/>
<circle x="0" y="1.27" radius="1.27" width="0.254" layer="94"/>
<text x="-2.54" y="3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="+12V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="0V" urn="urn:adsk.eagle:symbol:26989/1" library_version="2">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.4064" layer="94"/>
<text x="-1.143" y="-2.032" size="1.778" layer="96">&gt;VALUE</text>
<pin name="0V" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+5V" urn="urn:adsk.eagle:component:27032/1" prefix="SUPPLY" library_version="2">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="+5V" symbol="+05V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+12V" urn="urn:adsk.eagle:component:27033/1" prefix="SUPPLY" library_version="2">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="+12V" symbol="+12V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="0V" urn="urn:adsk.eagle:component:27034/1" prefix="SUPPLY" library_version="2">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="0V" symbol="0V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="bike_computer" deviceset="STEPPER_GAUGE" device=""/>
<part name="ARDUINO_NANO1" library="ArduinoNanoV30" deviceset="ARDUINO_NANO" device=""/>
<part name="SUPPLY1" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="SUPPLY2" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="SUPPLY3" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="SUPPLY4" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="SUPPLY5" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="SUPPLY6" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+5V" device=""/>
<part name="SUPPLY7" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY8" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY9" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY10" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY11" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY12" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY13" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY14" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="+12V" device=""/>
<part name="SUPPLY15" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="SUPPLY16" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="SUPPLY17" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="SUPPLY18" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="SUPPLY19" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="SUPPLY20" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="SUPPLY21" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="SUPPLY22" library="supply2" library_urn="urn:adsk.eagle:library:372" deviceset="0V" device=""/>
<part name="U$3" library="bike_computer" deviceset="OLED_0.9" device=""/>
<part name="DRV8825" library="bike_computer" deviceset="DRV8825_BOARD" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="134.62" y="2.54" smashed="yes"/>
<instance part="ARDUINO_NANO1" gate="G$1" x="-12.7" y="12.7" smashed="yes">
<attribute name="NAME" x="-27.94" y="-17.78" size="1.778" layer="95"/>
<attribute name="VALUE" x="-27.94" y="-20.32" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY1" gate="+5V" x="-22.86" y="-35.56" smashed="yes">
<attribute name="VALUE" x="-24.765" y="-32.385" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY2" gate="+5V" x="-12.7" y="-38.1" smashed="yes">
<attribute name="VALUE" x="-14.605" y="-34.925" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY3" gate="+5V" x="91.44" y="-40.64" smashed="yes">
<attribute name="VALUE" x="89.535" y="-37.465" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY4" gate="+5V" x="43.18" y="2.54" smashed="yes">
<attribute name="VALUE" x="41.275" y="5.715" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY5" gate="+5V" x="17.78" y="22.86" smashed="yes">
<attribute name="VALUE" x="15.875" y="26.035" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY6" gate="+5V" x="-15.24" y="-38.1" smashed="yes">
<attribute name="VALUE" x="-17.145" y="-34.925" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY7" gate="+12V" x="53.34" y="-33.02" smashed="yes">
<attribute name="VALUE" x="50.8" y="-29.845" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY8" gate="+12V" x="58.42" y="-33.02" smashed="yes">
<attribute name="VALUE" x="55.88" y="-29.845" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY9" gate="+12V" x="91.44" y="25.4" smashed="yes">
<attribute name="VALUE" x="88.9" y="28.575" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY10" gate="+12V" x="60.96" y="-40.64" smashed="yes">
<attribute name="VALUE" x="58.42" y="-37.465" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY11" gate="+12V" x="50.8" y="-43.18" smashed="yes">
<attribute name="VALUE" x="48.26" y="-40.005" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY12" gate="+12V" x="58.42" y="-48.26" smashed="yes">
<attribute name="VALUE" x="55.88" y="-45.085" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY13" gate="+12V" x="68.58" y="-50.8" smashed="yes">
<attribute name="VALUE" x="66.04" y="-47.625" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY14" gate="+12V" x="71.12" y="-43.18" smashed="yes">
<attribute name="VALUE" x="68.58" y="-40.005" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY15" gate="0V" x="12.7" y="30.48" smashed="yes">
<attribute name="VALUE" x="11.557" y="28.448" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY16" gate="0V" x="20.32" y="-35.56" smashed="yes">
<attribute name="VALUE" x="19.177" y="-37.592" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY17" gate="0V" x="25.4" y="-30.48" smashed="yes">
<attribute name="VALUE" x="24.257" y="-32.512" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY18" gate="0V" x="48.26" y="5.08" smashed="yes">
<attribute name="VALUE" x="47.117" y="3.048" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY19" gate="0V" x="93.98" y="10.16" smashed="yes">
<attribute name="VALUE" x="92.837" y="8.128" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY20" gate="0V" x="30.48" y="-30.48" smashed="yes">
<attribute name="VALUE" x="29.337" y="-32.512" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY21" gate="0V" x="30.48" y="-35.56" smashed="yes">
<attribute name="VALUE" x="29.337" y="-37.592" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY22" gate="0V" x="91.44" y="-50.8" smashed="yes">
<attribute name="VALUE" x="90.297" y="-52.832" size="1.778" layer="96"/>
</instance>
<instance part="U$3" gate="OLED_0.9" x="134.62" y="-40.64" smashed="yes"/>
<instance part="DRV8825" gate="G$1" x="71.12" y="2.54" smashed="yes">
<attribute name="NAME" x="63.5" y="-15.24" size="1.778" layer="95"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="B2"/>
<wire x1="86.36" y1="5.08" x2="116.84" y2="5.08" width="0.1524" layer="91"/>
<pinref part="DRV8825" gate="G$1" pin="B2"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<wire x1="86.36" y1="2.54" x2="109.22" y2="2.54" width="0.1524" layer="91"/>
<wire x1="109.22" y1="2.54" x2="109.22" y2="0" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="B1"/>
<wire x1="109.22" y1="0" x2="116.84" y2="0" width="0.1524" layer="91"/>
<pinref part="DRV8825" gate="G$1" pin="B1"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="86.36" y1="0" x2="106.68" y2="0" width="0.1524" layer="91"/>
<wire x1="106.68" y1="0" x2="106.68" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="A2"/>
<wire x1="106.68" y1="-17.78" x2="132.08" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="132.08" y1="-17.78" x2="132.08" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="DRV8825" gate="G$1" pin="A2"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<wire x1="86.36" y1="-2.54" x2="104.14" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-2.54" x2="104.14" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="A1"/>
<wire x1="104.14" y1="-20.32" x2="137.16" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="137.16" y1="-20.32" x2="137.16" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="DRV8825" gate="G$1" pin="A1"/>
</segment>
</net>
<net name="0V" class="0">
<segment>
<pinref part="SUPPLY19" gate="0V" pin="0V"/>
<wire x1="93.98" y1="12.7" x2="88.9" y2="12.7" width="0.1524" layer="91"/>
<wire x1="88.9" y1="12.7" x2="86.36" y2="12.7" width="0.1524" layer="91"/>
<wire x1="86.36" y1="15.24" x2="88.9" y2="15.24" width="0.1524" layer="91"/>
<wire x1="88.9" y1="15.24" x2="88.9" y2="12.7" width="0.1524" layer="91"/>
<junction x="88.9" y="12.7"/>
<pinref part="DRV8825" gate="G$1" pin="GNDMOT"/>
<pinref part="DRV8825" gate="G$1" pin="GNDLOGIC"/>
</segment>
<segment>
<pinref part="SUPPLY18" gate="0V" pin="0V"/>
<wire x1="48.26" y1="7.62" x2="55.88" y2="7.62" width="0.1524" layer="91"/>
<pinref part="DRV8825" gate="G$1" pin="ENABLE"/>
</segment>
<segment>
<pinref part="ARDUINO_NANO1" gate="G$1" pin="GND@2"/>
<wire x1="7.62" y1="22.86" x2="10.16" y2="22.86" width="0.1524" layer="91"/>
<wire x1="10.16" y1="22.86" x2="10.16" y2="35.56" width="0.1524" layer="91"/>
<wire x1="10.16" y1="35.56" x2="12.7" y2="35.56" width="0.1524" layer="91"/>
<pinref part="SUPPLY15" gate="0V" pin="0V"/>
<wire x1="12.7" y1="35.56" x2="12.7" y2="33.02" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$3" gate="OLED_0.9" pin="GND"/>
<pinref part="SUPPLY22" gate="0V" pin="0V"/>
<wire x1="111.76" y1="-45.72" x2="91.44" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="91.44" y1="-45.72" x2="91.44" y2="-48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+12V" class="0">
<segment>
<pinref part="SUPPLY9" gate="+12V" pin="+12V"/>
<wire x1="86.36" y1="17.78" x2="91.44" y2="17.78" width="0.1524" layer="91"/>
<wire x1="91.44" y1="17.78" x2="91.44" y2="22.86" width="0.1524" layer="91"/>
<pinref part="DRV8825" gate="G$1" pin="VMOT"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="SUPPLY4" gate="+5V" pin="+5V"/>
<wire x1="43.18" y1="0" x2="43.18" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="43.18" y1="-5.08" x2="53.34" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="53.34" y1="-5.08" x2="55.88" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="55.88" y1="-2.54" x2="53.34" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="53.34" y1="-2.54" x2="53.34" y2="-5.08" width="0.1524" layer="91"/>
<junction x="53.34" y="-5.08"/>
<pinref part="DRV8825" gate="G$1" pin="RESET"/>
<pinref part="DRV8825" gate="G$1" pin="SLEEP"/>
</segment>
<segment>
<pinref part="ARDUINO_NANO1" gate="G$1" pin="5V"/>
<pinref part="SUPPLY5" gate="+5V" pin="+5V"/>
<wire x1="7.62" y1="17.78" x2="17.78" y2="17.78" width="0.1524" layer="91"/>
<wire x1="17.78" y1="17.78" x2="17.78" y2="20.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$3" gate="OLED_0.9" pin="VCC"/>
<pinref part="SUPPLY3" gate="+5V" pin="+5V"/>
<wire x1="111.76" y1="-43.18" x2="91.44" y2="-43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="STEP" class="0">
<segment>
<wire x1="55.88" y1="-7.62" x2="43.18" y2="-7.62" width="0.1524" layer="91"/>
<label x="35.56" y="-7.62" size="1.778" layer="95"/>
<pinref part="DRV8825" gate="G$1" pin="STEP"/>
</segment>
<segment>
<pinref part="ARDUINO_NANO1" gate="G$1" pin="D2"/>
<wire x1="-33.02" y1="15.24" x2="-40.64" y2="15.24" width="0.1524" layer="91"/>
<label x="-48.26" y="15.24" size="1.778" layer="95"/>
</segment>
</net>
<net name="DIR" class="0">
<segment>
<wire x1="55.88" y1="-10.16" x2="43.18" y2="-10.16" width="0.1524" layer="91"/>
<label x="35.56" y="-10.16" size="1.778" layer="95"/>
<pinref part="DRV8825" gate="G$1" pin="DIR"/>
</segment>
<segment>
<pinref part="ARDUINO_NANO1" gate="G$1" pin="D3"/>
<wire x1="-33.02" y1="12.7" x2="-40.64" y2="12.7" width="0.1524" layer="91"/>
<label x="-48.26" y="12.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="SDA" class="0">
<segment>
<pinref part="U$3" gate="OLED_0.9" pin="SDA"/>
<wire x1="111.76" y1="-35.56" x2="106.68" y2="-35.56" width="0.1524" layer="91"/>
<label x="99.06" y="-35.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="ARDUINO_NANO1" gate="G$1" pin="A4"/>
<wire x1="7.62" y1="7.62" x2="12.7" y2="7.62" width="0.1524" layer="91"/>
<label x="15.24" y="7.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="SCL" class="0">
<segment>
<pinref part="U$3" gate="OLED_0.9" pin="SCL"/>
<wire x1="111.76" y1="-38.1" x2="106.68" y2="-38.1" width="0.1524" layer="91"/>
<label x="99.06" y="-38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="ARDUINO_NANO1" gate="G$1" pin="A5"/>
<wire x1="7.62" y1="10.16" x2="12.7" y2="10.16" width="0.1524" layer="91"/>
<label x="15.24" y="10.16" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
