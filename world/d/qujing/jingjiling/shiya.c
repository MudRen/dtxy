#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "石崖");
  set ("long", @LONG

石崖上甚是平坦，打扫的也十分干净，没有什么杂物，象是有人
常在此走动。崖边有一石桌，旁有四个石凳。后面有一小屋，屋
前石碑上刻有“木仙庵”三字。
LONG);

  set("objects", ([ /* sizeof() == 1*/ 
//  __DIR__"npc/hunter" : 2,
]));
  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
  "northdown" : __DIR__"ping",
  "southwest": __DIR__"huilin",
  "southeast": __DIR__"bolin",
  "south" : __DIR__"xinglin",
]));

  setup();
}

void init()
{ 
 	add_action("do_dig","dig");
}

int do_dig(string arg)
{
        object obj;
        object me;
        object arrow;
        me = this_player();
        obj = me->query_temp("weapon");
        if( me->query_temp("jueqing/houyi") != 2 )
        {
        	return 0;	
        }
        if( !obj )
        {
        	write("你空着手，怎么挖？\n");
        	return 1;
        }
        if( present("jiutian arrow",me) )
        {
        	write("你已经挖到了啊？！\n");
        	return 1;
        }
        message_vision(sprintf("$N用手中的%s使劲在石崖上挖掘！\n",obj->name()),me);
        if( random(me->query("kar")) > 20 )
        {
        	message_vision("$N觉得好像碰到了金属的东西，铿锵有声！\n",me);
        	message_vision("$N加把劲，终于挖出了一副弓箭，不过看上去好像没什么特别的！\n",me);
        	arrow = new("/d/moon/obj/jiutian-arrow");
        	arrow->move(me);
        }
        return 1;
}