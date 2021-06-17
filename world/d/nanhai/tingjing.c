//Cracked by Roath
//standroom.c used by weiqi...others may hate this format:D
//tingjing.c

#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_jie();

void create ()
{
	set ("short", "听经石");
	set ("long", @LONG

这块石头(stone)状似两只并卧的海龟，静静地趴在海滩上。据说
东海龙王敖广曾派二海龟去偷听观音念经，并要它们记下经文，
好用来给水族讲解。不料，二龟光顾听经，全神贯注下竟错过了
返回大海的时间，遂变为石头。
石头上有一道金光灿灿的佛印，好像可以揭（jie）下来。
LONG);

	set("item_desc", (["stone" : "石头上刻着一首诗： \n
		见说盘陀著地灵，
		普门曾此坐谈经。
		二龟何事翻成石，
		想是当年不解听。\n", ]));
	//for look something.

	set("exits", 
	([ //sizeof() == 4
		//"south" : __DIR__"***",
		//"north" : __DIR__"wuchang-s",
		"south" : __DIR__"island",
		"north" : __DIR__"shanglu2",
		//"up" : __DIR__"***",
		//"down" : __DIR__"***",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		//__DIR__"npc/***" : 1,
	]));


	set("outdoors", "/d/nanhai");

	setup();
}

//void init()
//{
	//add_action("do_jump", "jump");
//}

//int do_jump(string arg)
//{
       
//}

void init()
{
        add_action("do_jie","jie");
}

int do_jie()
{
	object me = this_player();
	object jingang;
	if( !me->query_temp("huohun/yuanshen") )
		return 0;
	else if( me->query_temp("huohun/huo") )
	{
		message_vision("\n这道佛印，已经被你揭开了！\n",me);
		return 1;
	}
	else
	{
		me->add_temp("huohun/yuanshen",1);
		me->set_temp("huohun/huo",1);
		message_vision(HIY"\n$N轻轻将佛印揭开，一道光芒飞出，向枯松涧火云洞方向飞去！\n"NOR,me);
		message_vision(HIY"\n忽然狂风大作，空中走下两位金刚，大声喝道：谁敢私自揭开佛印？！\n",me);
		jingang = new("/d/qujing/kusong/npc/jingang");
		jingang->move(environment(me));
		jingang->kill_ob(me);
		jingang = new("/d/qujing/kusong/npc/jingang");
		jingang->move(environment(me));
		jingang->kill_ob(me);
		return 1;
	}
}