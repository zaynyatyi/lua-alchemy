all:
	(cd lua; make generic CFLAGS="-O3 -Wall -DLUA_USE_POSIX -DLUA_ANSI")
	(cd alchemy; make)
	(cd test/FluintLuaTests; ant)
	(cd demo/LuaAlchemyDemo; ant)

clean:
	(cd lua;  make clean)
	rm lua/swfbridge.log 
	rm lua/*achacks*
	rm -r lua/_sb_*
	(cd alchemy; make clean)
	(cd test/FluintLuaTests; ant clear)
	(cd demo/LuaAlchemyDemo; ant clear)
