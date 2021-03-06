// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.

inherit ROOM;
void create()
{
        set("short", "魔界中心");
        set("long", @LONG
这里与外面的世界完全相反，一片冰天雪地，这里地形复杂，可以好好的搜索（search）一下。
LONG
        );
        set("exits", ([ 
  "out" : __DIR__"zhaoze7",
]));
        set("objects", ([
                __DIR__"npc/dragon" : 1,
       ]) );
        setup();
}

void init()
{
	object mo,ob;
	add_action("do_search", "search");
 	if( interactive( ob = this_player()) )
 	{
 		if( ob->query_temp("jueqing/binghun") == 2 && objectp(mo = present("binghun guard",environment(ob))) )
 		{
 			mo->copy_status(mo,ob,9);
 		}
	}
}

int do_search()
{
	int kar;
	object me = this_player();
	object mo = present("binghun guard",environment(me));
	object binghun;
	if( mo )
	{
		return notify_fail("冰魂守护者一晃来到你面前。\n");
	}
	if( me->is_busy() )
	{
		return notify_fail("你正忙着呢。\n");
	}
	kar = me->query("kar");
	me->start_busy(3);
	if( random(kar) > 28 ) 
	{
		message_vision("$N仔细搜索着地上，突然触到了一块什么东西。\n", me);
		message_vision("$N立刻拿起纳入怀中。\n", me);
		me->set_temp("jueqing/binghun",3);
		binghun = new(__DIR__"obj/binghun");
		binghun->move(me);
		message_vision("$N捡起冰魂，周围的气温开始升高，地上的冰雪悄悄开始融化了。\n", me);
		message_vision("$N眼见四周的熔岩开始流动，心中大急。\n", me);
		message_vision("突然冰魂上传来一股巨大的能量，将$N带离了魔界！\n", me);
		me->move("/d/penglai/bomingyan");
		return 1;
	}
	return notify_fail("你仔细找了半天，结果什么都没发现。\n");
}
