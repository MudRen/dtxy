inherit ROOM;

void create()
{
        set("short", "大殿");
        set("long", @LONG
    这里是玉虚洞的大殿，殿内五光十色，金碧辉煌，不时有
几个仙人来往于此处，临窗可见院中翠竹竿竿倒，金莲朵朵，
煞是漂亮。�


LONG );
        set("exits", ([
                "south" : __DIR__"wuchang",
                "northwest" : __DIR__"mishi",
        ]));
          set("kunlun", 1);
  set("objects", ([ // sizeof() == 1 //
 __DIR__"npc/luya" : 1, 
__DIR__"npc/zhangmen" : 1, 
 ]));
  set("valid_startroom", 1);
  setup();
}

