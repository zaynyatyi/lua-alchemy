package
{
  import mx.collections.ArrayCollection;
  import mx.core.ByteArrayAsset;

  public class LuaSampleCode
  {
    [Embed(source="../assets/demo.lua", mimeType="application/octet-stream")]
    private static var _defaultLuaClass:Class;

    [Embed(source="../assets/hello.lua", mimeType="application/octet-stream")]
    private static var _helloLuaClass:Class;

	  [Embed(source="../assets/return.lua", mimeType="application/octet-stream")]
	  private static var _returnLuaClass:Class;

	  [Embed(source="../assets/print.lua", mimeType="application/octet-stream")]
	  private static var _printLuaClass:Class;

	  [Embed(source="../assets/movebox.lua", mimeType="application/octet-stream")]
	  private static var _moveBoxLuaClass:Class;

	  [Embed(source="../assets/buttonclick.lua", mimeType="application/octet-stream")]
	  private static var _buttonClickLuaClass:Class;

    private static var _embeddedLuaFiles:Array = [
        {label:"Hello World", asset:_helloLuaClass},
        {label:"Return Values", asset:_returnLuaClass},
        {label:"print()", asset:_printLuaClass},
        {label:"Moving Box", asset:_moveBoxLuaClass},
        {label:"Button Click", asset:_buttonClickLuaClass},
        {label:"Demo", asset:_defaultLuaClass}
    ];

    [Bindable]
    public static var sampleCode:ArrayCollection = new ArrayCollection();

    public static function init():void
    {
        var luaFile:Object;
        sampleCode.removeAll();
        sampleCode.addItem({label:"", code:""})
        for each (luaFile in _embeddedLuaFiles)
        {
            var luaAsset:ByteArrayAsset = ByteArrayAsset(new luaFile.asset());
            var luaString:String = luaAsset.toString();
            sampleCode.addItem({label:luaFile.label, code:luaString});
       }
    }


  }
}
