#include "QTextFormat.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QBrush.hpp"
#include "QPen.hpp"
#include "QColor.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QVector.hpp"
#include "../Qt5Core/QMap.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "QTextLength.hpp"
#include "QTextCharFormat.hpp"
#include "QTextBlockFormat.hpp"
#include "../Qt5Core/QFlags.hpp"

int QTextFormat_setProperty(lua_State* const state)
{
    return 0;
}

namespace lua {

void QTextFormat_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["background"] = &QTextFormat::background;
    mt["boolProperty"] = &QTextFormat::boolProperty;
    mt["brushProperty"] = &QTextFormat::brushProperty;
    mt["clearBackground"] = &QTextFormat::clearBackground;
    mt["clearForeground"] = &QTextFormat::clearForeground;
    mt["clearProperty"] = &QTextFormat::clearProperty;
    mt["colorProperty"] = &QTextFormat::colorProperty;
    mt["doubleProperty"] = &QTextFormat::doubleProperty;
    mt["foreground"] = &QTextFormat::foreground;
    mt["hasProperty"] = &QTextFormat::hasProperty;
    mt["intProperty"] = &QTextFormat::intProperty;
    mt["isBlockFormat"] = &QTextFormat::isBlockFormat;
    mt["isCharFormat"] = &QTextFormat::isCharFormat;
    mt["isEmpty"] = &QTextFormat::isEmpty;
    mt["isFrameFormat"] = &QTextFormat::isFrameFormat;
    mt["isImageFormat"] = &QTextFormat::isImageFormat;
    mt["isListFormat"] = &QTextFormat::isListFormat;
    mt["isTableCellFormat"] = &QTextFormat::isTableCellFormat;
    mt["isTableFormat"] = &QTextFormat::isTableFormat;
    mt["isValid"] = &QTextFormat::isValid;
    mt["layoutDirection"] = &QTextFormat::layoutDirection;
    mt["lengthProperty"] = &QTextFormat::lengthProperty;
    mt["lengthVectorProperty"] = &QTextFormat::lengthVectorProperty;
    mt["merge"] = &QTextFormat::merge;
    mt["objectIndex"] = &QTextFormat::objectIndex;
    mt["objectType"] = &QTextFormat::objectType;
    mt["penProperty"] = &QTextFormat::penProperty;
    mt["properties"] = &QTextFormat::properties;
    mt["property"] = &QTextFormat::property;
    mt["propertyCount"] = &QTextFormat::propertyCount;
    mt["setBackground"] = &QTextFormat::setBackground;
    mt["setForeground"] = &QTextFormat::setForeground;
    mt["setLayoutDirection"] = &QTextFormat::setLayoutDirection;
    mt["setObjectIndex"] = &QTextFormat::setObjectIndex;
    mt["setObjectType"] = &QTextFormat::setObjectType;
    mt["setProperty"] = QTextFormat_setProperty;
    mt["stringProperty"] = &QTextFormat::stringProperty;
    mt["swap"] = &QTextFormat::swap;
    mt["toBlockFormat"] = &QTextFormat::toBlockFormat;
    mt["toCharFormat"] = &QTextFormat::toCharFormat;
    QTextFrameFormat    toFrameFormat() const
    QTextImageFormat    toImageFormat() const
    QTextListFormat     toListFormat() const
    QTextTableCellFormat    toTableCellFormat() const
    QTextTableFormat    toTableFormat() const
    mt["type"] = &QTextFormat::type;
}

} // namespace lua

