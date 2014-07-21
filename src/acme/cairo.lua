acme = acme or {};

function acme.cairo()
    require "luacxx.search.GIRepository";
    require "cairo";

    print(cairo);
end;
