#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "九天之上");
  set ("long", @LONG

这里就是太阳神的地盘了，太阳也在这里运转，给下界送去阳光
这个空间无边无际，而且炎热异常。
LONG);

  set("objects", ([ /* sizeof() == 1*/ 
//  __DIR__"npc/hunter" : 2,
]));

  set("outdoors", 1);
  
set("objects", ([
                __DIR__"npc/sun" : 1,
       ]) );

  setup();
}