int QTextFormat_new(lua_State* const state)
{
    // QTextFormat()
    // QTextFormat(int type)
    // QTextFormat(const QTextFormat & other)
    lua::make<QTextFormat>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QTextFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextFormat"] = lua::value::table;
    env["QTextFormat"]["new"] = QTextFormat_new;
    auto t = env["QTextFormat"];

    // enum QTextFormat::FormatType
    t["InvalidFormat"] = QTextFormat::InvalidFormat;
    t["BlockFormat"] = QTextFormat::BlockFormat;
    t["CharFormat"] = QTextFormat::CharFormat;
    t["ListFormat"] = QTextFormat::ListFormat;
    t["FrameFormat"] = QTextFormat::FrameFormat;
    t["UserFormat"] = QTextFormat::UserFormat;

    // enum QTextFormat::ObjectTypes
    t["NoObject"] = QTextFormat::NoObject;
    t["ImageObject"] = QTextFormat::ImageObject;
    t["TableObject"] = QTextFormat::TableObject;
    t["TableCellObject"] = QTextFormat::TableCellObject;
    t["UserObject"] = QTextFormat::UserObject;


    // enum QTextFormat::PageBreakFlag
    t["PageBreakFlags"] = lua::QFlags_new<QTextFormat::PageBreakFlags>;
    t["PageBreak_Auto"] = QTextFormat::PageBreak_Auto;
    t["PageBreak_AlwaysBefore"] = QTextFormat::PageBreak_AlwaysBefore;
    t["PageBreak_AlwaysAfter"] = QTextFormat::PageBreak_AlwaysAfter;

    // enum QTextFormat::Property
    t["ObjectIndex"] = QTextFormat::ObjectIndex;
    t["CssFloat"] = QTextFormat::CssFloat;
    t["LayoutDirection"] = QTextFormat::LayoutDirection;
    t["OutlinePen"] = QTextFormat::OutlinePen;
    t["ForegroundBrush"] = QTextFormat::ForegroundBrush;
    t["BackgroundBrush"] = QTextFormat::BackgroundBrush;
    t["BackgroundImageUrl"] = QTextFormat::BackgroundImageUrl;
    t["BlockAlignment"] = QTextFormat::BlockAlignment;
    t["BlockTopMargin"] = QTextFormat::BlockTopMargin;
    t["BlockBottomMargin"] = QTextFormat::BlockBottomMargin;
    t["BlockLeftMargin"] = QTextFormat::BlockLeftMargin;
    t["BlockRightMargin"] = QTextFormat::BlockRightMargin;
    t["TextIndent"] = QTextFormat::TextIndent;
    t["TabPositions"] = QTextFormat::TabPositions;
    t["BlockIndent"] = QTextFormat::BlockIndent;
    t["LineHeight"] = QTextFormat::LineHeight;
    t["LineHeightType"] = QTextFormat::LineHeightType;
    t["BlockNonBreakableLines"] = QTextFormat::BlockNonBreakableLines;
    t["BlockTrailingHorizontalRulerWidth"] = QTextFormat::BlockTrailingHorizontalRulerWidth;
    t["FontFamily"] = QTextFormat::FontFamily;
    t["FontPointSize"] = QTextFormat::FontPointSize;
    t["FontPixelSize"] = QTextFormat::FontPixelSize;
    t["FontSizeAdjustment"] = QTextFormat::FontSizeAdjustment;
    t["FontFixedPitch"] = QTextFormat::FontFixedPitch;
    t["FontWeight"] = QTextFormat::FontWeight;
    t["FontItalic"] = QTextFormat::FontItalic;
    t["FontUnderline"] = QTextFormat::FontUnderline;
    t["FontOverline"] = QTextFormat::FontOverline;
    t["FontStrikeOut"] = QTextFormat::FontStrikeOut;
    t["FontCapitalization"] = QTextFormat::FontCapitalization;
    t["FontLetterSpacingType"] = QTextFormat::FontLetterSpacingType;
    t["FontLetterSpacing"] = QTextFormat::FontLetterSpacing;
    t["FontWordSpacing"] = QTextFormat::FontWordSpacing;
    t["FontStretch"] = QTextFormat::FontStretch;
    t["FontStyleHint"] = QTextFormat::FontStyleHint;
    t["FontStyleStrategy"] = QTextFormat::FontStyleStrategy;
    t["FontKerning"] = QTextFormat::FontKerning;
    t["FontHintingPreference"] = QTextFormat::FontHintingPreference;
    t["TextUnderlineColor"] = QTextFormat::TextUnderlineColor;
    t["TextVerticalAlignment"] = QTextFormat::TextVerticalAlignment;
    t["TextOutline"] = QTextFormat::TextOutline;
    t["TextUnderlineStyle"] = QTextFormat::TextUnderlineStyle;
    t["TextToolTip"] = QTextFormat::TextToolTip;
    t["IsAnchor"] = QTextFormat::IsAnchor;
    t["AnchorHref"] = QTextFormat::AnchorHref;
    t["AnchorName"] = QTextFormat::AnchorName;
    t["ObjectType"] = QTextFormat::ObjectType;
    t["ListStyle"] = QTextFormat::ListStyle;
    t["ListIndent"] = QTextFormat::ListIndent;
    t["ListNumberPrefix"] = QTextFormat::ListNumberPrefix;
    t["ListNumberSuffix"] = QTextFormat::ListNumberSuffix;
    t["FrameBorder"] = QTextFormat::FrameBorder;
    t["FrameBorderBrush"] = QTextFormat::FrameBorderBrush;
    t["FrameBorderStyle"] = QTextFormat::FrameBorderStyle;
    t["FrameBottomMargin"] = QTextFormat::FrameBottomMargin;
    t["FrameHeight"] = QTextFormat::FrameHeight;
    t["FrameLeftMargin"] = QTextFormat::FrameLeftMargin;
    t["FrameMargin"] = QTextFormat::FrameMargin;
    t["FramePadding"] = QTextFormat::FramePadding;
    t["FrameRightMargin"] = QTextFormat::FrameRightMargin;
    t["FrameTopMargin"] = QTextFormat::FrameTopMargin;
    t["FrameWidth"] = QTextFormat::FrameWidth;
    t["TableCellSpacing"] = QTextFormat::TableCellSpacing;
    t["TableCellPadding"] = QTextFormat::TableCellPadding;
    t["TableColumns"] = QTextFormat::TableColumns;
    t["TableColumnWidthConstraints"] = QTextFormat::TableColumnWidthConstraints;
    t["TableHeaderRowCount"] = QTextFormat::TableHeaderRowCount;
    t["TableCellRowSpan"] = QTextFormat::TableCellRowSpan;
    t["TableCellColumnSpan"] = QTextFormat::TableCellColumnSpan;
    t["TableCellLeftPadding"] = QTextFormat::TableCellLeftPadding;
    t["TableCellRightPadding"] = QTextFormat::TableCellRightPadding;
    t["TableCellTopPadding"] = QTextFormat::TableCellTopPadding;
    t["TableCellBottomPadding"] = QTextFormat::TableCellBottomPadding;
    t["ImageName"] = QTextFormat::ImageName;
    t["ImageWidth"] = QTextFormat::ImageWidth;
    t["ImageHeight"] = QTextFormat::ImageHeight;
    t["FullWidthSelection"] = QTextFormat::FullWidthSelection;
    t["PageBreakPolicy"] = QTextFormat::PageBreakPolicy;
    t["UserProperty"] = QTextFormat::UserProperty;

    return 0;
}
