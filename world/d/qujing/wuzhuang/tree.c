//Cracked by Roath

//  妖神之争 １。０
//  by happ@YSZZ 2000.4.9
//  /d/qujing/wuzhuang/tree.c

#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_jie();
void create ()
{
   set ("short", "人参果树");
   set ("long", @LONG

这是一棵人参果树，真是个青枝馥郁，绿叶阴森，那叶儿却似芭蕉
模样，直上去有千尺多高，根下有七八丈周围，向南的枝上，露出
一个人参果，真象个孩儿一般，风过处裟裟做响。
树干上有一道金光灿灿的佛印，好像可以揭（jie）下来。
LONG);

   set("exits", 
   ([ //sizeof() == 4
        "up" : __DIR__"shugan1",
        "south": __DIR__"baicaidi",
   ]));
   
   setup();
}

int valid_leave(object me, string dir)
{
        if ( dir == "south" && me->query_temp("kill_tree") )
                {
        tell_object(me,HIY"忽然天上伸出一个大手，一下就把你抓走了，原来是镇元大仙。\n"NOR);
        me->move("/d/qujing/wuzhuang/chengyun");
        return notify_fail(HIC"你心里暗想，这下玩了。\n"NOR);
                }
        return ::valid_leave(me, dir);
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
	else if( me->query_temp("huohun/tu") )
	{
		message_vision("\n这道佛印，已经被你揭开了！\n",me);
		return 1;
	}
	else
	{
		me->add_temp("huohun/yuanshen",1);
		me->set_temp("huohun/tu",1);
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