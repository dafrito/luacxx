demo = demo or {};

function demo.gtk_gstreamer()
    require "luacxx.gir"
    require "Gst"

    print(Gst.version());
end;
