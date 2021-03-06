//
//
//

#if(defined(WIN32)||defined(LINUX))

std::string chordableWindow_XML = \
"<PKVLayout id=\"ID_ROOT\" layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"0\">"
"  <PKHLayout layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"0\">"
"    <PKVLayout layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"0\">"
"    <PKScrollView id=\"ID_SCROLLVIEW\" layoutx=\"2\" layouty=\"2\" macMargin=\"1\" vScroll=\"true\" >"
"      <ChordableVectorControlRoot id=\"ID_VECTOR_CONTROL_ROOT\" wantFocus=\"true\" layoutx=\"2\" layouty=\"2\" doubleBuffer=\"true\" backColor=\"180, 180, 180, 255\" >"
"        <PKHLayout layoutx=\"2\" layouty=\"2\" margin=\"10\" spacing=\"0\">"
"          <PKSpacer layoutx=\"2\" />"
"          <PKVLayout layouty=\"2\" margin=\"0\" spacing=\"0\">"
"            <PKSpacer type=\"1\" layouty=\"2\" />"
"            <PKBitmapBorderVectorPanel id=\"ID_PAGE_PANEL\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,490,620\" borderWidth=\"16\" sharedVectorEngine=\"true\" "
"               topLeftImage=\"res|TOPLEFT\" topRightImage=\"res|TOPRIGHT\" bottomLeftImage=\"res|BOTTOMLEFT\" bottomRightImage=\"res|BOTTOMRIGHT\" "
"               topStartImage=\"res|TOP_START\" topMiddleImage=\"res|TOP_MIDDLE\" topEndImage=\"res|TOP_END\" "
"               leftStartImage=\"res|LEFT_START\" leftMiddleImage=\"res|LEFT_MIDDLE\" leftEndImage=\"res|LEFT_END\" "
"               rightStartImage=\"res|RIGHT_START\" rightMiddleImage=\"res|RIGHT_MIDDLE\" rightEndImage=\"res|RIGHT_END\" "
"               bottomStartImage=\"res|BOTTOM_START\" bottomMiddleImage=\"res|BOTTOM_MIDDLE\" bottomEndImage=\"res|BOTTOM_END\" >"
"              <PKVLayout layoutx=\"2\" id=\"ID_PAGE_LAYOUT\" margin=\"30\" spacing=\"0\">"
"                <PKSpacer id=\"ID_SPACER_TOP\" layouty=\"1\" frame=\"0,0,0,20\" />"
"                <PKEditableVectorLabel id=\"ID_TITLE_EDIT\" layoutx=\"2\" layouty=\"1\" frame=\"0,0,0,40\" offset=\"5\" sharedVectorEngine=\"true\" bold=\"true\" textColor=\"40,40,40,255\" hoverBackgroundColor=\"0,0,0,0\" defaultTextColor=\"180,180,180,255\" borderColor=\"220,220,220,0\" text=\"\" offset=\"5\" defaultText=\"PKI18N:Title: Click to edit\"/>"
"                <PKEditableVectorLabel id=\"ID_SUBTITLE_EDIT\" layoutx=\"2\" layouty=\"1\" frame=\"0,0,0,20\" offset=\"5\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"70,70,70,255\" hoverBackgroundColor=\"0,0,0,0\" defaultTextColor=\"180,180,180,255\" borderColor=\"220,220,220,0\" text=\"\" offset=\"5\" defaultText=\"PKI18N:Subtitle: Click to edit\"/>"
"                <PKSpacer id=\"ID_SPACER_MIDDLE\" layouty=\"1\" frame=\"0,0,0,20\" />"
"                <PKGridLayout id=\"ID_PAGE_GRID\" margin=\"0\" spacing=\"0\" cols=\"11\" layoutx=\"2\" >"
"                  <PKEditableVectorLabel id=\"ID_CAPO_LABEL\" editable=\"false\" layoutx=\"1\" layouty=\"1\" offset=\"0\" frame=\"0,0,82,32\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"PKI18N:Capo\" sharedVectorEngine=\"true\" defaultText=\"\" />"
"                  <PKEditableVectorLabel id=\"ID_CAPO_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,20\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"1\" defaultText=\"\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_CAPO_SPACER\" frame=\"0,0,5,0\"/>"
"                  <PKImageVectorControl id=\"ID_TEMPO_IMAGE\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,32,32\" image=\"res|QUARTER_NOTE\" sharedVectorEngine=\"true\" />"
"                  <PKEditableVectorLabel id=\"ID_TEMPO_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,20\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"120\" defaultText=\"\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_TEMPO_SPACER\" frame=\"0,0,5,0\"/>"
"                  <PKImageVectorControl id=\"ID_KEY_IMAGE\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,32,32\" image=\"res|KEY\" sharedVectorEngine=\"true\" />"
"                  <PKEditableVectorLabel id=\"ID_KEY_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,26,22\" editable=\"false\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"C\" defaultText=\"\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_KEY_SPACER\" frame=\"0,0,5,0\"/>"
"                  <PKImageVectorControl id=\"ID_TUNING_IMAGE\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,32,32\" image=\"res|TUNING\" sharedVectorEngine=\"true\" />"
"                  <PKEditableVectorLabel id=\"ID_TUNING_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,20\" editable=\"false\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"EADGBE\" defaultText=\"\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_2\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_3\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_4\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_5\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_6\" frame=\"0,0,0,0\"/>"
"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_7\" frame=\"0,0,0,0\"/>"
"                  <PKEditableVectorLabel id=\"ID_TUNING_SUBEDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,10\" editable=\"false\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"120,120,120,255\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"(Standard)\" defaultText=\"\"/>"
"                </PKGridLayout>"
"                <PKSpacer id=\"ID_CHORDS_SPACER\" layouty=\"1\" frame=\"0,0,0,20\" />"
"                <PKHLayout layoutx=\"2\" spacing=\"0\" margin=\"0\">"
"                  <PKSpacer layoutx=\"2\" id=\"ID_CHORD_SPACER_1\" />"
"                  <PKGridLayout id=\"ID_CHORDS_GRID\" margin=\"0\" spacing=\"0\" cols=\"6\" />"
"                  <PKSpacer layoutx=\"2\" id=\"ID_CHORD_SPACER_2\" />"
"                </PKHLayout>"
"                <PKSpacer id=\"ID_SPACER_MIDDLE2\" layouty=\"1\" frame=\"0,0,0,20\" />"
"                <PKGridLayout id=\"ID_BAR_GRID\" margin=\"0\" spacing=\"0\" cols=\"6\" layoutx=\"2\">"
"                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
"                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
"                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
"                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
"                  <AddBarsVectorControl id=\"ID_ADD_BARS\" hidden=\"true\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
"                </PKGridLayout>"
"              </PKVLayout>"
"            </PKBitmapBorderVectorPanel>"
"            <PKSpacer type=\"1\" layouty=\"2\" />"
"          </PKVLayout>"
"          <PKSpacer layoutx=\"2\" />"
"        </PKHLayout>"
"      </ChordableVectorControlRoot>"
"    </PKScrollView>"
"    <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
"    <PKHLayout layoutx=\"2\" margin=\"2\" spacing=\"2\">"
"      <PKSpacer layoutx=\"2\" />"
"      <PKLabel id=\"ID_ZOOM_TEXT\" text=\"PKI18N:Zoom:\" color=\"80,80,80,255\"/>"
"      <PKSlider layoutx=\"1\" layouty=\"1\" frame=\"0,0,100,24\" id=\"ID_ZOOM_SLIDER\" range=\"0-100\" value=\"50\" />"
"    </PKHLayout>"
"    </PKVLayout>"
"    <PKLineControl horizontal=\"false\" layouty=\"2\" layoutx=\"1\" frame=\"0,0,1,0\" color=\"178,178,178,255\" />"
"    <PKArrowTabControl id=\"ID_ICON_TAB\" bkgImage=\"res|BAR\" arrowImage=\"res|BAR_SELECT\" icons=\"res|DOC_SMALL,res|BAR_SMALL\" tooltips=\"PKI18N:Document Properties,Bar Properties\" layouty=\"2\" >"
"      <PKVLayout id=\"ID_ICON_TAB_LAYOUT\" layoutx=\"2\" margin=\"10\" spacing=\"8\">"
"        <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"2\">"
"         <PKLabel id=\"ID_LABEL_TITLE\" layoutx=\"2\" text=\"PKI18N:Title:\" />"
"         <PKEdit  id=\"ID_INSPECTOR_TITLE_EDIT\"  layoutx=\"2\" text=\"\" />"
"        </PKVLayout>"
"        <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"2\">"
"         <PKLabel id=\"ID_LABEL_SUBTITLE\" layoutx=\"2\" text=\"PKI18N:Subtitle:\" />"
"         <PKEdit  id=\"ID_INSPECTOR_SUBTITLE_EDIT\"  layoutx=\"2\" text=\"\" />"
"        </PKVLayout>"
"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
"        <PKVLayout layoutx=\"2\" margin=\"0\">"
"         <PKLabel id=\"ID_LABEL_TUNING\" layoutx=\"2\" text=\"PKI18N:Tuning:\" />"
"         <PKComboBox id=\"ID_TUNING_COMBO\" items=\"\" layoutx=\"2\"/>"
"        </PKVLayout>"
"        <PKCheckBox id=\"ID_INSPECTOR_TUNING_CHECKBOX\" text=\"PKI18N:Show Tuning:\" layoutx=\"2\" />"
"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
"        <PKHLayout margin=\"0\" layoutx=\"2\">"
"          <PKCheckBox id=\"ID_INSPECTOR_CAPO_CHECKBOX\" text=\"PKI18N:Show capo:\" />"
"          <PKHLayout margin=\"0\" spacing=\"6\" layoutx=\"2\" >"
"           <PKEdit id=\"ID_INSPECTOR_CAPO_EDIT\" layoutx=\"2\" text=\"1\" type=\"2\" />"
"           <PKLittleArrows id=\"ID_CAPO_ARROWS\" range=\"1,24\" />"
"          </PKHLayout>"
"        </PKHLayout>"
"        <PKHLayout margin=\"0\" layoutx=\"2\">"
"          <PKCheckBox id=\"ID_INSPECTOR_TEMPO_CHECKBOX\" text=\"PKI18N:Show tempo:\" />"
"          <PKHLayout margin=\"0\" spacing=\"0\" layoutx=\"2\" >"
#ifdef LINUX
"           <PKEdit id=\"ID_INSPECTOR_TEMPO_EDIT\" layoutx=\"1\" frame=\"0,0,60,0\" text=\"120\" type=\"2\" />"
#else
"           <PKEdit id=\"ID_INSPECTOR_TEMPO_EDIT\" layoutx=\"2\" text=\"120\" type=\"2\" />"
#endif
"           <PKLittleArrows id=\"ID_TEMPO_ARROWS\" range=\"1,999\" />"
"          </PKHLayout>"
"        </PKHLayout>"
"        <PKHLayout margin=\"0\" layoutx=\"2\">"
"          <PKCheckBox id=\"ID_INSPECTOR_KEY_CHECKBOX\" text=\"PKI18N:Show key:\"/>"
#ifdef LINUX
"          <PKComboBox id=\"ID_INSPECTOR_KEY_COMBO\" items=\"\" />"
#else
"          <PKComboBox id=\"ID_INSPECTOR_KEY_COMBO\" items=\"\" layoutx=\"2\"/>"
#endif
"        </PKHLayout>"
"        <PKHLayout layoutx=\"2\" margin=\"0\" spacing=\"2\">"
"         <PKLabel text=\"PKI18N:Display\" />"
"         <PKHLayout margin=\"0\" spacing=\"0\">"
"           <PKEdit id=\"ID_NUM_COL_EDIT\" layoutx=\"1\" frame=\"0,0,20,0\" type=\"2\" text=\"6\" />"
"           <PKLittleArrows id=\"ID_COL_ARROWS\" range=\"4,8\" />"
"         </PKHLayout>"
"         <PKLabel text=\"PKI18N: bars per row\"/>"
"        </PKHLayout>"
"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
"        <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"2\">"
"         <PKLabel layoutx=\"2\" text=\"PKI18N:Notes:\"/>"
"         <PKEdit id=\"ID_INSPECTOR_NOTES_EDIT\" multiLine=\"true\" layoutx=\"2\" text=\"\" layouty=\"1\" frame=\"0,0,0,70\" />"
"        </PKVLayout>"
"        <PKCheckBox id=\"ID_INSPECTOR_CHORDS_CHECKBOX\" text=\"PKI18N:Show chord diagrams     \" layoutx=\"2\" />"
"      </PKVLayout>"
"      <PKVLayout layoutx=\"2\" margin=\"10\" spacing=\"8\">"
"        <PKLabel id=\"ID_BAR_LABEL_1\" layoutx=\"2\" text=\"PKI18N:Bar Type:\" />"
"        <PKHLayout margin=\"0\" spacing=\"0\" layoutx=\"2\" >"
"          <PKSpacer layoutx=\"2\" />"
"          <PKSelectorControl id=\"ID_BAR_TYPE_SELECTOR\" normalImage=\"res|BAR_TYPE\" pushedImage=\"res|BAR_TYPE_DOWN\" disabledImage=\"res|BAR_TYPE_DISABLED\" selection=\"0\" numItems=\"5\" offsets=\"0,39,79,119,159,199\"/>"
"          <PKSpacer layoutx=\"2\" />"
"        </PKHLayout>"
"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
"        <PKLabel id=\"ID_BAR_LABEL_2\" layoutx=\"2\" text=\"PKI18N:Chords:\" />"
"        <PKHLayout id=\"ID_BAR_LAYOUT_1\" layoutx=\"2\" margin=\"2\">"
"          <PKImageView id=\"ID_BAR_IMAGE_1\" image=\"res|CHORD_4BARS_1\" />"
"          <PKLabel id=\"ID_BAR_CHORD_1\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
"          <PKButton id=\"ID_CHORD_BUTTON_1\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,22\" />"
"        </PKHLayout>"
"        <PKHLayout id=\"ID_BAR_LAYOUT_2\" layoutx=\"2\" margin=\"2\">"
"          <PKImageView id=\"ID_BAR_IMAGE_2\" image=\"res|CHORD_4BARS_2\" />"
"          <PKLabel id=\"ID_BAR_CHORD_2\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
"          <PKButton id=\"ID_CHORD_BUTTON_2\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,22\"  />"
"        </PKHLayout>"
"        <PKHLayout id=\"ID_BAR_LAYOUT_3\" layoutx=\"2\" margin=\"2\">"
"          <PKImageView id=\"ID_BAR_IMAGE_3\" image=\"res|CHORD_4BARS_3\" />"
"          <PKLabel id=\"ID_BAR_CHORD_3\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
"          <PKButton id=\"ID_CHORD_BUTTON_3\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,22\" />"
"        </PKHLayout>"
"        <PKHLayout id=\"ID_BAR_LAYOUT_4\" layoutx=\"2\" margin=\"2\">"
"          <PKImageView id=\"ID_BAR_IMAGE_4\" image=\"res|CHORD_4BARS_4\" />"
"          <PKLabel id=\"ID_BAR_CHORD_4\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
"          <PKButton id=\"ID_CHORD_BUTTON_4\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,22\" />"
"        </PKHLayout>"
"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
"        <PKLabel id=\"ID_BAR_LABEL_3\" layoutx=\"2\" text=\"PKI18N:Markups:\" />"
"        <PKHLayout margin=\"0\" layoutx=\"2\">"
"          <PKHLayout margin=\"0\" spacing=\"4\">"
"            <PKBitmapToggleButton id=\"ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON\"  normalImage=\"res|BAR_REPEAT_LEFT\"  hoverImage=\"res|BAR_REPEAT_LEFT_OVER\"  pushedImage=\"res|BAR_REPEAT_LEFT_DOWN\"  toggledNormalImage=\"res|BAR_REPEAT_LEFT_TOGGLED\"  toggledHoverImage=\"res|BAR_REPEAT_LEFT_TOGGLED_OVER\"  toggledPushedImage=\"res|BAR_REPEAT_LEFT_TOGGLED_DOWN\"  />"
"            <PKBitmapToggleButton id=\"ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON\" normalImage=\"res|BAR_REPEAT_RIGHT\" hoverImage=\"res|BAR_REPEAT_RIGHT_OVER\" pushedImage=\"res|BAR_REPEAT_RIGHT_DOWN\" toggledNormalImage=\"res|BAR_REPEAT_RIGHT_TOGGLED\" toggledHoverImage=\"res|BAR_REPEAT_RIGHT_TOGGLED_OVER\" toggledPushedImage=\"res|BAR_REPEAT_RIGHT_TOGGLED_DOWN\" />"
"          </PKHLayout>"
"          <PKSpacer layoutx=\"2\" />"
"          <PKCheckBox id=\"ID_BAR_SECTION_MARKUP_CHECK\" text=\"\" />"
"          <PKImageView image=\"res|MARKUP\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,60,18\" />"
"          <PKHLayout margin=\"0\" spacing=\"0\">"
"            <PKEdit id=\"ID_BAR_SECTION_NUMBER_EDIT\" type=\"2\" layoutx=\"1\" frame=\"0,0,22,0\" text=\"1\" enabled=\"false\" />"
"            <PKLittleArrows id=\"ID_BAR_SECTION_ARROWS\" range=\"1,10\" enabled=\"false\" />"
"          </PKHLayout>"
"        </PKHLayout>"
"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
"        <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"2\">"
"         <PKLabel id=\"ID_BAR_LABEL_4\" layoutx=\"2\" text=\"PKI18N:Header:\" />"
"         <PKEdit id=\"ID_BAR_HEADER_EDIT\" layoutx=\"2\" text=\"\" />"
"        </PKVLayout>"
"      </PKVLayout>"
"    </PKArrowTabControl>"
"  </PKHLayout>"
"</PKVLayout>";

