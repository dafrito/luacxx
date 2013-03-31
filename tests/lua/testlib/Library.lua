
function Curry(func, first)
    return function(...)
        return func(first, ...);
    end;
end;
