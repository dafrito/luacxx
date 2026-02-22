demo = demo or {};

function demo.qt_window(...)
    require "Qt5Core.QRect";
    require "Qt5Core.QElapsedTimer";
    require "Qt5Core.Qt";
    require "Qt5Core.QEventFilter";
    require "Qt5Core.QEvent";

    require "Qt5Gui.QGuiApplication";
    require "Qt5Gui.QWindow";
    require "Qt5Gui.QBackingStore";
    require "Qt5Gui.QPainter";
    require "Qt5Gui.QVector3D";
    require "Qt5Gui.QRegion";
    require "Qt5Gui.QResizeEvent";

    require "Qt5Core.QEventFilter";

    local qApp = QGuiApplication.new("demo", ...);

    window = QWindow.new();
    store = QBackingStore.new(window);

    local function render()
        if not window:isExposed() then
            return;
        end;
        if window:width() == 0 then
            return;
        end;

        local rect = QRect.new(0, 0, window:width(), window:height());

        store:beginPaint(QRegion.new(rect));

        local painter = QPainter.new();

        painter:begin(store:paintDevice());
        painter:fillRect(0, 0, window:width(), window:height(), Qt.white);
        painter:drawText(15, 15, "Hello, world!");
        painter:endPainting();

        store:endPaint();
        store:flush(QRegion.new(rect));
    end;

    local filter = QEventFilter.new(window);
    filter:setDelegate(function(watched, event)
        print("DELEGATE", event);
        if event:type() == QEvent.Expose then
            print("RENDERING");
            render();
        elseif event:type() == QEvent.Resize then
            store:resize(QResizeEvent.cast(event):size());
            render();
        end;
        return false;
    end);
    window:installEventFilter(filter);
    window:show();

    return QGuiApplication.exec();
end;
