//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef ChordablesPreferences_XML_H
#define ChordablesPreferences_XML_H

//
// ChordablesPreferencesXML
//

std::string ChordablesPreferencesXML = 
"<PKVLayout id=\"ID_ROOT\" layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"0\">"
"    <PKPanelControl id=\"ID_OBJ_0\" layoutx=\"2\" borderColor=\"0,0,0,0\" borderSize=\"0\">"
"        <PKHLayout id=\"ID_OBJ_1\" layoutx=\"2\" margin=\"0\">"
"            <PKSpacer layoutx=\"1\" frame=\"0,10,0,0\" />"
"            <PKVLayout id=\"ID_HEADER_LAYOUT\" layoutx=\"2\">"
"                <PKSpacer id=\"ID_SP1\"/>"
"                <PKLabel id=\"ID_HEADER\" layoutx=\"2\" layouty=\"2\" text=\"PKI18N:Options\" fontName=\"Arial\" color=\"90,90,130,255\" bold=\"true\" relativeFontSize=\"+5\"/>"
"                <PKSpacer id=\"ID_SP2\"/>"
"            </PKVLayout>"
"            <PKImageView id=\"ID_OBJ_4\" image=\"res|HEADER\"/>"
"        </PKHLayout>"
"    </PKPanelControl>"
"    <PKLineControl id=\"ID_OBJ_3\" layoutx=\"2\" color=\"200,200,200,255\"/>"
"    <PKHLayout id=\"ID_MAIN\" layoutx=\"2\" layouty=\"2\" margin=\"30\" spacing=\"10\">"
"        <PKImageView id=\"ID_OBJ_10\" image=\"res|GLOBE\"/>"
"        <PKVLayout id=\"ID_OBJ_11\" margin=\"0\">"
"            <PKLabel id=\"ID_LANG\" text=\"PKI18N:Please select your preferred language:\"/>"
"            <PKComboBox id=\"ID_LANGUAGE_COMBO\" layoutx=\"2\" items=\"\" />"
"        </PKVLayout>"
"    </PKHLayout>"
"    <PKLineControl id=\"ID_OBJ_6\" layoutx=\"2\" color=\"210,210,210,255\"/>"
"    <PKHLayout id=\"ID_BOTTOM\" layoutx=\"2\">"
"        <PKSpacer id=\"ID_OBJ_8\" layoutx=\"2\"/>"
"        <PKButton id=\"ID_CLOSE\" caption=\"PKI18N:Close\" default=\"true\"/>"
"    </PKHLayout>"
"</PKVLayout>";

#endif // ChordablesPreferences_XML_H
