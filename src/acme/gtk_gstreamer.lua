acme = acme or {};

function acme.gtk_gstreamer()
    require "luacxx.gir"
    require "Gst"

    print(Gst.version());
end;
