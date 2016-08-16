#ifndef exportDialog_XML_H
#define exportDialog_XML_H

//
// exportDialogXML
//

#ifdef MACOSX 

std::string exportDialogXML = 
"<PKVLayout id=\"ID_ROOT\" layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"6\">"
"    <PKArrowTabControl id=\"ID_TAB_CONTROL\" layoutx=\"2\" layouty=\"2\" doubleBuffer=\"true\" icons=\"res|JPEG_64,res|PNG_64,res|PDF_64\" bkgImage=\"res|EXPORT_BKG\" arrowImage=\"res|EXPORT_SEL\">"
"        <PKVLayout id=\"ID_OBJ_31\" margin=\"10\">"
"            <PKLabel id=\"ID_OBJ_30\" maxWidth=\"380\" text=\"PKI18N:Creates a JPEG image from the contents of your document. This image can then be shared on the web or printed with an external program.\" multiline=\"true\" />"
"            <PKHLayout id=\"ID_OBJ_32\" layoutx=\"2\" margin=\"0\" spacing=\"0\">"
"                <PKLabel id=\"ID_OBJ_33\" text=\"PKI18N:JPEG Image size : \"/>"
"                <PKEdit id=\"ID_JPEG_EDIT\" frame=\"99,154,50,19\" layoutx=\"1\" text=\"1000\" type=\"2\"/>"
"                <PKLittleArrows id=\"ID_JPEG_ARROWS\" range=\"100,5000\"/>"
"                <PKLabel id=\"ID_OBJ_34\" text=\"PKI18N: pixels\"/>"
"            </PKHLayout>"
"            <PKHLayout id=\"ID_OBJ_35\" layoutx=\"2\" margin=\"0\" spacing=\"0\">"
"                <PKLabel id=\"ID_OBJ_36\" text=\"PKI18N:JPEG Quality : \"/>"
"                <PKSlider type=\"1\" id=\"ID_JPEG_SLIDER\" frame=\"99,154,120,19\" range=\"0-100\" value=\"80\" layoutx=\"1\" />"
"            </PKHLayout>"
"        </PKVLayout>"
"        <PKVLayout id=\"ID_OBJ_16\" margin=\"10\">"
"            <PKLabel id=\"ID_OBJ_18\" maxWidth=\"380\" text=\"PKI18N:Creates a PNG image from the contents of your document. This image can then be shared on the web or printed with an external program.\" multiline=\"true\" />"
"            <PKHLayout id=\"ID_OBJ_19\" layoutx=\"2\" margin=\"0\" spacing=\"0\">"
"                <PKLabel id=\"ID_OBJ_20\" text=\"PKI18N:PNG Image size : \"/>"
"                <PKEdit id=\"ID_PNG_EDIT\" frame=\"99,154,50,19\" layoutx=\"1\" text=\"1000\" type=\"2\"/>"
"                <PKLittleArrows id=\"ID_PNG_ARROWS\" range=\"100,5000\"/>"
"                <PKLabel id=\"ID_OBJ_24\" text=\"PKI18N: pixels\"/>"
"            </PKHLayout>"
"        </PKVLayout>"
"        <PKVLayout id=\"ID_OBJ_17\">"
"            <PKLabel id=\"ID_OBJ_27\" maxWidth=\"380\" text=\"PKI18N:Creates a PDF file from the contents of your document. This PDF can then be edited or printed with an external program.\" multiline=\"true\"/>"
"        </PKVLayout>"
"    </PKArrowTabControl>"
"    <PKLineControl id=\"ID_LINE\" layoutx=\"2\" color=\"180,180,180,255\"/>"
"    <PKHLayout id=\"ID_OBJ_13\" layoutx=\"2\">"
"        <PKSpacer id=\"ID_OBJ_14\" layoutx=\"2\"/>"
"        <PKButton id=\"ID_BUTTON_CANCEL\" caption=\"PKI18N:Cancel\"/>"
"        <PKButton id=\"ID_BUTTON_EXPORT\" caption=\"PKI18N:Export\" default=\"true\"/>"
"    </PKHLayout>"
"</PKVLayout>";

