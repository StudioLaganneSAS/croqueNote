
//
// XML for the Chord Library Dialog
// 

std::string xml =   "<PKVLayout spacing=\"0\" margin=\"0\">"
/*
                    " <PKGradientPanel layoutx=\"2\" borderSize=\"0\" backgroundColor1=\"255,255,255,255\" backgroundColor2=\"245,245,245,255\">" 
                    "  <PKHLayout margin=\"15\" spacing=\"0\">"
                    "   <PKImageView id=\"ID_ICON\" image=\"res|GUITAR\" />"
                    "   <PKLabel id=\"ID_TITLE\" text=\"PKI18N: Chord Library\" fontName=\"Arial\" bold=\"true\" relativeFontSize=\"+8\" />"
                    "   <PKSpacer type=\"0\" layoutx=\"2\" />"

// SEARCH BAR - REMOVED
//						"   <PKVLayout margin=\"0\" spacing=\"0\">"
//                      "    <PKStretchEdit layoutx=\"1\" frame=\"20, 0, 155, 30\" normalImage=\"res|SEARCH\" stretchOffset=\"60\" offsetTop=\"11\" offsetLeft=\"30\" offsetRight=\"28\" offsetBottom=\"4\" text=\"\"/>"		
//						"    <PKLabel relativeSize=\"-2\" color=\"150,150,150,255\" text=\"PKI18N:Quick Search\"/>"
//						"   </PKVLayout>"
// SEARCH BAR - REMOVED

				    "  </PKHLayout>"
                    " </PKGradientPanel>"
                    " <PKLineControl layoutx=\"2\" color=\"210,210,210,255\" />"
*/
                    " <PKHLayout margin=\"10\" spacing=\"15\" layoutx=\"2\">"
                    "   <PKVLayout margin=\"0\" spacing=\"4\">"
					"    <PKLabel text=\"PKI18N:Root Note:\" layoutx=\"2\" />"
					"    <PKHLayout margin=\"0\" spacing=\"5\">"
                    "     <PKHLayout margin=\"0\" spacing=\"0\">"
                    "      <PKStretchToggleButton id=\"ID_NOTE_C\" preventToggleOff=\"true\" fontName=\"Arial\" fontSize=\"11\" bold=\"true\" text=\"C\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,44,50\" textOffset=\"2\" stretchOffset=\"12\" normalImage=\"res|TOP_NORMAL\" hoverImage=\"res|TOP_HOVER\" pushedImage=\"res|TOP_CLICKED\" toggledNormalImage=\"res|TOP_TOGGLED_NORMAL\" toggledHoverImage=\"res|TOP_TOGGLED_HOVER\" toggledPushedImage=\"res|TOP_TOGGLED_CLICKED\" />"
                    "      <PKStretchToggleButton id=\"ID_NOTE_D\" preventToggleOff=\"true\" fontName=\"Arial\" fontSize=\"11\" bold=\"true\" text=\"D\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,44,50\" textOffset=\"2\" stretchOffset=\"12\" normalImage=\"res|MID_NORMAL\" hoverImage=\"res|MID_HOVER\" pushedImage=\"res|MID_CLICKED\" toggledNormalImage=\"res|MID_TOGGLED_NORMAL\" toggledHoverImage=\"res|MID_TOGGLED_HOVER\" toggledPushedImage=\"res|MID_TOGGLED_CLICKED\" />"
                    "      <PKStretchToggleButton id=\"ID_NOTE_E\" preventToggleOff=\"true\" fontName=\"Arial\" fontSize=\"11\" bold=\"true\" text=\"E\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,44,50\" textOffset=\"2\" stretchOffset=\"12\" normalImage=\"res|MID_NORMAL\" hoverImage=\"res|MID_HOVER\" pushedImage=\"res|MID_CLICKED\" toggledNormalImage=\"res|MID_TOGGLED_NORMAL\" toggledHoverImage=\"res|MID_TOGGLED_HOVER\" toggledPushedImage=\"res|MID_TOGGLED_CLICKED\" />"
                    "      <PKStretchToggleButton id=\"ID_NOTE_F\" preventToggleOff=\"true\" fontName=\"Arial\" fontSize=\"11\" bold=\"true\" text=\"F\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,44,50\" textOffset=\"2\" stretchOffset=\"12\" normalImage=\"res|MID_NORMAL\" hoverImage=\"res|MID_HOVER\" pushedImage=\"res|MID_CLICKED\" toggledNormalImage=\"res|MID_TOGGLED_NORMAL\" toggledHoverImage=\"res|MID_TOGGLED_HOVER\" toggledPushedImage=\"res|MID_TOGGLED_CLICKED\" />"
                    "      <PKStretchToggleButton id=\"ID_NOTE_G\" preventToggleOff=\"true\" fontName=\"Arial\" fontSize=\"11\" bold=\"true\" text=\"G\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,44,50\" textOffset=\"2\" stretchOffset=\"12\" normalImage=\"res|MID_NORMAL\" hoverImage=\"res|MID_HOVER\" pushedImage=\"res|MID_CLICKED\" toggledNormalImage=\"res|MID_TOGGLED_NORMAL\" toggledHoverImage=\"res|MID_TOGGLED_HOVER\" toggledPushedImage=\"res|MID_TOGGLED_CLICKED\" />"
                    "      <PKStretchToggleButton id=\"ID_NOTE_A\" preventToggleOff=\"true\" fontName=\"Arial\" fontSize=\"11\" bold=\"true\" text=\"A\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,44,50\" textOffset=\"2\" stretchOffset=\"12\" normalImage=\"res|MID_NORMAL\" hoverImage=\"res|MID_HOVER\" pushedImage=\"res|MID_CLICKED\" toggledNormalImage=\"res|MID_TOGGLED_NORMAL\" toggledHoverImage=\"res|MID_TOGGLED_HOVER\" toggledPushedImage=\"res|MID_TOGGLED_CLICKED\" />"
                    "      <PKStretchToggleButton id=\"ID_NOTE_B\" preventToggleOff=\"true\" fontName=\"Arial\" fontSize=\"11\" bold=\"true\" text=\"B\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,44,50\" textOffset=\"2\" stretchOffset=\"12\" normalImage=\"res|BTM_NORMAL\" hoverImage=\"res|BTM_HOVER\" pushedImage=\"res|BTM_CLICKED\" toggledNormalImage=\"res|BTM_TOGGLED_NORMAL\" toggledHoverImage=\"res|BTM_TOGGLED_HOVER\" toggledPushedImage=\"res|BTM_TOGGLED_CLICKED\" />"
                    "     </PKHLayout>"
                    "     <PKVLayout margin=\"0\" spacing=\"6\">"
                    "      <PKStretchToggleButton id=\"ID_SHARP\" fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"#\" layoutx=\"1\" frame=\"0,0,22,0\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
                    "      <PKStretchToggleButton id=\"ID_FLAT\"  fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"b\" layoutx=\"1\" frame=\"0,0,22,0\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
                    "     </PKVLayout>"
                    "    </PKHLayout>"
					"    <PKGridLayout cols=\"3\" margin=\"0\" layoutx=\"2\" spacing=\"4\">"
					"      <PKLabel text=\"PKI18N:Alterations:\" layoutx=\"2\" />"
					"      <PKSpacer layoutx=\"1\" frame=\"0,0,8,0\"/>"
					"      <PKLabel text=\"PKI18N:Bass:\" layoutx=\"2\" />"
					"      <PKHLayout margin=\"0\" layoutx=\"2\" spacing=\"8\" >"
					"       <PKHLayout margin=\"0\" layoutx=\"2\" spacing=\"4\">"
                    "        <PKStretchToggleButton id=\"ID_5PLUS\"  fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"5+\" layoutx=\"1\" frame=\"0,0,32,0\" disabledColor=\"128,128,128,255\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" disabledImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
                    "        <PKStretchToggleButton id=\"ID_5MINUS\" fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"5-\" layoutx=\"1\" frame=\"0,0,32,0\" disabledColor=\"128,128,128,255\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" disabledImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
					"       </PKHLayout>"
					"       <PKHLayout margin=\"0\" layoutx=\"2\" spacing=\"4\">"
                    "        <PKStretchToggleButton id=\"ID_9PLUS\"  fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"9+\" layoutx=\"1\" frame=\"0,0,32,0\" disabledColor=\"128,128,128,255\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" disabledImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
                    "        <PKStretchToggleButton id=\"ID_9MINUS\" fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"9-\" layoutx=\"1\" frame=\"0,0,32,0\" disabledColor=\"128,128,128,255\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" disabledImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
					"       </PKHLayout>"
					"       <PKHLayout margin=\"0\" layoutx=\"2\" spacing=\"4\">"
                    "        <PKStretchToggleButton id=\"ID_13PLUS\"  fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"13+\" layoutx=\"1\" frame=\"0,0,32,0\" disabledColor=\"128,128,128,255\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" disabledImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
                    "        <PKStretchToggleButton id=\"ID_13MINUS\" fontName=\"Arial\" fontSize=\"9\" bold=\"true\" text=\"13-\" layoutx=\"1\" frame=\"0,0,32,0\" disabledColor=\"128,128,128,255\" textOffset=\"1\" stretchOffset=\"12\" normalImage=\"res|SQR_NORMAL\" disabledImage=\"res|SQR_NORMAL\" hoverImage=\"res|SQR_HOVER\" pushedImage=\"res|SQR_CLICKED\" toggledNormalImage=\"res|SQR_TOGGLED_NORMAL\" toggledHoverImage=\"res|SQR_TOGGLED_HOVER\" toggledPushedImage=\"res|SQR_TOGGLED_CLICKED\" />"
					"       </PKHLayout>"
					"      </PKHLayout>"
					"      <PKSpacer layoutx=\"1\" frame=\"0,0,8,0\"/>"
					"      <PKComboBox id=\"ID_BASS\" items=\"C,D,E,F,G,A,B\" layoutx=\"1\" frame=\"0,0,100,0\"/>"
					"    </PKGridLayout>"
					"    <PKSpacer layouty=\"1\" frame=\"0,0,0,4\" />"
					"    <PKHLayout margin=\"0\" layoutx=\"2\">"
					"      <PKCheckBox id=\"ID_ALLOW_OPEN\" text=\"PKI18N:Look for more variations using open strings\"/>"
					"      <PKSpacer layoutx=\"2\"/>"
					"    </PKHLayout>"
					"   </PKVLayout>"
                    "   <PKVLayout margin=\"0\" spacing=\"4\" layouty=\"2\" layoutx=\"2\" >"
					"    <PKLabel text=\"PKI18N:Chord Type:\" layoutx=\"2\" />"
                    "    <PKListBox id=\"ID_CHORD_TYPES\" layouty=\"2\" layoutx=\"2\" alwaysScroll=\"true\" />"
					"   </PKVLayout>"
                    " </PKHLayout>"
                    " <PKLineControl layoutx=\"2\" color=\"200,200,200,255\" />"
                    " <PKHLayout margin=\"10\" spacing=\"10\" layoutx=\"2\">"
					"  <PKPanelControl layouty=\"2\" borderSize=\"1\" borderColor=\"200,200,200,255\" backgroundColor=\"245,245,245,255\">"
					"   <PKVLayout margin=\"8\" layoutx=\"2\" layouty=\"2\" spacing=\"10\">"
					"     <PKLabel id=\"ID_SMALL_NAME\" color=\"120,120,120,255\" bold=\"true\" align=\"center\" layoutx=\"2\" fontSize=\"12\" text=\"CMaj\"/>"
					"     <PKGridLayout spacing=\"4\" margin=\"2\" layoutx=\"2\" layouty=\"2\" cols=\"2\">"
					"      <PKLabel id=\"ID_LABEL_HEADER_1\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" text=\"XXXXXX:\" />"
					"      <PKLabel id=\"ID_LABEL_NOTE_1\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" align=\"right\" text=\"XXXb\" />"
					"      <PKLabel id=\"ID_LABEL_HEADER_2\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" text=\"XXXXXX:\" />"
					"      <PKLabel id=\"ID_LABEL_NOTE_2\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" align=\"right\" text=\"XXXb\" />"
					"      <PKLabel id=\"ID_LABEL_HEADER_3\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" text=\"XXXXXX:\" />"
					"      <PKLabel id=\"ID_LABEL_NOTE_3\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" align=\"right\" text=\"XXXb\" />"
					"      <PKLabel id=\"ID_LABEL_HEADER_4\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" text=\"XXXXXX:\" />"
					"      <PKLabel id=\"ID_LABEL_NOTE_4\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" align=\"right\" text=\"XXXb\" />"
					"      <PKLabel id=\"ID_LABEL_HEADER_5\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" text=\"XXXXXX:\" />"
					"      <PKLabel id=\"ID_LABEL_NOTE_5\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" align=\"right\" text=\"XXXb\" />"
					"      <PKLabel id=\"ID_LABEL_HEADER_6\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" text=\"XXXXXX:\" />"
					"      <PKLabel id=\"ID_LABEL_NOTE_6\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" align=\"right\" text=\"XXXb\" />"
					"      <PKLabel id=\"ID_LABEL_HEADER_7\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" text=\"XXXXXX:\" />"
					"      <PKLabel id=\"ID_LABEL_NOTE_7\" fixedSize=\"true\" color=\"50,50,50,255\" layoutx=\"2\" align=\"right\" text=\"XXXb\" />"
					"     </PKGridLayout>"
					"   </PKVLayout>"
					"  </PKPanelControl>"
                    "  <PKScrollView id=\"ID_SCROLL_VIEW\" vScroll=\"true\" layoutx=\"1\" layouty=\"1\" frame=\"0,0,330,180\" backgroundColor=\"255,255,255,255\">"
					"   <PKVectorControlRoot id=\"ID_VECTOR_ROOT\" doubleBuffer=\"true\" layoutx=\"2\" layouty=\"2\">"
                    "    <PKGridLayout id=\"ID_CHORD_GRID\" margin=\"6\" spacing=\"2\" cols=\"5\" layoutx=\"2\" layouty=\"2\">"
                    "    </PKGridLayout>"
					"   </PKVectorControlRoot>"
                    "  </PKScrollView>"
                    "  <PKPanelControl layoutx=\"2\" margin=\"15\" borderSize=\"3\" borderColor=\"100,150,205,255\" backgroundColor=\"255,255,255,255\">"
                    "   <PKVLayout layoutx=\"2\" spacing=\"10\">"
                    "     <PKHLayout layoutx=\"2\" margin=\"5\">"
                    "      <PKLabel layoutx=\"2\" align=\"center\" id=\"CHORD_NAME\" fontName=\"Arial\" text=\"CMaj\" bold=\"true\" fontSize=\"16\"/>"
                    "     </PKHLayout>"
					"    <PKVectorControlRoot id=\"CHORD_DIAGRAM_ROOT\" doubleBuffer=\"true\" >"   
                    "     <PKChordDiagramVectorUI id=\"CHORD_DIAGRAM\" sharedVectorEngine=\"true\" minHeight=\"130\" backColor=\"255,255,255,255\"/>"
					"    </PKVectorControlRoot>"
					"   </PKVLayout>"
                    "  </PKPanelControl>"
                    " </PKHLayout>"
                    " <PKLineControl layoutx=\"2\" color=\"200,200,200,255\" />"
                    " <PKHLayout layoutx=\"2\" margin=\"10\">"
                    "  <PKLabel id=\"ID_TUNING_LABEL\" text=\"PKI18N:Tuning:\" />"
#ifdef MACOSX
					"  <PKComboBox id=\"ID_TUNING\" items=\"\" layoutx=\"1\" frame=\"0,0,250,0\" />"
#else
					"  <PKComboBox id=\"ID_TUNING\" items=\"\" />"
#endif
                    "  <PKSpacer type=\"0\" layoutx=\"2\"/>"
                    "  <PKButton id=\"ID_CHOOSE\" caption=\"PKI18N:Choose this Chord\" default=\"true\" />" 
                    "  <PKButton id=\"ID_CANCEL\" caption=\"PKI18N:Cancel\"/>" 
                    " </PKHLayout>"
                    "</PKVLayout>";
