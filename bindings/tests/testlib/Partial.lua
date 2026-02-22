function Partial(func, first)
    return function(...)
        return func(first, ...);
    end;
end;
