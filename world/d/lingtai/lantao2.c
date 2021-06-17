// Room: some place in 西牛贺洲
// forrest.c
#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_jie();
void create()
{
  set ("short", "烂桃山");
  set ("long", @LONG

这里是一片野桃林，山中的桃子无人采摘，密密的桃子挂在枝
头。地下的早已腐烂成泥，不知堆集了几百年。
桃树上有一道金光灿灿的佛印，好像可以揭（jie）下来。
LONG);
set("exits", ([ /* sizeof() == 4 */
"eastdown" : __DIR__"lantao",

]));

set("objects", ([ /* sizeof() == 2 */
"/d/lingtai/npc/swk": 1]));
  
      //set("no_clean_up", 0);
	set("outdoors", 1);
        setup();
        //replace_program(ROOM);
}
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
	else if( me->query_temp("huohun/mu") )
	{
		message_vision("\n这道佛印，已经被你揭开了！\n",me);
		return 1;
	}
	else
	{
		me->add_temp("huohun/yuanshen",1);
		me->set_temp("huohun/mu",1);
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
