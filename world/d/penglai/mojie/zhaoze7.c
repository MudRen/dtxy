#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
 set("short", "阴阳界");
 set("long", @LONG
到了这里就快要到达魔界的中心了，经过一路熔岩火焰，这里竟然不是刮过一阵寒风，寒风好像是从不远处的一个巨大的洞穴中出来的。
LONG
 );
 set("exits", ([
  "east" : "/d/penglai/mojie/zhaoze6",
  "enter" : "/d/penglai/mojie/center",
]));
 
 setup();
}
