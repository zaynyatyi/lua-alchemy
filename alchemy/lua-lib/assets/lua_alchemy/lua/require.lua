-- Overloads
--   require()
-- Depends on
--   dofile()

do
  require = function(modname)
    as3.trace("require overloaded function", modname);
    as3.trace(modname..".lua");
    as3.trace(package.loaded[modname])
    dofile(modname..".lua");
  end
end