#else

std::string exportDialogXML = 
"<PKVLayout id=\"ID_ROOT\" layoutx=\"2\" layouty=\"2\" margin=\"0\" spacing=\"6\">"
"    <PKArrowTabControl id=\"ID_TAB_CONTROL\" layoutx=\"2\" layouty=\"2\" doubleBuffer=\"true\" icons=\"res|JPEG_64,res|PNG_64\" bkgImage=\"res|EXPORT_BKG\" arrowImage=\"res|EXPORT_SEL\">"
"        <PKVLayout id=\"ID_OBJ_31\" margin=\"10\">"
"            <PKLabel id=\"ID_OBJ_30\" maxWidth=\"380\" text=\"PKI18N:Creates a JPEG image from the contents of your document. This image can then be shared on the web or printed with an external program.\" multiline=\"true\" />"
"            <PKHLayout id=\"ID_OBJ_32\" layoutx=\"2\" margin=\"0\" spacing=\"0\">"
"                <PKLabel id=\"ID_OBJ_33\" text=\"PKI18N:JPEG Image size : \"/>"
"                <PKEdit id=\"ID_JPEG_EDIT\" frame=\"99,154,50,19\" layoutx=\"1\" text=\"1000\" type=\"2\"/>"
"                <PKLittleArrows id=\"ID_JPEG_ARROWS\" range=\"100,5000\"/>"
"                <PKLabel id=\"ID_OBJ_34\" text=\"PKI18N: pixels\"/>"
"            </PKHLayout>"
"            <PKHLayout id=\"ID_OBJ_35\" layoutx=\"2\" margin=\"0\" spacing=\"0\">"
"                <PKLabel id=\"ID_OBJ_36\" text=\"PKI18N:JPEG Quality : \"/>"
"                <PKSlider type=\"1\" id=\"ID_JPEG_SLIDER\" frame=\"99,154,120,19\" layouty=\"1\" range=\"0-100\" value=\"80\" layoutx=\"1\" />"
"            </PKHLayout>"
"        </PKVLayout>"
"        <PKVLayout id=\"ID_OBJ_16\" margin=\"10\">"
"            <PKLabel id=\"ID_OBJ_18\" maxWidth=\"380\" text=\"PKI18N:Creates a PNG image from the contents of your document. This image can then be shared on the web or printed with an external program.\" multiline=\"true\" />"
"            <PKHLayout id=\"ID_OBJ_19\" layoutx=\"2\" margin=\"0\" spacing=\"0\">"
"                <PKLabel id=\"ID_OBJ_20\" text=\"PKI18N:PNG Image size : \"/>"
"                <PKEdit id=\"ID_PNG_EDIT\" frame=\"99,154,50,19\" layoutx=\"1\" text=\"1000\" type=\"2\"/>"
"                <PKLittleArrows id=\"ID_PNG_ARROWS\" range=\"100,5000\"/>"
"                <PKLabel id=\"ID_OBJ_24\" text=\"PKI18N: pixels\"/>"
"            </PKHLayout>"
"        </PKVLayout>"
"    </PKArrowTabControl>"
"    <PKLineControl id=\"ID_LINE\" layoutx=\"2\" color=\"180,180,180,255\"/>"
"    <PKHLayout id=\"ID_OBJ_13\" layoutx=\"2\">"
"        <PKSpacer id=\"ID_OBJ_14\" layoutx=\"2\"/>"
"        <PKButton id=\"ID_BUTTON_CANCEL\" caption=\"PKI18N:Cancel\"/>"
"        <PKButton id=\"ID_BUTTON_EXPORT\" caption=\"PKI18N:Export\" default=\"true\"/>"
"    </PKHLayout>"
"</PKVLayout>";

#endif // MACOSX


#endif // exportDialog_XML_H