#endif

#if(defined(MACOSX))

std::string chordableWindow_XML  =  "<PKVLayout id=\"ID_ROOT\" layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"0\">"
                                    "  <PKHLayout layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"0\">"
                                    "    <PKVLayout layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"0\">"
                                    "    <PKScrollView id=\"ID_SCROLLVIEW\" layoutx=\"2\" layouty=\"2\" macMargin=\"1\" vScroll=\"true\" >"
                                    "      <ChordableVectorControlRoot wantFocus=\"true\" id=\"ID_VECTOR_CONTROL_ROOT\" layoutx=\"2\" layouty=\"2\" backColor=\"180, 180, 180, 255\" >"
                                    "        <PKHLayout layoutx=\"2\" layouty=\"2\" margin=\"10\" spacing=\"0\">"
                                    "          <PKSpacer layoutx=\"2\" />"
                                    "          <PKVLayout layouty=\"2\" margin=\"0\" spacing=\"0\">"
                                    "            <PKSpacer type=\"1\" layouty=\"2\" />"
                                    "            <PKBitmapBorderVectorPanel id=\"ID_PAGE_PANEL\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,490,620\" borderWidth=\"16\" sharedVectorEngine=\"true\" "
                                    "               topLeftImage=\"res|TOPLEFT\" topRightImage=\"res|TOPRIGHT\" bottomLeftImage=\"res|BOTTOMLEFT\" bottomRightImage=\"res|BOTTOMRIGHT\" "
                                    "               topStartImage=\"res|TOP_START\" topMiddleImage=\"res|TOP_MIDDLE\" topEndImage=\"res|TOP_END\" "
                                    "               leftStartImage=\"res|LEFT_START\" leftMiddleImage=\"res|LEFT_MIDDLE\" leftEndImage=\"res|LEFT_END\" "
                                    "               rightStartImage=\"res|RIGHT_START\" rightMiddleImage=\"res|RIGHT_MIDDLE\" rightEndImage=\"res|RIGHT_END\" "
                                    "               bottomStartImage=\"res|BOTTOM_START\" bottomMiddleImage=\"res|BOTTOM_MIDDLE\" bottomEndImage=\"res|BOTTOM_END\">"
                                    "              <PKVLayout id=\"ID_PAGE_LAYOUT\" margin=\"40\" spacing=\"5\" >"
                                    "                <PKSpacer id=\"ID_SPACER_TOP\" layouty=\"1\" frame=\"0,0,0,20\" />"
                                    "                <PKEditableVectorLabel id=\"ID_TITLE_EDIT\" layoutx=\"2\" layouty=\"1\" frame=\"0,0,0,40\" offset=\"5\" sharedVectorEngine=\"true\" bold=\"true\" textColor=\"40,40,40,255\" hoverBackgroundColor=\"0,0,0,0\" text=\"\" borderColor=\"220,220,220,0\" defaultText=\"PKI18N:Title: Click to edit\"/>"
                                    "                <PKEditableVectorLabel id=\"ID_SUBTITLE_EDIT\" layoutx=\"2\" layouty=\"1\" frame=\"0,0,0,20\" offset=\"5\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"70,70,70,255\" hoverBackgroundColor=\"0,0,0,0\" text=\"\" borderColor=\"220,220,220,0\" defaultText=\"PKI18N:Subtitle: Click to edit\"/>"
                                    "                <PKSpacer id=\"ID_SPACER_MIDDLE\" layouty=\"1\" frame=\"0,0,0,20\" />"
									"                <PKGridLayout id=\"ID_PAGE_GRID\" margin=\"0\" spacing=\"0\" cols=\"11\" layoutx=\"2\" >"
									"                  <PKEditableVectorLabel id=\"ID_CAPO_LABEL\" editable=\"false\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,82,32\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"PKI18N:Capo\" sharedVectorEngine=\"true\" defaultText=\"\" />"
									"                  <PKEditableVectorLabel id=\"ID_CAPO_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,20\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"1\" defaultText=\"\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_CAPO_SPACER\" frame=\"0,0,5,0\"/>"
									"                  <PKImageVectorControl id=\"ID_TEMPO_IMAGE\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,32,32\" image=\"res|QUARTER_NOTE\" sharedVectorEngine=\"true\" />"
									"                  <PKEditableVectorLabel id=\"ID_TEMPO_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,20\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"120\" defaultText=\"\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_TEMPO_SPACER\" frame=\"0,0,5,0\"/>"
									"                  <PKImageVectorControl id=\"ID_KEY_IMAGE\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,32,32\" image=\"res|KEY\" sharedVectorEngine=\"true\" />"
									"                  <PKEditableVectorLabel id=\"ID_KEY_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,26,22\" editable=\"false\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"C\" defaultText=\"\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_KEY_SPACER\" frame=\"0,0,5,0\"/>"
									"                  <PKImageVectorControl id=\"ID_TUNING_IMAGE\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,32,32\" image=\"res|TUNING\" sharedVectorEngine=\"true\" />"
									"                  <PKEditableVectorLabel id=\"ID_TUNING_EDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,20\" editable=\"false\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"10,10,10,255\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"EADGBE\" defaultText=\"\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_1\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_2\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_3\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_4\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_5\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_6\" frame=\"0,0,0,0\"/>"
									"                  <PKSpacer layoutx=\"1\" id=\"ID_SUB_SPACER_7\" frame=\"0,0,0,0\"/>"
									"                  <PKEditableVectorLabel id=\"ID_TUNING_SUBEDIT\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,40,10\" editable=\"false\" offset=\"2\" sharedVectorEngine=\"true\" bold=\"false\" textColor=\"120,120,120,255\" hoverBackgroundColor=\"0,0,0,0\" hoverBorderColor=\"0,0,0,0\" borderColor=\"0,0,0,0\" text=\"(Standard)\" defaultText=\"\"/>"
									"                </PKGridLayout>"
									"                <PKSpacer id=\"ID_CHORDS_SPACER\" layouty=\"1\" frame=\"0,0,0,20\" />"
									"                <PKHLayout layoutx=\"2\" spacing=\"0\" margin=\"0\">"
									"                  <PKSpacer layoutx=\"2\" id=\"ID_CHORD_SPACER_1\" />"
									"                  <PKGridLayout id=\"ID_CHORDS_GRID\" margin=\"0\" spacing=\"0\" cols=\"6\" />"
									"                  <PKSpacer layoutx=\"2\" id=\"ID_CHORD_SPACER_2\" />"
									"                </PKHLayout>"
									"                <PKSpacer id=\"ID_SPACER_MIDDLE2\" layouty=\"1\" frame=\"0,0,0,20\" />"
                                    "                <PKGridLayout id=\"ID_BAR_GRID\" margin=\"0\" spacing=\"0\" cols=\"6\" layoutx=\"2\">"
                                    "                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
                                    "                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
                                    "                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
                                    "                  <BarViewVectorControl layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
                                    "                  <AddBarsVectorControl id=\"ID_ADD_BARS\" hidden=\"true\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,80,50\" sharedVectorEngine=\"true\" />"
                                    "                </PKGridLayout>"
                                    "              </PKVLayout>"
                                    "            </PKBitmapBorderVectorPanel>"
                                    "            <PKSpacer type=\"1\" layouty=\"2\" />"
                                    "          </PKVLayout>"
                                    "          <PKSpacer layoutx=\"2\" />"
                                    "        </PKHLayout>"
                                    "      </ChordableVectorControlRoot>"
                                    "    </PKScrollView>"
                                    "    <PKLineControl layoutx=\"2\" color=\"190,190,190,255\"/>"
                                    "    <PKHLayout layoutx=\"2\" margin=\"5\" spacing=\"2\">"
                                    "      <PKSpacer layoutx=\"2\" />"
                                    "      <PKLabel id=\"ID_ZOOM_TEXT\" text=\"PKI18N:Zoom:\" color=\"80,80,80,255\"/>"
                                    "      <PKSlider layoutx=\"1\" layouty=\"1\" frame=\"0,0,100,20\" id=\"ID_ZOOM_SLIDER\" range=\"0-100\" value=\"50\" />"
                                    "    </PKHLayout>"
                                    "    </PKVLayout>"
									"    <PKLineControl horizontal=\"false\" layouty=\"2\" layoutx=\"1\" frame=\"0,0,1,0\" color=\"128,128,128,255\" />"
                                    "    <PKArrowTabControl id=\"ID_ICON_TAB\" bkgImage=\"res|BAR\" arrowImage=\"res|BAR_SELECT\" icons=\"res|DOC_SMALL,res|BAR_SMALL\" tooltips=\"PKI18N:Document Properties,Bar Properties\" layouty=\"2\" >"
                                    "      <PKVLayout id=\"ID_ICON_TAB_LAYOUT1\" layoutx=\"2\" margin=\"10\" spacing=\"10\">"
                                    "       <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"4\">"
                                    "        <PKLabel id=\"ID_LABEL_TITLE\" layoutx=\"2\" text=\"PKI18N:Title:\" relativeFontSize=\"-2\" />"
                                    "        <PKEdit  id=\"ID_INSPECTOR_TITLE_EDIT\"  layoutx=\"2\" text=\"\" />"
                                    "       </PKVLayout>"
                                    "       <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"4\">"
                                    "        <PKLabel id=\"ID_LABEL_SUBTITLE\" layoutx=\"2\" text=\"PKI18N:Subtitle:\" relativeFontSize=\"-2\" />"
                                    "        <PKEdit  id=\"ID_INSPECTOR_SUBTITLE_EDIT\"  layoutx=\"2\" text=\"\" />"
                                    "       </PKVLayout>"
									"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
									"        <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"4\" >"
									"         <PKLabel id=\"ID_LABEL_TUNING\" layoutx=\"2\" text=\"PKI18N:Tuning:\" relativeFontSize=\"-2\" />"
									"         <PKComboBox id=\"ID_TUNING_COMBO\" items=\"\" layoutx=\"1\" frame=\"0,0,205,0\" />"
									"        </PKVLayout>"
									"        <PKCheckBox id=\"ID_INSPECTOR_TUNING_CHECKBOX\" text=\"PKI18N:Show Tuning:\" layoutx=\"2\" />"
									"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
									"        <PKHLayout margin=\"0\" layoutx=\"2\">"
									"          <PKCheckBox id=\"ID_INSPECTOR_CAPO_CHECKBOX\" text=\"PKI18N:Show capo:\" />"
									"          <PKHLayout margin=\"0\" spacing=\"6\" layoutx=\"2\" >"
									"           <PKEdit id=\"ID_INSPECTOR_CAPO_EDIT\" layoutx=\"2\" text=\"1\" type=\"2\" />"
									"           <PKLittleArrows id=\"ID_CAPO_ARROWS\" range=\"1,24\" />"
									"          </PKHLayout>"
									"        </PKHLayout>"
									"        <PKHLayout margin=\"0\" layoutx=\"2\">"
                                    "          <PKCheckBox id=\"ID_INSPECTOR_TEMPO_CHECKBOX\" text=\"PKI18N:Show tempo:\" />"
                                    "          <PKHLayout margin=\"0\" spacing=\"6\" layoutx=\"2\" >"
                                    "           <PKEdit id=\"ID_INSPECTOR_TEMPO_EDIT\" layoutx=\"2\" text=\"120\" type=\"2\" />"
                                    "           <PKLittleArrows id=\"ID_TEMPO_ARROWS\" range=\"1,999\" />"
                                    "          </PKHLayout>"
                                    "        </PKHLayout>"
                                    "        <PKHLayout margin=\"0\" layoutx=\"2\">"
                                    "          <PKCheckBox id=\"ID_INSPECTOR_KEY_CHECKBOX\" text=\"PKI18N:Show key:\"/>"
                                    "          <PKComboBox id=\"ID_INSPECTOR_KEY_COMBO\" items=\"\" layoutx=\"2\"/>"
                                    "        </PKHLayout>"
                                    "        <PKHLayout layoutx=\"2\" margin=\"0\" spacing=\"2\">"
                                    "         <PKLabel text=\"PKI18N:Display \" />"
                                    "         <PKHLayout margin=\"0\" spacing=\"6\">"
                                    "           <PKEdit id=\"ID_NUM_COL_EDIT\" layoutx=\"1\" frame=\"0,0,20,0\" type=\"2\" text=\"6\" />"
                                    "           <PKLittleArrows id=\"ID_COL_ARROWS\" range=\"4,8\" />"
                                    "         </PKHLayout>"
                                    "         <PKLabel text=\"PKI18N: bars per row\"/>"
                                    "        </PKHLayout>"
									"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
                                    "       <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"4\">"
                                    "        <PKLabel layoutx=\"2\" text=\"PKI18N:Notes:\" relativeFontSize=\"-2\" />"
                                    "        <PKEdit id=\"ID_INSPECTOR_NOTES_EDIT\" multiLine=\"true\" layoutx=\"2\" text=\"\" layouty=\"1\" frame=\"0,0,0,70\" />"
                                    "       </PKVLayout>"
                                    "        <PKCheckBox id=\"ID_INSPECTOR_CHORDS_CHECKBOX\" layoutx=\"2\" text=\"PKI18N:Show chord diagrams\" />"
                                    "      </PKVLayout>"
                                    "      <PKVLayout id=\"ID_ICON_TAB_LAYOUT2\" layoutx=\"2\" margin=\"10\" spacing=\"10\">"
                                    "        <PKLabel layoutx=\"2\" text=\"PKI18N:Bar Type:\" relativeFontSize=\"-2\" />"
                                    "        <PKHLayout margin=\"0\" spacing=\"0\" layoutx=\"2\" >"
                                    "          <PKSpacer layoutx=\"2\" />"
                                    "          <PKSelectorControl id=\"ID_BAR_TYPE_SELECTOR\" normalImage=\"res|BAR_TYPE\" pushedImage=\"res|BAR_TYPE_DOWN\" disabledImage=\"res|BAR_TYPE_DISABLED\" selection=\"0\" numItems=\"5\" offsets=\"0,39,79,119,159,199\"/>"
                                    "          <PKSpacer layoutx=\"2\" />"
                                    "        </PKHLayout>"
									"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
                                    "        <PKLabel layoutx=\"2\" text=\"PKI18N:Chords:\" relativeFontSize=\"-2\" />"
                                    "        <PKHLayout id=\"ID_BAR_LAYOUT_1\" layoutx=\"2\" margin=\"2\">"
                                    "          <PKImageView id=\"ID_BAR_IMAGE_1\" image=\"res|CHORD_4BARS_1\" />"
                                    "          <PKLabel id=\"ID_BAR_CHORD_1\" relativeFontSize=\"-2\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
                                    "          <PKButton id=\"ID_CHORD_BUTTON_1\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,20\" />"
                                    "        </PKHLayout>"
                                    "        <PKHLayout id=\"ID_BAR_LAYOUT_2\" layoutx=\"2\" margin=\"2\">"
                                    "          <PKImageView id=\"ID_BAR_IMAGE_2\" image=\"res|CHORD_4BARS_2\" />"
                                    "          <PKLabel id=\"ID_BAR_CHORD_2\" relativeFontSize=\"-2\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
                                    "          <PKButton id=\"ID_CHORD_BUTTON_2\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,20\"  />"
                                    "        </PKHLayout>"
                                    "        <PKHLayout id=\"ID_BAR_LAYOUT_3\" layoutx=\"2\" margin=\"2\">"
                                    "          <PKImageView id=\"ID_BAR_IMAGE_3\" image=\"res|CHORD_4BARS_3\" />"
                                    "          <PKLabel id=\"ID_BAR_CHORD_3\" relativeFontSize=\"-2\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
                                    "          <PKButton id=\"ID_CHORD_BUTTON_3\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,20\" />"
                                    "        </PKHLayout>"
                                    "        <PKHLayout id=\"ID_BAR_LAYOUT_1\" layoutx=\"2\" margin=\"2\">"
                                    "          <PKImageView id=\"ID_BAR_IMAGE_4\" image=\"res|CHORD_4BARS_4\" />"
                                    "          <PKLabel id=\"ID_BAR_CHORD_4\" relativeFontSize=\"-2\" text=\"PKI18N:Not Selected\" layoutx=\"2\" />"
                                    "          <PKButton id=\"ID_CHORD_BUTTON_4\" caption=\"PKI18N:Select...\" layouty=\"1\" frame=\"0,0,0,20\" />"
                                    "        </PKHLayout>"
									"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
									"        <PKLabel layoutx=\"2\" text=\"PKI18N:Markups:\" relativeFontSize=\"-2\" />"
									"        <PKHLayout margin=\"0\" layoutx=\"2\" spacing=\"3\">"
									"          <PKHLayout margin=\"0\" spacing=\"4\">"
									"            <PKBitmapToggleButton id=\"ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON\"  normalImage=\"res|BAR_REPEAT_LEFT\"  hoverImage=\"res|BAR_REPEAT_LEFT_OVER\"  pushedImage=\"res|BAR_REPEAT_LEFT_DOWN\"  toggledNormalImage=\"res|BAR_REPEAT_LEFT_TOGGLED\"  toggledHoverImage=\"res|BAR_REPEAT_LEFT_TOGGLED_OVER\"  toggledPushedImage=\"res|BAR_REPEAT_LEFT_TOGGLED_DOWN\"  />"
									"            <PKBitmapToggleButton id=\"ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON\" normalImage=\"res|BAR_REPEAT_RIGHT\" hoverImage=\"res|BAR_REPEAT_RIGHT_OVER\" pushedImage=\"res|BAR_REPEAT_RIGHT_DOWN\" toggledNormalImage=\"res|BAR_REPEAT_RIGHT_TOGGLED\" toggledHoverImage=\"res|BAR_REPEAT_RIGHT_TOGGLED_OVER\" toggledPushedImage=\"res|BAR_REPEAT_RIGHT_TOGGLED_DOWN\" />"
									"          </PKHLayout>"
									"          <PKSpacer layoutx=\"2\" />"
									"          <PKCheckBox id=\"ID_BAR_SECTION_MARKUP_CHECK\" text=\"\" />"
									"          <PKImageView image=\"res|MARKUP\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,60,18\" />"
									"          <PKHLayout margin=\"0\" spacing=\"0\">"
									"            <PKEdit id=\"ID_BAR_SECTION_NUMBER_EDIT\" type=\"2\" layoutx=\"1\" frame=\"0,0,22,0\" text=\"1\" enabled=\"false\" />"
									"            <PKLittleArrows id=\"ID_BAR_SECTION_ARROWS\" range=\"1,10\" enabled=\"false\" />"
									"          </PKHLayout>"
									"        </PKHLayout>"
									"        <PKLineControl layoutx=\"2\" color=\"220,220,220,255\" />"
									"        <PKVLayout layoutx=\"2\" margin=\"0\" spacing=\"2\">"
									"         <PKLabel id=\"ID_BAR_LABEL_4\" layoutx=\"2\" text=\"PKI18N:Header:\" />"
									"         <PKEdit id=\"ID_BAR_HEADER_EDIT\" layoutx=\"2\" text=\"\" />"
									"        </PKVLayout>"
									"      </PKVLayout>"
                                    "    </PKArrowTabControl>"
                                    "  </PKHLayout>"
                                    "</PKVLayout>";
#endif

